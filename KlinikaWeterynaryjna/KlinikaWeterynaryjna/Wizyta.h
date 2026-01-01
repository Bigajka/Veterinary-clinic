/**
@file Wizyta.h
*/
#pragma once
#include <string>
#include "GodzinyPracy.h"
#include <string>

using namespace std;

/**
@class DataGodzinaWizyty
@brief Klasa odpowiedzialna za date i godzine wizyty
*/
class DataGodzinaWizyty {
private:
	int dzien;
	int miesiac;
	int rok;
	int godzina;

public:

/**
@brief Konstruktor argumentowy, ustawiajacy godzine, dzien, miesiac, rok
*/
	DataGodzinaWizyty(int godzina, int dzien, int miesiac, int rok);
/**
@brief Konstruktor bezargumentowy
*/
	DataGodzinaWizyty();
/**
@brief Funkcja zwracajaca dzien, ustawiamy w konstruktorze
@return dzien
*/
	int getDzien();
/**
@brief Funkcja zwracajaca miesiac, ustawiamy w konstruktorze
@return miesiac
*/
	int getMiesiac();
/**
@brief Funkcja zwracajaca rok, ustawiamy w konstruktorze
@return rok
*/
	int getRok();
/**
@brief Funkcja zwracajaca godzine, ustawiamy w konstruktorze
@return godzina
*/
	int getGodzina();
};

/**
@class Wizyta
@brief Klasa odpowiedzialna wizyte
*/
class Wizyta {
private:
	int idWizyty;
	DataGodzinaWizyty dataWizyty;
	int idWlasciciela;
	int idLekarza;
	int idZwierzecia;
	string typUslugi;

public:
/**
@brief Konstruktor argumentowy, ustawiajacy date wizyty, id wizyty, id wlasciciela, id zwierzecia, id lekarza, typ uslugi
*/
	Wizyta(DataGodzinaWizyty dataWizty, int idWizyty, int idWlasciciela, int idZwierzecia, int idLekarza, string typUslugi);
/**
@brief Funkcja zamieniajaca obiekt wizyty na tekst, aby mozna bylo go zapisac do pliku
@return tekst, ktory zosatnie zapisany do pliku
*/
	string zamieNaTekst();
/**
@brief Funkcja zwracajaca date i godzine wizyty
@return zwraca date i godzine
*/
	DataGodzinaWizyty getDataGodzina();
/**
@brief Funkcja generujaca id wizyty
@return zwraca id wizyty
*/
	int getIdWizyty();
/**
@brief Funkcja generujaca id wlasciciela zwierzecia
@return zwraca id wlasciciela zwierzecia
*/
	int getIdWlasciciela();
/**
@brief Funkcja generujaca id lekarza
@return zwraca id lekarza
*/
	int getIdLekarza();
/**
@brief Funkcja generujaca id zwierzecia
@return zwraca id zwierzecia
*/
	int getIdZwierzecia();
/**
@brief Funkcja zwracajaca typ uslugi
@return zwraca typ uslugi
*/
	string getTypUslugi();
/**
@brief Funkcja zwracajaca date
@return zwraca date
*/
	string getData();
/**
@brief Funkcja zwracajaca godzine
@return zwraca godzine
*/
	string getGodzina();
};
