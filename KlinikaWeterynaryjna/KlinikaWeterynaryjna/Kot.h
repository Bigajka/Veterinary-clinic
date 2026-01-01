/**
@file Kot.h
*/
#pragma once
#include "Zwierze.h" 
#include<string>

using namespace std;

/**
@class Kot
@brief Klasa opisujaca kota, klasa pochodna. Dziedziczy po klasie Zwierze
*/
class Kot :public Zwierze {

public:
/**
@brief Konstruktor argumentowy, ustawiajacy pola ID zwierzecia, wiek, plec, liczbe nog, imie, ID wlasciciela, umaszczenie, kolor, wage w gramach
*/
	Kot(int id, int wiek, Plec plec, int liczbaNog, string imie, int idWlasciciela, string umaszczenie, string kolor, int wagaWGramach);
/**
@brief Metoda, ktora zwroci typ string, w ktorym bedzie zawarty dzwiek, ktory wydaje odpoweidni typ zwierzaka. 
Np. Dla kota Miua miau
*/
	string dzwiek();
/**
@brief Metoda zwracajaca sformatowana wage, w zaleznosci od wagi zwierzecia.
Np. Kot 4000g
*/
	string getWaga();
};

