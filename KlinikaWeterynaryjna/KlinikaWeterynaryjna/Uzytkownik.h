/**
@file Uzytkownik.h
*/
#pragma once
#include <string>
#include "TypUzytkownika.h"

using namespace std;

/**
@class Uzytkownik
@brief Klasa odpowiedzialna za uzytkownikow
*/
class Uzytkownik {
private:
	string login;
	string haslo;
	int id;
	TypUzytkownika typUzytkownika;
	
public:
/**
@brief Konstruktor argumentowy, ustawiajacy login, haslo, typ uzytkownika
*/
		Uzytkownik(string login, string haslo, int id, TypUzytkownika typUzytkownika);
/**
@brief Funkcja zamieniajaca obiekt uzytkownika na tekst, aby mozna bylo go zapisac do pliku
@return tekst, ktory zosatnie zapisany do pliku
*/
		string zamienNaTekst();
/**
@brief Funkcja zwracajaca id uzytkownika
@return zwraca id uzytkownika
*/
		int getId();
/**
@brief Funkcja zwracajaca typ uzytkownika (lekarz, wlasciciela zwierzecia)
@return zwraca typ uzytkownika
*/
		TypUzytkownika getTypUzytkownika();
/**
@brief Stala okreslajaca id nieznanego uzytkownika
*/
		static const int ID_DLA_NIEZNANEGO_UZYTKOWNIKA = -1;
};