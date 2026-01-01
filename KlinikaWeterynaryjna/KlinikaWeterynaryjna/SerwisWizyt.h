/**
@file SerwisWizyt.h
*/
#pragma once

#include "StatusWizyty.h"
#include "Wizyta.h"
#include "CzytaczWizyt.h"
#include<list>
#include <list>
#include <memory>

using namespace std;

/**
@class SerwisWizyt
@brief Klasa odpowiedzialna za serwis wizyt
*/
class SerwisWizyt {

private:
	shared_ptr<CzytaczWizyt> czytaczWizyt;

	const int idWizytyIndeks = 0;
	const int idLekarzaIndeks = 1;
	const int idWlasicielaZwierzeciaIndeks = 2;
	const int idZwierzeciaIndeks = 3;
	const int godzinaWizytyIndeks = 4;
	const int dzienWizytyIndeks = 5;
	const int miesiacWizytyIndeks = 6;
	const int rokWizytyIndeks = 7;
	const int typUslugiIndeks = 8;
public:
/**
@brief Konstruktor argumentowy, ustawiajacy czytacz wizyt
*/
	SerwisWizyt(shared_ptr<CzytaczWizyt> czytaczWizyt);
/**
@brief Funkcja rezerwujaca wizyte
@param wizyta - wizyta, ktorya chcemy zarezerwowac
@return zwraca status czy operacaj jest powiodla
*/
	StatusWizyty zarezerujWizyte(Wizyta wizyta);
/**
@brief Funkcja anulujacy wizyte
@param idwizyta - wizyta, ktorya chcemy zarezerwowac, szukamy jej po id
@return zwraca status czy operacaj jest powiodla
*/
	StatusWizyty anulujWizyte(int idWizyty);
/**
@brief Funkcja anulujacy wizyte dle zwierzaka
@param idZwierzaka - wizyta, ktorya chcemy zarezerwowac, szukamy jej po id zwierzaka
@return zwraca status czy operacaj jest powiodla
*/
	StatusWizyty anulujWizyteDlaZwierzaka(int idZwierzaka);
/**
@brief Funkcja zwracajaca wizyty dla danego wlasciciela po id
@param idWlasicielZwierzecia - id wlasciciela, dla ktorego chcemy znalezc wizyty
@return zwraca liste wizyt dla danego wlasciciela
*/
	list<shared_ptr<Wizyta>> przegladWizytPoIdWlasiciela(int idWlasicielZwierzecia);
/**
@brief Funkcja zwracajaca wizyty na podstawie przekazanego roku, miesiaca, dnia
@param rok - rok dla przegladajacych wizyt
@param miesiac - miesiac dla przegladajacych wizyt
@param dzien - dzien dla przegladajacych wizyt
@return zwraca liste wizyt dla konkretnej daty
*/
	list<shared_ptr<Wizyta>> zaladujWizytyDlaDaty(int rok, int miesiac, int dzien);
/**
@brief Funkcja zwracajaca wizyty dla danego lekarza po id
@param idLekarza - - id lekarza, dla ktorego chcemy znalezc wizyty
@return zwraca liste wizyt dla konkretnego lekarza
*/
	list<shared_ptr<Wizyta>> przegladWizytPoIdLekarza(int idLekarza);
/**
@brief Funkcja generujaca nastepnego id, ktore mozna uzyc do zapisu na kolejna wizyte
@return zwraca nastepne id do zapisu wizyty
*/
	int getNastepneId();
};