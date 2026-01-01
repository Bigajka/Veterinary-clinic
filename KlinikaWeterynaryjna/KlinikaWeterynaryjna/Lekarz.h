/**
@file Lekarz.h
*/
#pragma once
#include <unordered_map>
#include <string>
#include "Uzytkownik.h"
#include  "GodzinyPracy.h"
#include "DniTygodnia.h"

using namespace std;

/**
@class Lekarz
@brief Klasa opisujaca lekarza, klasa pochodna. Dziedziczy po klasie Uzytkownik
*/
class Lekarz : public Uzytkownik{

private :
	string imie;
	string nazwisko;
	string specjalizacja;
	unordered_map<DniTygodnia, GodzinyPracy> dostepnosc;

public :
/**
@brief Konstruktor argumentowy, ustawiajacy pola imie, nazwisko, specjalizacje oraz typ uzytkownika lekarza
*/
	Lekarz(string imie, string nazwisko, string specjalizacja, Uzytkownik& uzytkownik);
/**
@brief Funkcja zwracajaca imie danego lekarza
@return Imie lekarza
*/
	string getImie();
/**
@brief Funkcja zwracajaca nazwisko danego lekarza
@return Nazwisko lekarza
*/
	string getNazwisko();
/**
@brief Funkcja zwracajaca specjalizacje danego lekarza
@return Specjalizacja lekarza
*/
	string getSpecjalizacja();
/**
@brief Funkcja zwracajaca godziny pracy lekarza na dany dzien
@return dostepnosc na konkretny dzien 
@param dzien - dzien, dla ktorego chcemy sprawdzic godziny pracy
*/
	GodzinyPracy zwrocGodzinyPracyDlaDnia(DniTygodnia dzien) {
		return dostepnosc[dzien];
	}
/**
@brief Funkcja zwracajaca czy konkretny lekarz jest dostepny w godzinach 
@param godzina - godzina, ktora chcemy sprawdzic czy jest dostepny lekarz 
@param dzienTygodnia - dzien, dla ktorego chcemy sprawdzic dostepnosc lekarza
*/
	bool czyDostepnyWGodzinach(int godzina, DniTygodnia dzienTygodnia);
};