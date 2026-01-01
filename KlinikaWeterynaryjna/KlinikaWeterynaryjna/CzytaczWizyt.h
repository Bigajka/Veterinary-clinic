/**
@file CzytaczWizyt.h
*/
#pragma once
#include "CzytaczPlikow.h"
#include "Wizyta.h"

using namespace std;

/**
@class CzytaczWizyt
@brief Klasa bazowa do czytania wizyt
*/
class CzytaczWizyt : public CzytaczPlikow
{
public:
/**
@brief Funkcja zwracajace sciezke do pliku, w ktorym znajduja sie wszystkie wizyty.
@return sciezka do pliku zaspiana w typie tekstowym (String)
@param brak parametrow
*/
	string podajNazwePliku();
};

