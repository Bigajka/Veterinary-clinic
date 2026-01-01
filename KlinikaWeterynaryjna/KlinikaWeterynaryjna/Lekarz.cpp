#include "Lekarz.h"

Lekarz::Lekarz(string imie, string nazwisko, string specjalizacja, Uzytkownik& uzytkownik) : Uzytkownik(uzytkownik)
{
	this->imie = imie;
	this->nazwisko = nazwisko;
	this->specjalizacja = specjalizacja;
}

string Lekarz::getImie()
{
	return this->imie;
}

string Lekarz::getNazwisko()
{
	return this->nazwisko;
}

string Lekarz::getSpecjalizacja()
{
	return this->specjalizacja;
}

bool Lekarz::czyDostepnyWGodzinach(int godzina, DniTygodnia dzienTygodnia)
{
	GodzinyPracy godzinyPracy = dostepnosc[dzienTygodnia];
	return godzina >= godzinyPracy.getGodzinaRozpoczecia() && godzina <= godzinyPracy.getGodzinaZakonczenia() - 1;
}
