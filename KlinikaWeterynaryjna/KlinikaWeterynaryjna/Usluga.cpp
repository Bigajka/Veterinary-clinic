#include "Usluga.h"


Usluga::Usluga(int cena, std::string nazwaUslugi, std::string typUslugi):
	cena(cena), nazwaUslugi(nazwaUslugi), typUslugi(typUslugi) {
}


int Usluga::getCena() {
	return cena;
}

string Usluga::getTypUslugi()
{
	return typUslugi;
}

std::string Usluga::getNazwaUslugi() {

	return nazwaUslugi;
}