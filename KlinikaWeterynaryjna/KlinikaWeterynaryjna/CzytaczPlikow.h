/**
@file CzytaczPlikow.h
*/
#pragma once
#include <vector>
#include <string>

using namespace std;
/**
@class CzytaczPlikow
@brief Klasa bazowa do czytania pliku, po ktorej dziedzicza inne klasy, ktore musza zaimplementowac funkcje podajNazwePliku
*/
class CzytaczPlikow {

private:
/**
@brief Funkcja zapisuje cala zawartosc pliku do zmiennej.
@return Cala zawartosc pliku jako typ string
@param plik
*/
	string zapiszZawartoscPlikuDoZmiennej(ifstream& plik);
/**
@brief Funkcja zwracajajaca indeks ostatniej kolumny
Ta funkcja jest potrzebna do przetworzenia pliku, ktory jest podzielony na kolummny separatorem |
@return Indeks ostatniej kolumny
@param caly wiersz z pliku
*/
	int znajdzIndeksOstatniejKolumny(string& calyTekst);
/**
@brief Funkcja zwracajaca srodkowej kolumny
Funkcja ta jest potrzebna do znalezienia indeksu kolumny, kota nei jest pierwsza i ostatnia.
@return sciezka do pliku zaspiana w typie tekstowym (String)
@param n- liczba wszystkich kolumn w wierszu
@param calyTekst- caly wiersz z pliku
*/
	int znajdzWystapienieSrodkowejKolumny(string& calyTekst, int n);

public:
/**
@brief Funkcja zwracajajaca cala zawartosc pliku
@return Zawartosc calego pliku
*/
	string wczytajPlik();
/**
@brief Funkcja dopisujaca do pliku nowy wiersz
@param nowy wiersz, ktory zosatnie dopisany do istniejacego pliku
*/
	void dopiszDoPliku(string& nowyWiersz);
/**
@brief Funkcja wirtualna, ktora musza zaimplementowac klasy, ktore po niej dziedzicza 
Funkcja ta musi zwracac sciezke do pliku
@return sciezka do pliku
*/
	virtual string podajNazwePliku() = 0;
/**
@brief Funkcja zamienijaca cala zawartosc pliku na wektor typu string
@return Wektor typu string. Kazdy element kolekcji wektora reprezentuje dany wiersz. Np. pierwszy element bedzie pierwszym wierszem w pliku.
@param tresc calego pliku
*/
	vector<string> zmaienNaWiersze(string& trescPliku);
/**
@brief Funkcja zwracajajaca tekst z danej kolumny
Np. 
string tekst = "abc|def"
getPozycjaTextu(tekst, 0) -> zwroci abc
getPozycjaTextu(tekst, 1) -> zwroci def
@return Tekst z danej kolumny
@param calyTekst - caly wiersz z pliku
@param pozycja - indeks pozycji, ktorej chcemy wyciagnac dany tekst
*/
	string getPozycjaTextu(string calyTekst, int pozycja);
/**
@brief Funkcja, kora usuwa dany wiersz po danym id
@param indeksID - indeks kolumy, z ktorej chcemy usunac dana wartosc
@param id - numer ktory ma zostac usuniety
@param czyJestUnikalny - false jesli jest szansa, ze id o takiej samej wartosci wystpuje wiecej niz raz w pliku. True jesli to id jest unikalne w ramach jednego pliku 
*/	
	void usunWieszPoId(int indeksId, int id, bool czyJestUnikalny);
/**
@brief Funkcja zwracajaca pozycje danego wiersza z podanego wektroa stringow
@return Indeks wiersza
@param wiersze - wektor wierszy 
@param wiersz - tekst, ktorego pozycje chcemy znalezc w wektorze wierszy
*/
	int getPozycjaWiersza(vector<string> wiersze, string wiersz);
/**
@brief Funkcja zapisujaca do pliku w dany wektor stringow
@param wektor - wektor stringow, w ktorym znajduje sie tresc do zapisania do pliku
@param nazwaPliku - nazwa pliku, do kotrego chcemy zapisac caly tekst
*/	
	void zapiszDoPliku(const vector<string>& wektor, const string& nazwaPliku);
/**
@brief Funkcja zwracajaca kolejne id, ktore mozemy uzyc przy zapisnie do pliku
Np. przykladowy plik
1|a
2|b
3|c

int getNastepneId(0); -> zwroci wartosc 4 - bedzie to kolejne ID, ktore mozna uzyc przy zapisie kolejnego wiersza

@return Kolejne dostepne ID
@param indeksId - indeks kolumny, dal ktorego chcemy znalezc kolejne ID
*/	
	int getNastepneId(int indeksId);
};

