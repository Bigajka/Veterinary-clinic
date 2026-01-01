/**
@file CzytaczGrafikuPracy.h
*/
#pragma once
#include "CzytaczPlikow.h"
#include <string>

using namespace std;

/**
@class CzytaczGrafikuPracy
@brief Klasa do czytania pliku, w ktorym jest zapisany grafik pracy kliniki
*/
class CzytaczGrafikuPracy : public CzytaczPlikow
{
/**
@brief Funkcja zwracajace sciezke do pliku, w ktorym znajduje sie grafik pracy
@return sciezka do pliku zaspiana w typie tekstowym (String)
@param brak parametrow
*/
	string podajNazwePliku();
};


