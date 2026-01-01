/**
@file CzytaczZwierzat.h
*/
#pragma once
#include "CzytaczPlikow.h"

using namespace std;

/**
@class CzytaczZwierzat
@brief Klasa bazowa do czytania zwierzat
*/
class CzytaczZwierzat: public CzytaczPlikow {
public:
/**
@brief Funkcja zwracajace sciezke do pliku, w ktorym znajduja sie zwierzeta.
@return sciezka do pliku zaspiana w typie tekstowym (String)
@param brak parametrow
*/
	string podajNazwePliku();
};

