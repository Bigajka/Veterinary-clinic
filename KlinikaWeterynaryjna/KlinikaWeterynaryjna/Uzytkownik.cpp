#include "Uzytkownik.h"
#include "TypUzytkownika.h"

Uzytkownik::Uzytkownik(string login, string haslo, int id, TypUzytkownika typUzytkownika) {
	this->login = login;
	this->haslo = haslo;
	this->id = id;
	this->typUzytkownika = typUzytkownika;
}

int Uzytkownik::getId() {
	return id;
}

TypUzytkownika Uzytkownik::getTypUzytkownika()
{
	return this->typUzytkownika;
}

string Uzytkownik::zamienNaTekst() {
	string typUzytkownikaTekst;
	if (typUzytkownika == TypUzytkownika::LEKARZ) {
		typUzytkownikaTekst = "L";
	}
	else {
		typUzytkownikaTekst = "W";
	}
	return login + "|" + haslo + "|" + to_string(id) + "|" + typUzytkownikaTekst;
}
