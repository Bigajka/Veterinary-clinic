/**
@file Pies.h
*/
#pragma once
#include "Zwierze.h"

using namespace std;

/**
@class Pies
@brief Klasa opisujaca psa, klasa pochodna. Dziedziczy po klasie Zwierze
*/
class Pies : public Zwierze {

public:
/**
@brief Konstruktor argumentowy, ustawiajacy pola ID zwierzecia, wiek, plec, liczbe nog, imie, ID wlasciciela, umaszczenie, kolor, wage w gramach
*/
	Pies(int idZwierzecia, int wiek, Plec plec, int liczbaNog, string imie, int idWlasciciela, string umaszczenie, string kolor, int wagaWGramach);
/**
@brief Metoda, ktora zwroci typ string, w ktorym bedzie zawarty dzwiek, ktory wydaje odpoweidni typ zwierzaka. 
Np. Dla psa Hau hau
*/
	string dzwiek();
/**
@brief Metoda zwracajaca sformatowana wage, w zaleznosci od wagi zwierzecia.
Np. Pies 6000g
*/
	string getWaga();
};
