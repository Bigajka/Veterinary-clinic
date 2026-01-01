/**
@file Zwierze.h
*/
#pragma once
#include <string>
#include "Plec.h"

using namespace std;

/**
@class Zwierze
@brief Klasa odpowiedzialna za zwierzeta
*/
class Zwierze {

private: 
	int id;
	int wiek;
	Plec plec;
	int liczbaNog;
	string imie;
	int idWlasciciela;
	string umaszczenie;
	string kolor;

protected:
	/**
	@brief Pole klasy, przechowywujace wage zwierzeecia w gramach
	@return waga w gramach
	*/
	int wagaWGramach;

public:

/**
@brief Konstruktor argumentowy, ustawiajacy id, wiek, plec, liczbe nog, imie, id wlasciciela, umaszczenie, kolor, wage w gramach
*/
	Zwierze(int id, int wiek, Plec plec, int liczbaNog, string imie, int idWlasciciela, string umaszczenie, string kolor, int wagaWGramach);
/**
@brief Funkcja zwracajaca id zwierzecia
@return id zwierzecia
*/
	int getId();
/**
@brief Funkcja zwracajaca wiek zwierzecia
@return wiek zwierzecia
*/
	int getWiek();
/**
@brief Zwraca enum plec, okreslajacy czy jest to samiec czy samica
@return plec
*/
	Plec getPlec();
/**
@brief Funkcja zwracajaca liczbe nog zwierzecia
@return liczba nog zwierzecia
*/
	int getliczaNog();
/**
@brief Funkcja zwracajaca imie zwierzecia
@return imie zwierzecia
*/
	string getImie();
/**
@brief Funkcja zwracajaca id wlasciciela zwierzaka
@return id wlasciciela zwierzaka
*/
	int getIdWlasciciela();
/**
@brief Funkcja zwracajaca umaszczenie zwierzaka
@return umaszczenie
*/
	string getUmaszczenie();
/**
@brief Funkcja zwracajaca kolor zwierzaka
@return kolor
*/
	string getKolor();
/**
@brief Funkcja wirtualna, zwracajaca dzwiek jaki wydaje konkretne zwierze.
Klasy dziedziczace po klasie zwierze musza zaimplementowac metode dzwiek(). Np. kot ma wydawac dzwiek miau
@return dzwiek jaki wydaje dane zwierze
*/
	virtual string dzwiek() = 0;
/**
@brief Funkcja wirtualna, zwracajaca wage dla konkretnego zwierzecia.
Klasy dziedziczace po klasie zwierze musza zaimplementowac metode getWaga(). Np. kot ma miec wyswietlana wage w kg, a kanarek w gramch
@return dzwiek jaki wydaje dane zwierze
*/
	virtual string getWaga() = 0;
/**
@brief Funkcja ustawiajaca wage, ktora ma byc w gramach
@param wagaWGramach - waga w gramach
*/
	void setWagaWGramach(int wagaWGramach);
/**
@brief Funkcja ustawiajaca imie
@param imie - imie zwierzaka
*/
	void setImie(string imie);
/**
@brief Funkcja zamieniajaca obiekt zwierze na tekst, aby mozna bylo go zapisac do pliku
@return tekst, ktory zosatnie zapisany do pliku
*/
	string zamienNaTekst();
};

