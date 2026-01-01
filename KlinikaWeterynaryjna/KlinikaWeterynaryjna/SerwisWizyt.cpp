#include "SerwisWizyt.h"

#include "StatusWizyty.h"
#include "Wizyta.h"


SerwisWizyt::SerwisWizyt(shared_ptr<CzytaczWizyt> czytaczWizyt)
{
	this->czytaczWizyt = czytaczWizyt;
}

StatusWizyty SerwisWizyt::zarezerujWizyte(Wizyta wizyta)
{
	string tekst = wizyta.zamieNaTekst();
	czytaczWizyt->dopiszDoPliku(tekst);
	return StatusWizyty::POTWIERDZONA;
}

StatusWizyty SerwisWizyt::anulujWizyte(int idWizyty)
{
	czytaczWizyt->usunWieszPoId(idWizytyIndeks, idWizyty, true);
	return StatusWizyty::NIEPOTWIERDZONA;
}

StatusWizyty SerwisWizyt::anulujWizyteDlaZwierzaka(int idZwierzaka)
{
	czytaczWizyt->usunWieszPoId(idZwierzeciaIndeks, idZwierzaka, false);
	return StatusWizyty::NIEPOTWIERDZONA;
}

list<shared_ptr<Wizyta>> SerwisWizyt::przegladWizytPoIdLekarza(int id) {
	string calyPlik = czytaczWizyt->wczytajPlik();
	vector <string> wizytyWiesze = czytaczWizyt->zmaienNaWiersze(calyPlik);
	list<shared_ptr<Wizyta>> wizyty;

	for (auto wizytyWiesz : wizytyWiesze) {

		string idLekarzaTekst = czytaczWizyt->getPozycjaTextu(wizytyWiesz, idLekarzaIndeks);
		int idLekarza = stoi(idLekarzaTekst);
		

		if (id == idLekarza) {
			string dzienWizytyTekst = czytaczWizyt->getPozycjaTextu(wizytyWiesz, dzienWizytyIndeks);
			int dzienWizyty = stoi(dzienWizytyTekst);

			string miesiacWizytyTekst = czytaczWizyt->getPozycjaTextu(wizytyWiesz, miesiacWizytyIndeks);
			int miesiacWizty = stoi(miesiacWizytyTekst);

			string rokWizytyTekst = czytaczWizyt->getPozycjaTextu(wizytyWiesz, rokWizytyIndeks);
			int rokWizyty = stoi(rokWizytyTekst);

			string idWizytyTekst = czytaczWizyt->getPozycjaTextu(wizytyWiesz, idWizytyIndeks);
			int idWizty = stoi(idWizytyTekst);

			string idLekarzaTekst = czytaczWizyt->getPozycjaTextu(wizytyWiesz, idLekarzaIndeks);
			int idLekarza = stoi(idLekarzaTekst);

			string idZwierzeciaTekst = czytaczWizyt->getPozycjaTextu(wizytyWiesz, idZwierzeciaIndeks);
			int idZwierzecia = stoi(idZwierzeciaTekst);

			string godzinaWizytyTekst = czytaczWizyt->getPozycjaTextu(wizytyWiesz, godzinaWizytyIndeks);
			int godzinaWizyty = stoi(godzinaWizytyTekst);

			string idWlasicielaZwierzeciaTekst = czytaczWizyt->getPozycjaTextu(wizytyWiesz, idWlasicielaZwierzeciaIndeks);
			int idWlascicela = stoi(idWlasicielaZwierzeciaTekst);

			string typUslugiTekst = czytaczWizyt->getPozycjaTextu(wizytyWiesz, typUslugiIndeks);

			DataGodzinaWizyty dataGodzinaWizty = DataGodzinaWizyty(godzinaWizyty, dzienWizyty, miesiacWizty, rokWizyty);
			shared_ptr<Wizyta> wizyta(new Wizyta(dataGodzinaWizty, idWizty, idWlascicela, idZwierzecia, idLekarza, typUslugiTekst));
			wizyty.push_back(wizyta);
		}
	}
	return wizyty;
}

list<shared_ptr<Wizyta>> SerwisWizyt::przegladWizytPoIdWlasiciela(int idWlasicielZwierzecia)
{
	string calyPlik = czytaczWizyt->wczytajPlik();
	vector <string> wizytyWiesze = czytaczWizyt->zmaienNaWiersze(calyPlik);
	list<shared_ptr<Wizyta>> wizyty;

	for (auto wizytyWiesz : wizytyWiesze) {
		bool czyPoprawnyWiersz = wizytyWiesz.find_first_not_of(" \t\n\v\f\r") != std::string::npos;
		if (!czyPoprawnyWiersz) {
			continue;
		}
		string idWlasicielaZwierzeciaTekst = czytaczWizyt->getPozycjaTextu(wizytyWiesz, idWlasicielaZwierzeciaIndeks);
		if (idWlasicielaZwierzeciaTekst == "") {
			continue;
		}
		int idWlascicela = stoi(idWlasicielaZwierzeciaTekst);

		if (idWlascicela == idWlasicielZwierzecia) {
			string dzienWizytyTekst = czytaczWizyt->getPozycjaTextu(wizytyWiesz, dzienWizytyIndeks);
			int dzienWizyty = stoi(dzienWizytyTekst);

			string miesiacWizytyTekst = czytaczWizyt->getPozycjaTextu(wizytyWiesz, miesiacWizytyIndeks);
			int miesiacWizty = stoi(miesiacWizytyTekst);

			string rokWizytyTekst = czytaczWizyt->getPozycjaTextu(wizytyWiesz, rokWizytyIndeks);
			int rokWizyty = stoi(rokWizytyTekst);

			string idWizytyTekst = czytaczWizyt->getPozycjaTextu(wizytyWiesz, idWizytyIndeks);
			int idWizty = stoi(idWizytyTekst);

			string idLekarzaTekst = czytaczWizyt->getPozycjaTextu(wizytyWiesz, idLekarzaIndeks);
			int idLekarza = stoi(idLekarzaTekst);

			string idZwierzeciaTekst = czytaczWizyt->getPozycjaTextu(wizytyWiesz, idZwierzeciaIndeks);
			int idZwierzecia = stoi(idZwierzeciaTekst);

			string godzinaWizytyTekst = czytaczWizyt->getPozycjaTextu(wizytyWiesz, godzinaWizytyIndeks);
			int godzinaWizyty = stoi(godzinaWizytyTekst);

			string typUslugiTekst = czytaczWizyt->getPozycjaTextu(wizytyWiesz, typUslugiIndeks);

			DataGodzinaWizyty dataGodzinaWizty = DataGodzinaWizyty(godzinaWizyty, dzienWizyty, miesiacWizty, rokWizyty);
			shared_ptr<Wizyta> wizyta( new Wizyta(dataGodzinaWizty, idWizty, idWlascicela, idZwierzecia, idLekarza, typUslugiTekst));
			wizyty.push_back(wizyta);
		}
	}
	return wizyty;
}

list<shared_ptr<Wizyta>> SerwisWizyt::zaladujWizytyDlaDaty(int rok, int miesiac, int dzien)
{
	string calyPlik = czytaczWizyt->wczytajPlik();
	vector <string> wizytyWiesze = czytaczWizyt->zmaienNaWiersze(calyPlik);
	list<shared_ptr<Wizyta>> wizyty;

	for (auto wizytyWiesz : wizytyWiesze) {
		string dzienWizytyTekst = czytaczWizyt->getPozycjaTextu(wizytyWiesz, dzienWizytyIndeks);
		int dzienWizyty = stoi(dzienWizytyTekst);

		string miesiacWizytyTekst = czytaczWizyt->getPozycjaTextu(wizytyWiesz, miesiacWizytyIndeks);
		int miesiacWizty = stoi(miesiacWizytyTekst);

		string rokWizytyTekst = czytaczWizyt->getPozycjaTextu(wizytyWiesz, rokWizytyIndeks);
		int rokWizyty = stoi(rokWizytyTekst);

		if (rok == rokWizyty && miesiac == miesiacWizty && dzien == dzienWizyty) {
			string idWizytyTekst = czytaczWizyt->getPozycjaTextu(wizytyWiesz, idWizytyIndeks);
			int idWizty = stoi(idWizytyTekst);

			string idLekarzaTekst = czytaczWizyt->getPozycjaTextu(wizytyWiesz, idLekarzaIndeks);
			int idLekarza = stoi(idLekarzaTekst);

			string idWlasicielaZwierzeciaTekst = czytaczWizyt->getPozycjaTextu(wizytyWiesz, idWlasicielaZwierzeciaIndeks);
			int idWlascicela = stoi(idWlasicielaZwierzeciaTekst);

			string idZwierzeciaTekst = czytaczWizyt->getPozycjaTextu(wizytyWiesz, idZwierzeciaIndeks);
			int idZwierzecia = stoi(idZwierzeciaTekst);

			string godzinaWizytyTekst = czytaczWizyt->getPozycjaTextu(wizytyWiesz, godzinaWizytyIndeks);
			int godzinaWizyty = stoi(godzinaWizytyTekst);

			string typUslugiTekst = czytaczWizyt->getPozycjaTextu(wizytyWiesz, typUslugiIndeks);

			DataGodzinaWizyty dataGodzinaWizty = DataGodzinaWizyty(godzinaWizyty, dzienWizyty, miesiacWizty, rokWizyty);
			shared_ptr<Wizyta> wizyta( new Wizyta(dataGodzinaWizty, idWizty, idWlascicela, idZwierzecia, idLekarza, typUslugiTekst));
			wizyty.push_back(wizyta);
		}
	}

	return wizyty;
}

int SerwisWizyt::getNastepneId()
{
	return czytaczWizyt->getNastepneId(idWizytyIndeks);
}
