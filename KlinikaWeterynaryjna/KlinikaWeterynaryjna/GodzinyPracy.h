/**
@file GodzinyPracy.h
*/
#pragma once
/**
@class GodzinyPracy
@brief Klasa opisujaca strukture godzin pracy, gdzie mamy godzine rozpoczecia i zakonczenia wraz z minutami
*/
class GodzinyPracy {

private:
	int godzinaRozpoczecia;
	int minutaRozpoczecia;
	int godzinaZakonczenia;
	int minutaZakonczenia;

public:
/**
@brief Konstruktor domyslny, bezargumentowy
*/
	GodzinyPracy();
/**
@brief Konstruktor argumentowy ustawia godziny, minuty zakonczenia i rozpoczecia
*/
	GodzinyPracy(int godzinaRozpoczecia, int minutaRozpoczecia, int godzinaZakonczenia, int minutaZakonczenia);
/**
@brief Funkcja zwracajaca godziny rozpoczecia
@return Godziny rozpoczecia
*/
	int getGodzinaRozpoczecia();
/**
@brief Funkcja zwracajaca godziny zakonczenia
@return Godziny Zakonczenia
*/
	int getGodzinaZakonczenia();
/**
@brief Funkcja zwracajaca minuty rozpoczecia
@return Minuty rozpoczecia
*/
	int getMinutaRozpoczecia();
/**
@brief Funkcja zwracajaca minuty zakonczenia
@return Minuty zakonczenia
*/
	int getMinutaZakonczenia();
};
