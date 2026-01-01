/**
@file CzytaczLekarza.h
*/
#pragma once
#include "CzytaczPlikow.h"
#include <string>
using namespace std;


/**
@class CzytaczLekarza
@brief Klasa do czytania pliku, w ktorym sa zapisani lekarze
*/
class CzytaczLekarza : public CzytaczPlikow
{
/**
@brief Funkcja zwracajace sciezke do pliku, w ktorym znajduja sie lekarze
@return sciezka do pliku zaspiana w typie tekstowym (String)
@param brak parametrow
*/
	string podajNazwePliku();
};