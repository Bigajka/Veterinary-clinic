#include "Kot.h"

Kot::Kot(int id, int wiek, Plec plec, int liczbaNog, std::string imie, int idWlasciciela, std::string umaszczenie, std::string kolor, int wagaWGramach) :
	Zwierze(id, wiek, plec, liczbaNog, imie, idWlasciciela, umaszczenie, kolor, wagaWGramach) {
};

string Kot::dzwiek() {
	return "Miauuu";
}

string Kot::getWaga() {
	return to_string(wagaWGramach / 1000) + " kg";
}