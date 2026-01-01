#include <memory>
#include "SerwisWlasicielaZwierzecia.h"
#include "SerwisLogowaniaUzytkownika.h"

SerwisWlasicielaZwierzecia::SerwisWlasicielaZwierzecia(std::shared_ptr<CzytaczWlasicielaZwierzecia> czytaczWlasicielaZwierzecia, std::shared_ptr<SerwisLogowaniaUzytkownika> serwisLogowaniaUzytkownika)
{
	this->czytaczWlasicielaZwierzecia = czytaczWlasicielaZwierzecia;
	this->serwisLogowaniaUzytkownika = serwisLogowaniaUzytkownika;
}

std::shared_ptr<WlascicielZwierzecia> SerwisWlasicielaZwierzecia::zaladujWlascicielaZwierzecia(std::shared_ptr<Uzytkownik> uzytkownik)
{
	string calyPlik = czytaczWlasicielaZwierzecia->wczytajPlik();
	vector<string> wlascicielZwierzeciaTekstVector = czytaczWlasicielaZwierzecia->zmaienNaWiersze(calyPlik);
	for (auto wlascicelZwierzciaTekst : wlascicielZwierzeciaTekstVector) {
		string idTekst = czytaczWlasicielaZwierzecia->getPozycjaTextu(wlascicelZwierzciaTekst, 1);
		int id = stoi(idTekst);
		if (id == uzytkownik->getId()) {
			string imie = czytaczWlasicielaZwierzecia->getPozycjaTextu(wlascicelZwierzciaTekst, 0);
			string miasto = czytaczWlasicielaZwierzecia->getPozycjaTextu(wlascicelZwierzciaTekst, 2);
			string kodPocztowy = czytaczWlasicielaZwierzecia->getPozycjaTextu(wlascicelZwierzciaTekst, 3);
			string ulicaINumerDomu = czytaczWlasicielaZwierzecia->getPozycjaTextu(wlascicelZwierzciaTekst, 4);
			string numerTelefonu = czytaczWlasicielaZwierzecia->getPozycjaTextu(wlascicelZwierzciaTekst, 5);
			return shared_ptr<WlascicielZwierzecia> (new WlascicielZwierzecia(imie, id, miasto, kodPocztowy, ulicaINumerDomu, numerTelefonu, *uzytkownik.get()));
		}
	}

	return NULL;
}

std::shared_ptr<WlascicielZwierzecia> SerwisWlasicielaZwierzecia::zaladujWlascicielaZwierzeciaPoId(int id)
{
	string calyPlik = czytaczWlasicielaZwierzecia->wczytajPlik();
	vector<string> wlascicielZwierzeciaTekstVector = czytaczWlasicielaZwierzecia->zmaienNaWiersze(calyPlik);
	for (auto wlascicelZwierzciaTekst : wlascicielZwierzeciaTekstVector) {
		string idTekst = czytaczWlasicielaZwierzecia->getPozycjaTextu(wlascicelZwierzciaTekst, 1);
		int idWlasciciela = stoi(idTekst);
		if (idWlasciciela == id) {
			string imie = czytaczWlasicielaZwierzecia->getPozycjaTextu(wlascicelZwierzciaTekst, 0);
			string miasto = czytaczWlasicielaZwierzecia->getPozycjaTextu(wlascicelZwierzciaTekst, 2);
			string kodPocztowy = czytaczWlasicielaZwierzecia->getPozycjaTextu(wlascicelZwierzciaTekst, 3);
			string ulicaINumerDomu = czytaczWlasicielaZwierzecia->getPozycjaTextu(wlascicelZwierzciaTekst, 4);
			string numerTelefonu = czytaczWlasicielaZwierzecia->getPozycjaTextu(wlascicelZwierzciaTekst, 5);
			shared_ptr<Uzytkownik> uzytkownik = serwisLogowaniaUzytkownika->znajdz(idTekst);
			return shared_ptr <WlascicielZwierzecia> (new WlascicielZwierzecia(imie, idWlasciciela, miasto, kodPocztowy, ulicaINumerDomu, numerTelefonu, *uzytkownik.get()));
		}
	}

	return NULL;
}
