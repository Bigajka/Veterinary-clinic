/**
@file CzytaczWlascicielaZwierzecia.h
*/
#pragma once
#include "CzytaczPlikow.h"
#include <string>
using namespace std;

/**
@class CzytaczWlasicielaZwierzecia
@brief Klasa bazowa do czytania wlasciciela zwierzeci
*/
class CzytaczWlasicielaZwierzecia : public CzytaczPlikow
{
/**
@brief Funkcja zwracajace sciezke do pliku, w ktorym znajduja sie wlasciciele zwierzat.
@return sciezka do pliku zaspiana w typie tekstowym (String)
@param brak parametrow
*/
	string podajNazwePliku();
};

