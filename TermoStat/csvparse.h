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

	fstream t; //obiekt do odczytu pliku

public:
	
    csvparse(){

	}

	void otworz_plik(char* sciezka){
		t.open(sciezka);
	}
    void zamknij_plik(void){
		t.close();
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
		for(int i=0; i<4; i++){ //przeczytaj rok z linijki
			 t.get(znak);
			 if(t.eof()) return POMIAR; //jesli koniec pliku, zwróc strukture z samymi zerami
			 str_rok += znak;
		 }

		 String^ str2 = gcnew String(str_rok.c_str());
		 POMIAR.rok = Convert::ToInt32(str2);

		 for(int i=0; i<2; i++){ //przeczytaj miesiac z badanej linijki
			 t.get(znak);
			 str_mies += znak;
		 }
		 str2 = gcnew String(str_mies.c_str());
		 POMIAR.miesiac = Convert::ToInt32(str2);


		 for(int i=0; i<2; i++){ //przeczytaj dzien z badanej linijki
			 t.get(znak);
			 str_dzien += znak;
		 }
		 str2 = gcnew String(str_dzien.c_str());
		 POMIAR.dzien = Convert::ToInt32(str2);


		 for(int i=0; i<2; i++){ //przeczytaj godzine z badanej linijki
			 t.get(znak);
			 str_godz += znak;
		 }
		 str2 = gcnew String(str_godz.c_str());
		 POMIAR.godzina = Convert::ToInt32(str2);


		 for(int i=0; i<2; i++){ //przeczytaj minute z badanej linijki
			 t.get(znak);
			 str_min += znak;
		 }
		 str2 = gcnew String(str_min.c_str());
		 POMIAR.minuta = Convert::ToInt32(str2);
     

		 while(1){ //przeczytaj temperature z badanej linijki
			 t.get(znak);
			 if(znak=='\n') break; //jesli koniec linii przestan czytac
			 str_temp += znak;
		 }
		 POMIAR.temperatura = ::atof(str_temp.c_str()); //przerob string na floata
	     return POMIAR;
	}


};


}