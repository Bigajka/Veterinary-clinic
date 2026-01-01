/**
@file CzytaczUzytkownikow.h
*/
#pragma once
#include "CzytaczPlikow.h"

using namespace std;

/**
@class CzytaczUzytkownikow
@brief Klasa bazowa do czytania uzytkownikow (lekarz, wlasciciel zwierzecia)
*/
class CzytaczUzytkownikow  : public CzytaczPlikow
{
public:
/**
@brief Funkcja zwracajace sciezke do pliku, w ktorym znajduja sie uzytkownicy.
@return sciezka do pliku zaspiana w typie tekstowym (String)
@param brak parametrow
*/
	string podajNazwePliku();
};

