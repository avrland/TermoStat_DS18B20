// TermoStat.cpp : main project file.

#include "stdafx.h"
#include "Form1.h"
#include "Form2.h"
#include <tchar.h>
#include <urlmon.h>
#include <string>
#include <cstdio>
#include <vcclr.h>
#include <msclr\marshal.h>
#include <Windows.h>
#include <stdio.h>
#include <msclr\marshal_cppstd.h>
#include <iostream>
#include "csvparse.h"
#include "pobieranie.cpp"
#pragma comment(lib, "MSCOREE.lib")
#pragma comment(lib, "urlmon.lib")
#pragma comment(lib,"wininet.lib")
using namespace System;
using namespace msclr::interop;
using namespace TermoStat;
using namespace term;
using namespace std;

[STAThreadAttribute]
int main(cli::array<System::String ^> ^args)
{
	// Enabling Windows XP visual effects before any controls are created
	Application::EnableVisualStyles();
	Application::SetCompatibleTextRenderingDefault(false); 
	// Create the main window and run it
	Application::Run(gcnew Form1());
	return 0;
}


//pobieranie i otwieranie pliku
System::Void Form1::button1_Click(System::Object^  sender, System::EventArgs^  e) {
	            Form2^ rgForm = gcnew Form2();
				rgForm->Show();
				rgForm->Refresh(); //potrzebne aby labele nie by³y bia³e
		     	String^ adres_logow = textBox1->Text;
                marshal_context context;
                string adres1 = context.marshal_as<std::string>(adres_logow);
				wstring To(adres1.begin(), adres1.end());
				LPCWSTR adres2 = To.c_str();

			    String^ adres_pobrania = textBox2->Text;
				adres_pobrania = adres_pobrania->Replace("\\", "\\\\");
                marshal_context context2;
                string adres1_pobrania = context2.marshal_as<std::string>(adres_pobrania);
				wstring To2(adres1_pobrania.begin(), adres1_pobrania.end());
				LPCWSTR adres2_pobrania = To2.c_str();
				HRESULT hr = URLDownloadToFile ( NULL, adres2, adres2_pobrania, 0, NULL );
				 switch (hr)
				{
					case S_OK:
					button3->Enabled = true;
					label6->ForeColor = Color::Green;
				    label6->Text = "Pobrano logi.";
					break;
					default:
					//rgForm->Hide();
					MessageBox::Show("B³êdny adres/problem z po³¹czeniem.", "B³¹d", 
						MessageBoxButtons::OK, MessageBoxIcon::Error);
					break;
				}
				rgForm->Hide();
}

//czyszczenie wykresu
System::Void Form1::button2_Click(System::Object^  sender, System::EventArgs^  e) {
		this->chart1->Series["Series1"]->Points->Clear();
		listBox2->Items->Clear();
		label6->ForeColor = Color::Blue;
	    label6->Text = "Wyczyszczono wykres.";
	    label1->Visible = true;
}

//³adowanie wykresu
System::Void Form1::button3_Click(System::Object^  sender, System::EventArgs^  e) {
	int liczba_pomiarow=0;
	double pomiar[1000], suma=0;
	double srednia;
	wynik ODCZYT, maksymalne, minimalne;
	wynik baza[1000];

	//pobieram œcie¿kê do pliku, zamieniam pojedynczy slash na podwójny, otwieram plik
	String^ odczyt = Form1::textBox2->Text;
	odczyt = odczyt->Replace("\\", "\\\\");
    IntPtr ptrToNativeString = Marshal::StringToHGlobalAnsi(odczyt);
    char* nativeString = static_cast<char*>(ptrToNativeString.ToPointer());
	klasa.otworz_plik(nativeString);
	//

     while(1){
			ODCZYT = klasa.tekst();
			baza[liczba_pomiarow] = klasa.tekst();
		  	if(ODCZYT.rok == 0) break;
			DateTime czas = DateTime(ODCZYT.rok, ODCZYT.miesiac, 
				ODCZYT.dzien, ODCZYT.godzina, ODCZYT.minuta, 00);
		    this->chart1->Series["Series1"]->Points->AddXY(czas, ODCZYT.temperatura);
			pomiar[liczba_pomiarow] = ODCZYT.temperatura;
			suma += ODCZYT.temperatura;
			liczba_pomiarow++;
	}
	klasa.zamknij_plik();
	listBox2->Items->Add("Liczba pomiarów: " + Convert::ToString(liczba_pomiarow));

	double mn = pomiar[0];
	double mx = pomiar[0];
	for(int i=1;i<liczba_pomiarow;i++){ //znajdx minimalny i maksymalny element tablicy pomiar[]
		if(mn>pomiar[i]){
			mn=pomiar[i];
			minimalne = baza[i];
		}
		else if(mx<pomiar[i]){
			maksymalne = baza[i];
			mx = pomiar[i];
		}
	}

	//wrzuæ dane do listboxa
	String^ data_poczatkowa = baza[0].dzien + "." + baza[0].miesiac + "." + 
		baza[0].rok + "r. " + baza[0].godzina + ":" + baza[0].minuta;
	String^ data_koncowa = baza[liczba_pomiarow - 2].dzien + "." + 
		baza[liczba_pomiarow - 2].miesiac + "." + baza[liczba_pomiarow - 2].rok
		+ "r. " + baza[liczba_pomiarow - 2].godzina + ":" + baza[liczba_pomiarow - 2].minuta;
	listBox2->Items->Add("Od " + data_poczatkowa + "  do  " + data_koncowa);
	listBox2->Items->Add("Max: " + Convert::ToString(mx) + "°C" + " Dnia: "
		+ maksymalne.dzien + "." + maksymalne.miesiac + "."
		+ maksymalne.rok + "  Godz: " + maksymalne.godzina + ":" + maksymalne.minuta);
	listBox2->Items->Add("Min: " + Convert::ToString(mn) + "°C" + " Dnia: " 
		+ minimalne.dzien + "." + minimalne.miesiac + "." + minimalne.rok
		+ "  Godz: " + minimalne.godzina + ":" + minimalne.minuta);
	srednia = suma/liczba_pomiarow;
    listBox2->Items->Add("Œrednia: " + Convert::ToString(roundf(srednia*100)/100) + "°C");

	label1->Visible = false; //wy³¹cz napis informuj¹cy o braku danych
	label6->ForeColor = Color::Green; //wyœwietl zielony napis 
	label6->Text = "Za³adowano wykres.";
}

//wybieranie œcie¿ki do zapisu pliku
System::Void Form1::button5_Click(System::Object^  sender, System::EventArgs^  e) {
		    openFileDialog1->Filter = "Plik logów|*.log";
            openFileDialog1->Title = "Wska¿ œcie¿kê do zapisania logów.";
	        openFileDialog1 -> ShowDialog();
			strfilename = openFileDialog1->InitialDirectory + openFileDialog1->FileName;
			textBox2->Text = strfilename;
			button1->Enabled = true; //odblokuj przycisk do pobrania logow;
}


