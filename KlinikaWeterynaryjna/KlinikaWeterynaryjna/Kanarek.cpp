#include "Kanarek.h"

Kanarek::Kanarek(int idZwierzecia, int wiek, Plec plec, int liczbaNog, string imie, int idWlasciciela, string umaszczenie, string kolor, int wagaWGramach) :
	Zwierze(idZwierzecia, wiek, plec, liczbaNog, imie, idWlasciciela, umaszczenie, kolor, wagaWGramach) {
};

string Kanarek::dzwiek() {
	return "Cwir cwir";
}

string Kanarek::getWaga() {
	return to_string(wagaWGramach) + " g";
}
