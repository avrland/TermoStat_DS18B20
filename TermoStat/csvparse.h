#pragma once

#include "stdafx.h"
#include "Form1.h"
#include <tchar.h>
#include <urlmon.h>
#include <string>
#include <cstdio>
#include <vcclr.h>
#include <msclr\marshal.h>
#include <Windows.h>
#include <stdio.h>
#include <msclr\marshal_cppstd.h>
#include <string>       // std::string
#include <iostream>     // std::cout
#include <sstream>      // std::stringstream, std::stringbuf
#include <streambuf>
#include <fstream>
#include "msclr\marshal_cppstd.h"

namespace term {
	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;
    using namespace System::Runtime::InteropServices;
 	using namespace std;

struct wynik {
	int rok;
	int miesiac;
	int dzien;
	int godzina;
	int minuta;
	double temperatura;
};
	bool koniec_pliku;
	public class csvparse {

	FILE* plik;
	fstream t;

public:
	
    csvparse(){

	}

	void otworz_plik(char* sciezka){
		//String^ odczyt = Form1::textBox2->Text;
		//IntPtr ptrToNativeString = Marshal::StringToHGlobalAnsi(odczyt);
      //  char* nativeString = static_cast<char*>(ptrToNativeString.ToPointer());
		t.open(sciezka);
	  //  MessageBox::Show("Plik otwarty!", "OK!", MessageBoxButtons::OK, MessageBoxIcon::Exclamation);
	}
    void zamknij_plik(void){
		t.close();
	   // MessageBox::Show("Plik zamkniêty!", "OK!", MessageBoxButtons::OK, MessageBoxIcon::Exclamation);
	}
	wynik tekst(void){
	     char znak;
		 wynik POMIAR;
		 POMIAR.rok = 0;
		 POMIAR.miesiac = 0;
		 POMIAR.dzien= 0;
		 POMIAR.godzina= 0;
		 POMIAR.minuta = 0;
		 POMIAR.temperatura = 0;

		 string str_rok, str_mies, str_dzien, str_godz, str_min, str_temp;
		for(int i=0; i<4; i++){
			 t.get(znak);
			 if(t.eof()) return POMIAR;
			 str_rok += znak;
		 }

		 String^ str2 = gcnew String(str_rok.c_str());
		 POMIAR.rok = Convert::ToInt32(str2);

		 for(int i=0; i<2; i++){
			 t.get(znak);
			 str_mies += znak;
		 }
		 str2 = gcnew String(str_mies.c_str());
		 POMIAR.miesiac = Convert::ToInt32(str2);


		 for(int i=0; i<2; i++){
			 t.get(znak);
			 str_dzien += znak;
		 }
		 str2 = gcnew String(str_dzien.c_str());
		 POMIAR.dzien = Convert::ToInt32(str2);


		 for(int i=0; i<2; i++){
			 t.get(znak);
			 str_godz += znak;
		 }
		 str2 = gcnew String(str_godz.c_str());
		 POMIAR.godzina = Convert::ToInt32(str2);


		 for(int i=0; i<2; i++){
			 t.get(znak);
			 str_min += znak;
		 }
		 str2 = gcnew String(str_min.c_str());
		 POMIAR.minuta = Convert::ToInt32(str2);
     

		 while(1){
			 t.get(znak);
			 if(znak=='\n') break;
			 str_temp += znak;
		 }
		 //str2 = gcnew String(str_temp.c_str());
		 POMIAR.temperatura = ::atof(str_temp.c_str());

		// KONIEC:
	     return POMIAR;
	}


};


}