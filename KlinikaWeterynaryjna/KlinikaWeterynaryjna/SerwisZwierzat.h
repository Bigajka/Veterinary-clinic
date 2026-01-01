/**
@file SerwisZwierzat.h
*/
#pragma once
#include "CzytaczZwierzat.h"
#include "Zwierze.h"
#include <vector>
#include <memory>

using namespace std;

/**
@class SerwisZwierzat
@brief Klasa odpowiedzialna za serwis zwierzat
*/
class SerwisZwierzat
{
private:
	std::shared_ptr<CzytaczZwierzat> czytaczZwierzat;
	const int indeksId = 0;
	const int indeksImienia = 1;
	const int indeksPlci = 2;
	const int indeksWieku = 3;
	const int indeksIlosciNog = 4;
	const int indeksIdWlasiciela = 5;
	const int indeksUmaszczenia = 6;
	const int indeksKoloru = 7;
	const int indeksTypu = 8;
	const int indeksWagi = 9;
public:
/**
@brief Konstruktor argumentowy, ustawiajacy czytacz zwierzat
*/
	SerwisZwierzat(shared_ptr<CzytaczZwierzat> czytaczZwierzat);
/**
@brief Funkcja zwracajaca wszystkich zwierzeta dla danego wlasciciela
@param idWlasciciela - id wlasciciela, dla ktorego chcemy zaladowac zwierzeta
@return zwracajacy typ jest wektorem, zwraca liste zwierzat dla wlasciciela o odpowiednim id
*/
	vector<shared_ptr<Zwierze>> zaladujZwierzetaDlaWlasciciela(int idWlasciela);
/**
@brief Funkcja szukajaca zwierzecia po przekazanym id i zwierzetach wlasciciela
@param idZwierzecia - id zwierzecia
@param zwierzeta - wektor wszystkich zwierzat danego wlasciciela
@return zwraca szukane zwierze
*/
	shared_ptr<Zwierze> znajdzPoId(int idZwierzecia, vector<shared_ptr<Zwierze>> zwierzeta);
/**
@brief Funkcja zwracajaca zwierze po jego id
@param idZwierzecia - id zwierzecia szukanego
@return zwraca zwierze, ktore szukalismy
*/
	shared_ptr<Zwierze> zaladujZwierzePoId(int idZwierzecia);
/**
@brief Funkcja generujaca nastepnego id
@return zwraca nastepne id 
*/
	int getNastepneId();
/**
@brief Funkcja dodajaca zwierze
@param zwierze - zwierze, ktore chcemy dodac
*/
	void dodaj(shared_ptr<Zwierze> zwierze);
/**
@brief Funkcja usuwajaca zwierze
@param idZwierzaka - id usuwanego zwierzaka
*/
	void usunZwierzaka(int idZwierzaka);
/**
@brief Funkcja aktualizujaca zwierze
@param zwierze - zwierze, ktore chcemy zaktualizowac (dodane badz usuniete)
*/
	void zaktualizuj(shared_ptr<Zwierze> zwierze);
};

