/**
@file Usluga.h
*/
#pragma once
#include <string>
#include <vector>

using namespace std;

/**
@class Usluga
@brief Klasa odpowiedzialna za uslugi
*/
class Usluga {
private:
	int cena;
	string nazwaUslugi;
	string typUslugi;

public: 
/**
@brief Konstruktor argumentowy, ustawiajacy cene, nazwe uslugi i typ uslugi
*/
	Usluga(int cena, string nazwaUslugi, string typUslugi);
/**
@brief Funkcja zwracajaca cene
@return zwraca cene uslugi
*/
	int getCena();
/**
@brief Funkcja zwracajaca typ uslugi
@return zwraca typ uslugi
*/
	string getTypUslugi();
/**
@brief Funkcja zwracajaca nazwe uslugi
@return zwraca nazwe uslugi
*/
	string getNazwaUslugi();
};