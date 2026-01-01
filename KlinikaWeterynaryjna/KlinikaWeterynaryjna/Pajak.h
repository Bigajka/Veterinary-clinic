/**
@file Pajak.h
*/
#pragma once
#include "Zwierze.h"

using namespace std;

/**
@class Pajak
@brief Klasa opisujaca pajaka, klasa pochodna. Dziedziczy po klasie Zwierze
*/
class Pajak : public Zwierze {

public:
/**
@brief Konstruktor argumentowy, ustawiajacy pola ID zwierzecia, wiek, plec, liczbe nog, imie, ID wlasciciela, umaszczenie, kolor, wage w gramach
*/
	Pajak(int idZwierzecia, int wiek, Plec plec, int liczbaNog, string imie, int idWlasciciela, string umaszczenie, string kolor, int wagaWGramch);
/**
@brief Metoda, ktora zwroci typ string, w ktorym bedzie zawarty dzwiek, ktory wydaje odpoweidni typ zwierzaka. 
Np. Dla pajaka Skrr skrrr
*/
	string dzwiek();
/**
@brief Metoda zwracajaca sformatowana wage, w zaleznosci od wagi zwierzecia.
Np. pajak 200g
*/
	string getWaga();
};

