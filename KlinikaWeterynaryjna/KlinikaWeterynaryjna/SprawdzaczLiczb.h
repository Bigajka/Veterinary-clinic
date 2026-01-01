/**
@file SprawdzaczLiczb.h
*/
#pragma once
#include <string>
using namespace std;

/**
@class SprawdzaczLiczb
@brief Klasa odpowiedzialna za sprawdzenie czy to co jest wprowadzane jest liczba
*/
class SprawdzaczLiczb
{

public:
/**	
@brief Funkcja sprawdzjaca czy podana fraza jest liczba
@param tekst - wprowadzony tekst do sprawdzenia
@return true jest liczba
*/
    bool jestLiczba(const string& tekst);
};

