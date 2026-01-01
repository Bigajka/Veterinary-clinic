#include "SerwisZwierzat.h"
#include "Pies.h"
#include "Pajak.h"
#include "Kanarek.h"
#include "Waz.h"
#include "Kot.h"
#include "Plec.h"
#include <iostream>

SerwisZwierzat::SerwisZwierzat(std::shared_ptr<CzytaczZwierzat> czytaczZwierzat)
{
	this->czytaczZwierzat = czytaczZwierzat;
}

std::shared_ptr<Zwierze> SerwisZwierzat::znajdzPoId(int idZwierzecia, vector<std::shared_ptr<Zwierze>> zwierzeta) {
	for  (auto zwierze : zwierzeta) {
		if (zwierze->getId() == idZwierzecia) {
			return zwierze;
		}
	}

	return NULL;
}

vector<shared_ptr<Zwierze>> SerwisZwierzat::zaladujZwierzetaDlaWlasciciela(int idWlasciela)
{
	vector<shared_ptr<Zwierze>> listaZwierzat;
	string calyPlik = czytaczZwierzat->wczytajPlik();
	vector<string> zwierzetaTekstWiersze = czytaczZwierzat->zmaienNaWiersze(calyPlik);
	for (auto zwierzetaWiersz : zwierzetaTekstWiersze) {
		string idWlasicelaZPliku = czytaczZwierzat->getPozycjaTextu(zwierzetaWiersz, indeksIdWlasiciela);
		if (stoi(idWlasicelaZPliku) == idWlasciela) {
			string idZwierzeciaTekst = czytaczZwierzat->getPozycjaTextu(zwierzetaWiersz, indeksId);
			int idZwierzecia = stoi(idZwierzeciaTekst);

			string imie = czytaczZwierzat->getPozycjaTextu(zwierzetaWiersz, indeksImienia);

			string wiekTekst = czytaczZwierzat->getPozycjaTextu(zwierzetaWiersz, indeksWieku);
			int wiek = stoi(wiekTekst);

			string liczbaNogTekst = czytaczZwierzat->getPozycjaTextu(zwierzetaWiersz, indeksIlosciNog);
			int liczbaNog = stoi(liczbaNogTekst);

			string plecTekst = czytaczZwierzat->getPozycjaTextu(zwierzetaWiersz, indeksPlci);

			string wagaWGramachTekst = czytaczZwierzat->getPozycjaTextu(zwierzetaWiersz, indeksWagi);
			int wagaWGramach = stoi(wagaWGramachTekst);

			Plec plec;
			if (plecTekst == "Samica") {
				plec = Plec::SAMICA;
			}
			else if (plecTekst == "Samiec")
			{
				plec = Plec::SAMIEC;
			}

			string umaszczenie = czytaczZwierzat->getPozycjaTextu(zwierzetaWiersz, indeksUmaszczenia);
			string kolor = czytaczZwierzat->getPozycjaTextu(zwierzetaWiersz, indeksKoloru);

			string typTekst = czytaczZwierzat->getPozycjaTextu(zwierzetaWiersz, indeksTypu);
			if (typTekst == "KOT") {
				shared_ptr<Kot> kot(new Kot(idZwierzecia, wiek, plec, liczbaNog, imie, idWlasciela, umaszczenie, kolor, wagaWGramach));
				//cout << kot->dzwiek();
				
				listaZwierzat.push_back(kot);
			}
			else if (typTekst == "PIES") {
				std::shared_ptr<Pies> pies (new Pies(idZwierzecia, wiek, plec, liczbaNog, imie, idWlasciela, umaszczenie, kolor, wagaWGramach));
				listaZwierzat.push_back(pies);
			}
			else if (typTekst == "KANAREK") {
				std::shared_ptr<Kanarek> kanarek (new Kanarek(idZwierzecia, wiek, plec, liczbaNog, imie, idWlasciela, umaszczenie, kolor, wagaWGramach));
				listaZwierzat.push_back(kanarek);
			}
			else if (typTekst == "WAZ") {
				std::shared_ptr<Waz> waz (new Waz(idZwierzecia, wiek, plec, liczbaNog, imie, idWlasciela, umaszczenie, kolor, wagaWGramach));
				listaZwierzat.push_back(waz);
			}
			else if (typTekst == "PAJAK") {
				std::shared_ptr<Pajak> pajak (new Pajak(idZwierzecia, wiek, plec, liczbaNog, imie, idWlasciela, umaszczenie, kolor, wagaWGramach));
				listaZwierzat.push_back(pajak);
			}

		}
	}
	return listaZwierzat;
}

std::shared_ptr<Zwierze> SerwisZwierzat::zaladujZwierzePoId(int id)
{
	
	string calyPlik = czytaczZwierzat->wczytajPlik();
	vector<string> zwierzetaTekstWiersze = czytaczZwierzat->zmaienNaWiersze(calyPlik);
	for (auto zwierzetaWiersz : zwierzetaTekstWiersze) {
		string idZwierzeciaTekst = czytaczZwierzat->getPozycjaTextu(zwierzetaWiersz, indeksId);
		int idZwierzecia = stoi(idZwierzeciaTekst);

		if (idZwierzecia == id) {
			string idZwierzeciaTekst = czytaczZwierzat->getPozycjaTextu(zwierzetaWiersz, indeksId);
			int idZwierzecia = stoi(idZwierzeciaTekst);
			string idWlasicelaZPliku = czytaczZwierzat->getPozycjaTextu(zwierzetaWiersz, indeksIdWlasiciela);
			int idWlasciciela = stoi(idWlasicelaZPliku);
			string imie = czytaczZwierzat->getPozycjaTextu(zwierzetaWiersz, indeksImienia);
			string wiekTekst = czytaczZwierzat->getPozycjaTextu(zwierzetaWiersz, indeksWieku);
			int wiek = stoi(wiekTekst);
			string liczbaNogTekst = czytaczZwierzat->getPozycjaTextu(zwierzetaWiersz, indeksIlosciNog);
			int liczbaNog = stoi(liczbaNogTekst);
			string plecTekst = czytaczZwierzat->getPozycjaTextu(zwierzetaWiersz, indeksPlci);
			Plec plec;
			if (plecTekst == "Samica") {
				plec = Plec::SAMICA;
			}
			else if (plecTekst == "Samiec")
			{
				plec = Plec::SAMIEC;
			}
			string wagaWGramachTekst = czytaczZwierzat->getPozycjaTextu(zwierzetaWiersz, indeksWagi);
			int wagaWGramach = stoi(wagaWGramachTekst);

			string umaszczenie = czytaczZwierzat->getPozycjaTextu(zwierzetaWiersz, indeksUmaszczenia);
			string kolor = czytaczZwierzat->getPozycjaTextu(zwierzetaWiersz, indeksKoloru);

			string typTekst = czytaczZwierzat->getPozycjaTextu(zwierzetaWiersz, indeksTypu);
			if (typTekst == "KOT") {
				return shared_ptr<Kot>(new Kot(idZwierzecia, wiek, plec, liczbaNog, imie, idWlasciciela, umaszczenie, kolor, wagaWGramach));
			}
			else if (typTekst == "PIES") {
				return shared_ptr<Pies>(new Pies(idZwierzecia, wiek, plec, liczbaNog, imie, idWlasciciela, umaszczenie, kolor, wagaWGramach));
			
			}
			else if (typTekst == "KANAREK") {
				return shared_ptr<Kanarek>(new  Kanarek(idZwierzecia, wiek, plec, liczbaNog, imie, idWlasciciela, umaszczenie, kolor, wagaWGramach));
				
			}
			else if (typTekst == "WAZ") {
				return shared_ptr<Waz>(new Waz(idZwierzecia, wiek, plec, liczbaNog, imie, idWlasciciela, umaszczenie, kolor, wagaWGramach));
				
			}
			else if (typTekst == "PAJAK") {
				return shared_ptr<Pajak>(new Pajak(idZwierzecia, wiek, plec, liczbaNog, imie, idWlasciciela, umaszczenie, kolor, wagaWGramach));
				
			}

		}
	}

	return NULL;
}

int SerwisZwierzat::getNastepneId()
{
	return czytaczZwierzat->getNastepneId(indeksId);
}

void SerwisZwierzat::dodaj(shared_ptr<Zwierze> zwierze)
{
	string tekstToZapisu = zwierze->zamienNaTekst();
	czytaczZwierzat->dopiszDoPliku(tekstToZapisu);
}

void SerwisZwierzat::usunZwierzaka(int idZwierzaka)
{
	czytaczZwierzat->usunWieszPoId(indeksId, idZwierzaka, true);
}

void SerwisZwierzat::zaktualizuj(std::shared_ptr<Zwierze> zwierze)
{
	usunZwierzaka(zwierze->getId());
	string tekstZaktualizowaneZwierze = zwierze->zamienNaTekst();
	czytaczZwierzat->dopiszDoPliku(tekstZaktualizowaneZwierze);
}