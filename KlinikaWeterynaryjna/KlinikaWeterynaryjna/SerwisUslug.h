/**
@file SerwisUslug.h
*/
#pragma once

#include <vector>
#include "Usluga.h"
#include "Zwierze.h"
#include "Pies.h"
#include "Kot.h"
#include "Kanarek.h"
#include "Waz.h"
#include "Pajak.h"
#include <memory>
#include <list>

using namespace std;

/**
@class SerwisUslug
@brief Klasa odpowiedzialna za serwis uslug
*/
class SerwisUslug
{
private:
    list<shared_ptr<Usluga>> dostepneUslugi;
public:
/**
@brief Konstruktor bezargumentowy
*/
    SerwisUslug();
/**
@brief Funkcja zwracajaca zainicjalizowane uslugi dla zwierzat
*/
    void zainicjalizujUslugi();
/**
@brief Funkcja szukajaca uslugi po przekazanym typie w podanej liscie uslug
@param typ - typ zwierzaka
@return zwraca szukana usluge
*/
    shared_ptr<Usluga> znajdzPoTypie(string typ);
/**
@brief Funkcja tworzaca usluge dla konkretnego juz zwierzaka
@param zwierze - dla niego szukamy odpowiednich uslug
@return zwraca wektor uslug dla danego zwierzaka
*/
    vector<shared_ptr<Usluga>> stworzUslugeDlaZwierzaka(shared_ptr<Zwierze> zwierze);
};

