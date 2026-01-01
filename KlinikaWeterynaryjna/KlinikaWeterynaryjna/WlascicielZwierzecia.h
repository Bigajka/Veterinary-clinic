/**
@file WlascicielZwierzecia.h
*/
#pragma once
#include "Uzytkownik.h"
#include <string>

using namespace std;

/**
@class WlascicielZwierzecia
@brief Klasa odpowiedzialna za wlasciciela zwierzecia
*/
class WlascicielZwierzecia : public Uzytkownik {

private:
	string imie;
	int id;
	string miasto;
	string kodPocztowy;
	string ulicaINumerDomu;
	string numerTelefonu;


public:
/**
@brief Konstruktor argumentowy, ustawiajacy imie, id, miasto, kod pocztowy, ulice i numer domu, numer telefonu, uzytkownika
*/
	WlascicielZwierzecia(string imie, int id, string miasto, string kodPocztowy, string ulicaINumerDomu, string numerTelefonu, Uzytkownik& uzytkownik);
/**
@brief Funkcja zwracajaca imie
@return imie wlasciciela zwierzecia
*/
	string getImie();
/**
@brief Funkcja zwracajaca id wlasciceila zwierzecia
@return id wlasciciela zwierzecia
*/
	int getId();
/**
@brief Funkcja zwracajaca miasto
@return miasto wlasciciela zwierzecia
*/
	string getMiasto();
/**
@brief Funkcja zwracajaca kod pocztowy
@return kod pocztowy wlasciciela zwierzecia
*/
	string getKodPoczowy();
/**
@brief Funkcja zwracajaca ulice i numer domu
@return ulice i numer domu wlasciciela zwierzecia
*/
	string getUlicaINumerDomu();
/**
@brief Funkcja zwracajaca numer telefonu
@return numer telefonu wlasciciela zwierzecia
*/
	string getNumerTelefonu();
/**
@brief Funkcja ustawiajaca miasto
@param miasto - miasto
*/
	void setMiasto(string miasto);
/**
@brief Funkcja ustawiajaca kod pocztowy
@param kodPocztowy - kodPocztowy
*/
	void setKodPocztowy(string kodPocztowy);
/**
@brief Funkcja ustawiajaca ulice i numer domu
@param ulicaINumerDomu - ulica i numer domu
*/
	void setUlicaINumerDomu(string ulicaINumerDomu);
/**
@brief Funkcja ustawiajaca numer telefonu
@param numerTelefonu - numer telefonu
*/
	void setNumerTelefonu(string numerTelefonu);
};