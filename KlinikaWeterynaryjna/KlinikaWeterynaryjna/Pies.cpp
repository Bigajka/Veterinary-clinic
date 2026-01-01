#include "Pies.h"

Pies::Pies(int idZwierzecia, int wiek, Plec plec, int liczbaNog, string imie, int idWlasciciela, string umaszczenie, string kolor, int wagaWGramach) :
	Zwierze(idZwierzecia, wiek, plec, liczbaNog, imie, idWlasciciela, umaszczenie, kolor, wagaWGramach) {
};

string Pies::dzwiek() {
	return "Hauu hauu";
}

string Pies::getWaga() {
	return to_string(wagaWGramach / 1000) + " kg";
}