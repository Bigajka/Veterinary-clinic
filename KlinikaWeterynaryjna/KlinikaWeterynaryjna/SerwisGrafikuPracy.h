/**
@file SerwisGrafikuPracy.h
*/
#pragma once
#include "CzytaczGrafikuPracy.h"
#include "Lekarz.h"
#include <unordered_map>
#include <memory>

/**
@class SerwisGrafikuPracy
@brief Klasa odpowiedzialna za serwis grafiku pracy
*/
class SerwisGrafikuPracy {
private:
	shared_ptr<CzytaczGrafikuPracy> czytaczGrafikuPracy;
public:
/**
@brief Konstruktor argumentowy, ustawiajacy czytacz grafiku pracy
*/
	SerwisGrafikuPracy(shared_ptr <CzytaczGrafikuPracy> czytaczGrafikuPracy);
/**
@brief Funkcja zwracajaca grafik pracy dla podanego w argumencie lekarza
@param lekarz - lekarz, dla ktorego chcemy znalezc grafik pracy
@return zwraca mape zawierajaca dni tygodnia wraz z godzinami dostenosci lekarza
*/
	unordered_map<DniTygodnia, GodzinyPracy> zaladujGrafik(shared_ptr <Lekarz> lekarz);
};

