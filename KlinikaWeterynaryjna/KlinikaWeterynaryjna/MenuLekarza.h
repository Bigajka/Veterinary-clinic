/**
@file MenuLekarza.h
*/
#pragma once
#include "SesjaLekarza.h"
#include <memory>

using namespace std;

/**
@enum OPCJA_POCZATKOWA_LEKARZA
@brief Typ enum reprezentujacy wszytskie dostepne opcje menu dla lekarza
*/
enum class OPCJA_POCZATKOWA_LEKARZA
{
	PRZEGLAD_WIZYT, ANULUJ_WIZYTE, WYJDZ, NIE_WYBRANO_ZADNEJ_OPCJI
};

/**
@class MenuLekarza
@brief Klasa opisujaca cale menu lekarza
*/
class MenuLekarza
{
private:

	shared_ptr<SesjaLekarza> sesjaLekarza;
public:
/**
@brief Konstruktor argumentowy, ustawiamy sesje lekarza
*/
	MenuLekarza(shared_ptr<SesjaLekarza> sesjaLekarza);
/**	
@brief Funkcja zwracajaca menu poczatkowe dla lekarza
@return zwraca opcje, ktora wybralismy (przeglad wizyt, anuluj wizyte, wyjdz)
*/
	OPCJA_POCZATKOWA_LEKARZA wyswietlMenuPoczatkowe();
/**	
@brief Funkcja wyswietlajaca wszystkie wizyty, ktore sa aktualnie dostepne
*/
	void przegladWizyt();
/**	
@brief Funkcja wyswietlajaca wszytskie wizyty, z opcja ich anulowania
*/
	void anulujWizyte();
};

