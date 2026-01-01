#include "Waz.h"


Waz::Waz(int idZwierzecia,int wiek, Plec plec, int liczbaNog, std::string imie, int idWlasciciela, std::string umaszczenie, std::string kolor, int wagaWGramach) :
	Zwierze(idZwierzecia, wiek, plec, liczbaNog, imie, idWlasciciela, umaszczenie, kolor, wagaWGramach) {
};

string Waz::dzwiek() {
	return "Ssssss";
}

string Waz::getWaga() {
	return to_string(wagaWGramach) + " g";
}