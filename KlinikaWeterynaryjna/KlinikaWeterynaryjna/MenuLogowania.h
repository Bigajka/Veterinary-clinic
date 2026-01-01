/**
@file MenuLogowania.h
*/
#pragma once
#include <string>
#include "MenuLogowaniaStatusu.h"

using namespace std;

/**
@class MenuLogowania
@brief Klasa zajmujaca sie obsluzeniem menu logowania
*/
class MenuLogowania
{
private:

	string login = "";
	string haslo = "";

public: 
/**
@brief Funkcja zwracajaca login
@param login uzytkownika
*/
	string getLogin();
/**
@brief Funkcja zwracajaca haslo
@param haslo uzytkownika
*/
	string getHaslo();
/**	
@brief Funkcja zwracajaca menu poczatkowe dla uzytkownika
@return zwraca opcje, ktora uzytkownik wybral (logowanie, wyjscie)
*/
	MenuLogowaniaStatusu wyswietlMenuPoczatkowe();
/**	
@brief Funkcja wyswietlajaca menu logowania dla konkretnego typu uzytkownika
*/
	void wyswietMenuLogowania();
};

