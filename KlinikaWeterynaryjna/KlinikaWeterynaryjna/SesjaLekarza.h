/**
@file SesjaLekarza.h
*/
#pragma once
#include "SerwisWizyt.h"
#include "Lekarz.h"
#include "SerwisZwierzat.h"
#include "SerwisUslug.h"
#include "SerwisWlasicielaZwierzecia.h"
#include <memory>

using namespace std;

/**
@class SesjaLekarza
@brief Klasa odpowiedzialna za sesje lekarza (za jego wizyty)
*/
class SesjaLekarza
{
private:
	shared_ptr<Lekarz> lekarz;
	shared_ptr<SerwisWizyt> serwisWizyt;
	shared_ptr<SerwisZwierzat> serwisZwierzat;
	shared_ptr<SerwisUslug> serwisUslug;
	shared_ptr<SerwisWlasicielaZwierzecia> serwisWlasicielaZwierzecia;
public:
/**
@brief Konstruktor argumentowy, ustawiajacy lekarza, serwis wizyt, serwis zwierzat, serwis uslug oraz serwis wlascicela zwierzecia
*/
	SesjaLekarza(shared_ptr<Lekarz> lekarz, shared_ptr<SerwisWizyt> serwisWizyt, shared_ptr<SerwisZwierzat> serwisZwierzat, shared_ptr<SerwisUslug> serwisUslug, shared_ptr<SerwisWlasicielaZwierzecia> serwisWlasicielaZwierzecia);
/**
@brief Funkcja zwracajaca lekarza
Zwraca jego imie, nazwisko, specjalizacje, dostepnosc godzinowa
@return lekarz
*/
	shared_ptr<Lekarz> getLekarz();
/**
@brief Funkcja zwracajaca serwis wizyt
@return serwis wizyt
*/
	shared_ptr<SerwisWizyt> getSerwisWizyt();
/**
@brief Funkcja zwracajaca serwis zwierzat
@return serwis zwierzat
*/
	shared_ptr<SerwisZwierzat> getSerwisZwierzat();
/**
@brief Funkcja zwracajaca fabryke uslug
@return fabryka usug
*/
	shared_ptr<SerwisUslug> getFabrykaUslug();
/**
@brief Funkcja zwracajaca serwis wlasciciela zwierzecia
@return serwis wlasciciela zwierzecia
*/
	shared_ptr<SerwisWlasicielaZwierzecia> getSerwisWlasicielaZwierzecia();
};

