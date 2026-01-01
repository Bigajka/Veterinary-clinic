#include "SerwisLekarza.h"

SerwisLekarza::SerwisLekarza(shared_ptr<CzytaczLekarza> czytaczLekarza, shared_ptr<SerwisLogowaniaUzytkownika> serwisLogowaniaUzytkownika) {
	this->czytaczLekarza = czytaczLekarza;
	this->serwisLogowaniaUzytkownika = serwisLogowaniaUzytkownika;
}

shared_ptr<Lekarz> SerwisLekarza::zaladujLekarza(shared_ptr<Uzytkownik> uzytkownik)
{
	string calyPlik = czytaczLekarza->wczytajPlik();
	vector <string> lekarzTekstWiersze = czytaczLekarza->zmaienNaWiersze(calyPlik);
	for (auto lekarzWiersz : lekarzTekstWiersze) {
		string idLekarzaZPliku = czytaczLekarza->getPozycjaTextu(lekarzWiersz, indeksId);
		int id = stoi(idLekarzaZPliku);
		if (id == uzytkownik->getId()) {
			string imie = czytaczLekarza->getPozycjaTextu(lekarzWiersz, indeksImienia);
			string nazwisko = czytaczLekarza->getPozycjaTextu(lekarzWiersz, indeksNazwiska);
			string specjalizacja = czytaczLekarza->getPozycjaTextu(lekarzWiersz, indeksSpecjalizacji);
			return shared_ptr<Lekarz>(new Lekarz(imie, nazwisko, specjalizacja, *uzytkownik));
		}
	}
		return NULL;
}

shared_ptr<Lekarz> SerwisLekarza::znajdzLekarzaPoId(int idLekarza, list<shared_ptr<Lekarz>> lekarze)
{
	for (auto&& lekarz : lekarze) {
		if (lekarz->getId() == idLekarza) {
			return lekarz;
		}
	}

	return NULL;
}

list<shared_ptr<Lekarz>> SerwisLekarza::zaladujWszystkichLekarzy()
{
	list<shared_ptr<Lekarz>> lista;
	string calyPlik = czytaczLekarza->wczytajPlik();
	vector <string> lekarzTekstWiersze = czytaczLekarza->zmaienNaWiersze(calyPlik);
	for (auto lekarzWiersz : lekarzTekstWiersze) {
		string idLekarzaZPliku = czytaczLekarza->getPozycjaTextu(lekarzWiersz, indeksId);
		string imie = czytaczLekarza->getPozycjaTextu(lekarzWiersz, indeksImienia);
		string nazwisko = czytaczLekarza->getPozycjaTextu(lekarzWiersz, indeksNazwiska);
		string specjalizacja = czytaczLekarza->getPozycjaTextu(lekarzWiersz, indeksSpecjalizacji);
		shared_ptr<Uzytkownik> uzytkownik = serwisLogowaniaUzytkownika->znajdz(idLekarzaZPliku);
		if (uzytkownik != nullptr) {
			lista.push_back(shared_ptr<Lekarz>(new Lekarz(imie, nazwisko, specjalizacja, *uzytkownik.get())));
		}
	
	}
	
	return lista;
}
