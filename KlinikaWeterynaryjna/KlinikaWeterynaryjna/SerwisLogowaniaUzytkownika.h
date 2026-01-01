/**
@file SerwisLogowaniaUzytkownikow.h
*/
#pragma once
#include "Uzytkownik.h"
#include "CzytaczUzytkownikow.h"
#include <string>
#include <memory>

using namespace std;

/**
@class SerwisLogowaniaUzytkownika
@brief Klasa odpowiedzialna za serwis logowania uzytkownikow
*/
class SerwisLogowaniaUzytkownika {
private:
	shared_ptr<CzytaczUzytkownikow> czytaczUzytkownikow;

public:
/**
@brief Konstruktor argumentowy, ustawiajacy czytacza uzytkownikow
*/
	SerwisLogowaniaUzytkownika(shared_ptr<CzytaczUzytkownikow> czytaczUzytkownikow);
/**
@brief Funkcja zwracajaca uzytkownikow, na podstawie przekazanego loginu i hasla
@param login - login uzytkownika
@param haslo - haslo uzytkownika
@return zwraca uzytkownika 
*/
	shared_ptr<Uzytkownik> zaloguj(string login, string haslo);
/**
@brief Funkcja zwracajaca uzytkownika
@param id - id uzytkownika, ktorego szukamy
@return zwraca id 
*/
	shared_ptr<Uzytkownik> znajdz(string id);
};