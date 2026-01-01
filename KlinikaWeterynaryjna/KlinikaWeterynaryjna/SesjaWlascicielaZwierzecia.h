/**
@file SesjaWlascicielaZwierzecia.h
*/
#pragma once
#include "Zwierze.h"
#include "Usluga.h"
#include <vector>
#include "WlascicielZwierzecia.h"
#include <memory>

using namespace std;

/**
@class SesjaWlascicielaZwierzecia
@brief Klasa odpowiedzialna za sesje wlasciciela zwierzecia
*/
class SesjaWlascicielaZwierzecia
{
private:
	shared_ptr<WlascicielZwierzecia> wlascicielZwierzecia;
	shared_ptr<Zwierze> wybraneZwierze;
	vector<shared_ptr<Zwierze>> zwierzetaUztkownika;
	shared_ptr<Usluga> wybranaUsluga;
	shared_ptr<pair<int, time_t>> wybranyDzien;
	shared_ptr<pair<int, time_t>> wybranyMiesiac;
	shared_ptr<pair<int, time_t>> wybranyRok;
	int wybranaGodzina;
	int idWybranegoLekarza;

public:

/**
@brief Konstruktor argumentowy, ustawiajacy wlasciciela zwierzecia, zwierzeta
*/
	SesjaWlascicielaZwierzecia(shared_ptr<WlascicielZwierzecia> wlascicielZwierzecia, vector<shared_ptr<Zwierze>> zwierzeta);
/**
@brief Funkcja zwracajaca wszystkie zwierzeta aktualnie zalogowanego wlasciciela
@return zwraca wektor zwierzat
*/
	vector<shared_ptr<Zwierze>> getZwierzeta();
/**
@brief Funkcja zwracajaca wszystkie wybrane zwierzeta aktualnie zalogowanego wlasciciela
@return zwraca wybrane zwierzeta
*/
	shared_ptr<Zwierze> getWybarneZwierze();
/**
@brief Funkcja zwracajaca zalogowanego wlasciciela
@return zwraca wlasciciela zwierzecia
*/
	shared_ptr<WlascicielZwierzecia> getWlasicielZwierzecia();
/**
@brief Funkcja ustawiajaca wybrane zwierze
@param zwierze - wybrane zwierze
*/
	void setWybraneZwierze(shared_ptr<Zwierze> zwierze);
/**
@brief Funkcja ustawiajaca wybrana usluge
@param wybranaUsluga - wybrane usluga
*/
	void setWybranaUsluga(shared_ptr<Usluga> wybranaUsluga);
/**
@brief Funkcja zwracajaca wybrana usluge
@return zwraca wybrana usluge przez wlasciciela zwierzecia
*/
	shared_ptr<Usluga> getWybranaUsluga();
/**
@brief Funkcja ustawiajaca wybrany miesiac
@param wybranyMiesiac - wybrany miesiac
*/
	void setWybranyMiesiac(shared_ptr<pair<int, time_t>> wybranyMiesiac);
/**
@brief Funkcja zwracajaca wybrany miesiac
@return zwraca wybrany miesiac przez wlasciciela zwierzecia
*/
	shared_ptr<pair<int, time_t>> getWybranyMiesiac();
/**
@brief Funkcja ustawiajaca wybrany dzien
@param wybranyDzien - wybrany dzien
*/
	void setWybranyDzien(shared_ptr<pair<int, time_t>> wybranyDzien);
/**
@brief Funkcja zwracajaca wybrany dzien
@return zwraca wybrany dzien przez wlasciciela zwierzecia
*/
	shared_ptr<pair<int, time_t>> getWybranyDzien();
/**
@brief Funkcja ustawiajaca wybrany rok
@param wybranyRok - wybrany rok
*/
	void setWybranyRok(shared_ptr<pair<int, time_t>> wybranyRok);
/**
@brief Funkcja zwracajaca wybrany rok
@return zwraca wybrany rok przez wlasciciela zwierzecia
*/
	shared_ptr<pair<int, time_t>> getWybranyRok();
/**
@brief Funkcja ustawiajaca wybrana godzine
@param wybranaGodzina - wybrana godzina
*/
	void setWybranaGodzina(int wybranaGodzina);
/**
@brief Funkcja zwracajaca wybrana godzine
@return zwraca wybrana godzine przez wlasciciela zwierzecia
*/
	int getWybranaGodzina();
/**
@brief Funkcja ustawiajaca id wybranego lekarza
@param idLekarza - id wybranego lekarza 
*/
	void setIdWybranegoLekarza(int idLekarza);
/**
@brief Funkcja zwracajaca id wybranego lekarza
@return zwraca id wybranego lekarza przez wlasciciela zwierzecia
*/
	int getIdWybranegoLekarza();
/**
@brief Funkcja sprawdzajaca czy wszystkie potrzebne dane sa ustawione do rezerwacji wizyty
@return zwraca true jezeli mozna utworzyc wizyte, false jezeli nie mozna
*/
	bool czyMoznaUtworzycWizyte();
/**
@brief Funkcja odswiezajaca wszystkie zwierzeta.
Jej wywolanie jest wymagane po dodaniu nowego zwierzaka, aby miec odswiezaona liste (ma zawierac nowo dodanego zwierzaka) 
*/
	void odswiezZwierzeta(vector<shared_ptr<Zwierze>> zwierzeta);
};