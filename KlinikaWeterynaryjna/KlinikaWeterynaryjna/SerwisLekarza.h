/**
@file SerwisLekarza.h
*/
#pragma once
#include "CzytaczLekarza.h"
#include "Lekarz.h"
#include <vector>
#include "SerwisLogowaniaUzytkownika.h"
#include <memory>

using namespace std;

/**
@class SerwisLekarza
@brief Klasa odpowiedzialna za serwis lekarza
*/
class SerwisLekarza
{
private:
	shared_ptr<CzytaczLekarza> czytaczLekarza;
	shared_ptr<SerwisLogowaniaUzytkownika> serwisLogowaniaUzytkownika;
	const int indeksId = 0;
	const int indeksImienia = 1;
	const int indeksNazwiska = 2;
	const int indeksSpecjalizacji = 3;
public:
/**
@brief Konstruktor argumentowy, ustawiajacy czytacza lekarza, czytacza uzytkownikow
*/
	SerwisLekarza(shared_ptr<CzytaczLekarza> czytaczLekarza, shared_ptr<SerwisLogowaniaUzytkownika> czytaczUzytkownikow);
/**
@brief Funkcja zwracajaca lekarza, na podstawie przekazanego uzytkownika.
Szukamy lekarza po id uzytkownika
@param uzytkownik - wskaznik na obiekt uzytkownik
@return zwraca wskaznik na lekarza, o ile zostal znaleziony
*/
	shared_ptr<Lekarz> zaladujLekarza(shared_ptr<Uzytkownik> uzytkownik);
/**
@brief Funkcja zwracajaca wszystkich lekarzy
@return zwracajacy typ jest lista wskaznikow na lekarzy, jezeli go nie znajdzie to zwraca NULL
*/
	list<shared_ptr<Lekarz>> zaladujWszystkichLekarzy();
/**
@brief Funkcja szukajaca lekarza po przekazanym id w podanej liscie lekarzy 
@param idLekarza - id szukanego lekarza
@param lekarze - lista lekarzy, wsrod ktorych chcemy znalezc o podanym id
@return zwraca szukanego lekarza, jezeli go nie znajdzie to zwraca NULL
*/
	shared_ptr<Lekarz> znajdzLekarzaPoId(int idLekarza, list<shared_ptr<Lekarz>> lekarze);
};

