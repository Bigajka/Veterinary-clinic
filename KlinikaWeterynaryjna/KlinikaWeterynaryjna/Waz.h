/**
@file Waz.h
*/
#pragma once
#include "Zwierze.h"

/**
@class Waz
@brief Klasa opisujaca weza, klasa pochodna. Dziedziczy po klasie Zwierze
*/
class Waz : public Zwierze {

public:
/**
@brief Konstruktor argumentowy, ustawiajacy pola ID zwierzecia, wiek, plec, liczbe nog, imie, ID wlasciciela, umaszczenie, kolor, wage w gramach
*/
	Waz(int idZwierzecia, int wiek, Plec plec, int liczbaNog, string imie, int idWlasciciela, string umaszczenie, string kolor, int wagaWGramach);
/**
@brief Metoda, ktora zwroci typ string, w ktorym bedzie zawarty dzwiek, ktory wydaje odpoweidni typ zwierzaka. 
Np. Dla weza Ssss ssss
*/
	string dzwiek();
/**
@brief Metoda zwracajaca sformatowana wage, w zaleznosci od wagi zwierzecia.
Np. Waz 700g
*/	
	string getWaga();
};
