/**
@file SerwisWlascicielaZwierzecia.h
*/
#pragma once
#include"CzytaczWlasicielaZwierzecia.h"
#include "SerwisLogowaniaUzytkownika.h"
#include "WlascicielZwierzecia.h"

/**
@class SerwisWlasicielaZwierzecia
@brief Klasa odpowiedzialna za serwis wlasciciela zwierzecia
*/
class SerwisWlasicielaZwierzecia
{
private:
	std::shared_ptr<CzytaczWlasicielaZwierzecia> czytaczWlasicielaZwierzecia;
	std::shared_ptr<SerwisLogowaniaUzytkownika> serwisLogowaniaUzytkownika;
	const int indeksImienia = 0;
	const int indeksId = 1;
	const int indekMiasta = 2;
	const int indeksKoduPocztowego = 3;
	const int indeksUlicyINumeruDomu = 4;
	const int indeksNumeruTelefonu = 5;
public:
/**
@brief Konstruktor argumentowy, ustawiajacy czytacz wlasciciela zwierzecia, serwis logowania uzytkownika
*/
	SerwisWlasicielaZwierzecia(std::shared_ptr<CzytaczWlasicielaZwierzecia> czytaczWlasicielaZwierzecia, std::shared_ptr<SerwisLogowaniaUzytkownika> serwisLogowaniaUzytkownika);
/**
@brief Funkcja zwracajaca wlasciciela zwierzecia, na podstawie przekazanego uzytkownika.
Szukamy wlasciciela zwierzecia po id uzytkownika
@param uzytkownik - wskaznik na obiekt uzytkownik
@return zwraca wskaznik na wlasciciela zwierzecia, o ile zostal znaleziony
*/
	std::shared_ptr<WlascicielZwierzecia> zaladujWlascicielaZwierzecia(std::shared_ptr<Uzytkownik> uzytkownik);
/**
@brief Funkcja szukajaca wlasciciela zwierzecia po przekazanym id w podanej liccie wlascicieli
@param id - id szukanego wlasciciela
@return zwraca szukanego wlasciciela, jezeli go nie znajdzie to zwraca NULL
*/
	std::shared_ptr<WlascicielZwierzecia> zaladujWlascicielaZwierzeciaPoId(int id);

};

