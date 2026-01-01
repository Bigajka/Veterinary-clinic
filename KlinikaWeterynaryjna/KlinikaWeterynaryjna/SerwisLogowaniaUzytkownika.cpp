#include "SerwisLogowaniaUzytkownika.h"
#include "Lekarz.h"
#include "TypUzytkownika.h"
#include <memory>

shared_ptr<Uzytkownik> SerwisLogowaniaUzytkownika::zaloguj(string login, string haslo)
{
    const int indeksLoginu = 0;
    const int indeksHasla = 1;
    const int indeksId = 2;
    const int indeksTypu = 3;
    string calyPlik = czytaczUzytkownikow->wczytajPlik();
    vector<string> uzytkownicyTekstVector = czytaczUzytkownikow->zmaienNaWiersze(calyPlik);
    for (auto uzytkownikTekst : uzytkownicyTekstVector) {
        string loginZPliku = czytaczUzytkownikow->getPozycjaTextu(uzytkownikTekst, indeksLoginu);
        string hasloZPliku = czytaczUzytkownikow->getPozycjaTextu(uzytkownikTekst, indeksHasla);
        if (login == loginZPliku && haslo == hasloZPliku) {
            string typ = czytaczUzytkownikow->getPozycjaTextu(uzytkownikTekst, indeksTypu);
            string id = czytaczUzytkownikow->getPozycjaTextu(uzytkownikTekst, indeksId);
            if (typ == "L") {
                return unique_ptr<Uzytkownik>(new Uzytkownik(login, haslo, stoi(id), LEKARZ));
            }
            else if (typ == "W") {
                return unique_ptr< Uzytkownik>(new Uzytkownik(login, haslo, stoi(id), WLASCICIEL_ZWIERZECIA));
            }
            else {

            }
        }
    }
    return unique_ptr< Uzytkownik>(new Uzytkownik("", "", Uzytkownik::ID_DLA_NIEZNANEGO_UZYTKOWNIKA, NIEZNANY_TYP));
}

shared_ptr<Uzytkownik> SerwisLogowaniaUzytkownika::znajdz(string id)
{
    const int indeksLoginu = 0;
    const int indeksHasla = 1;
    const int indeksId = 2;
    const int indeksTypu = 3;
    string calyPlik = czytaczUzytkownikow->wczytajPlik();
    vector<string> uzytkownicyTekstVector = czytaczUzytkownikow->zmaienNaWiersze(calyPlik);
    for (auto uzytkownikTekst : uzytkownicyTekstVector) {
        string idUzytkownika = czytaczUzytkownikow->getPozycjaTextu(uzytkownikTekst, indeksId);

        if (id == idUzytkownika) {
            string loginZPliku = czytaczUzytkownikow->getPozycjaTextu(uzytkownikTekst, indeksLoginu);
            string hasloZPliku = czytaczUzytkownikow->getPozycjaTextu(uzytkownikTekst, indeksHasla);
            string typ = czytaczUzytkownikow->getPozycjaTextu(uzytkownikTekst, indeksTypu);
            string id = czytaczUzytkownikow->getPozycjaTextu(uzytkownikTekst, indeksId);
            if (typ == "L") {
                return  unique_ptr< Uzytkownik>(new Uzytkownik(loginZPliku, hasloZPliku, stoi(id), LEKARZ));
            }
            else if (typ == "W") {
                return  unique_ptr< Uzytkownik>( new Uzytkownik(loginZPliku, hasloZPliku, stoi(id), WLASCICIEL_ZWIERZECIA));
            }
            else {

            }
        }
    }
    return nullptr;
}

SerwisLogowaniaUzytkownika::SerwisLogowaniaUzytkownika(shared_ptr<CzytaczUzytkownikow> czytaczUzytkownikow)
{
    this->czytaczUzytkownikow = czytaczUzytkownikow;
}
