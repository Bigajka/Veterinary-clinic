#include "Pajak.h"

Pajak::Pajak(int idZwierzecia, int wiek, Plec plec, int liczbaNog, string imie, int idWlasciciela, string umaszczenie, string kolor, int wagaWGramach) :
	Zwierze(idZwierzecia, wiek, plec, liczbaNog, imie, idWlasciciela, umaszczenie, kolor, wagaWGramach) {
};

string Pajak::dzwiek() {
	return "Skr skr";
}

string Pajak::getWaga() {
	return to_string(wagaWGramach) + " g";
}