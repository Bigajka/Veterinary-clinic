/**
@file Kanarek.h
*/
#pragma once
#include "Zwierze.h"

using namespace std;
/**
@class Kanarek
@brief Klasa opisujaca kanarka, klasa pochodna. Dziedziczy po klasie Zwierze
*/

class Kanarek : public Zwierze {

public:

/**
@brief Konstruktor argumentowy, ustawiajacy pola ID zwierzecia, wiek, plec, liczbe nog, imie, ID wlasciciela, umaszczenie, kolor, wage w gramach
*/
	Kanarek(int idZwierzecia, int wiek, Plec plec, int liczbaNog, string imie, int idWlasciciela, string umaszczenie, string kolor, int wagaWGramach);
/**
@brief Metoda, ktora zwroci typ string, w ktorym bedzie zawarty dzwiek, ktory wydaje odpoweidni typ zwierzaka. 
Np. Dla kanarka cwr cwir
*/
	string dzwiek();
/**
@brief Metoda zwracajaca sformatowana wage, w zaleznosci od wagi zwierzecia.
Np. Kanarek 300g
*/
	string getWaga();

};

