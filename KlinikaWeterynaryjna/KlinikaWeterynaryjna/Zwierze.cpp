#include "Zwierze.h"
#include "Pies.h"
#include "Pajak.h"
#include "Kanarek.h"
#include "Waz.h"
#include "Kot.h"
#include "Plec.h"

int Zwierze::getId()
{
    return id;
}

int Zwierze::getWiek()
{
    return wiek;
}

Plec Zwierze::getPlec()
{
    return plec;
}

int Zwierze::getliczaNog()
{
    return liczbaNog;
}

std::string Zwierze::getImie()
{
    return imie;
}

void Zwierze::setImie(string imie)
{
    this->imie = imie;
}

int Zwierze::getIdWlasciciela()
{
    return idWlasciciela;
}

std::string Zwierze::getUmaszczenie()
{
    return umaszczenie;
}

std::string Zwierze::getKolor()
{
    return kolor;
}

void Zwierze::setWagaWGramach(int wagaWGramach)
{
    this->wagaWGramach = wagaWGramach;
}


Zwierze::Zwierze(int id, int wiek, Plec plec, int liczbaNog, string imie, int idWlasciciela, 
    string umaszczenie, string kolor, int wagaWGramach): id(id), wiek(wiek), plec(plec), liczbaNog(liczbaNog),
    imie(imie), idWlasciciela(idWlasciciela), umaszczenie(umaszczenie), kolor(kolor), wagaWGramach(wagaWGramach) {
}

string Zwierze::zamienNaTekst() {
    string typZwierzeciaTekst;

    if (Pies* pies = dynamic_cast<Pies*>(this)) {
        typZwierzeciaTekst = "PIES";
    }
    else if (Kot* kot = dynamic_cast<Kot*>(this)) {
        typZwierzeciaTekst = "KOT";
    }
    else if (Kanarek* kanarek = dynamic_cast<Kanarek*>(this)) {
        typZwierzeciaTekst = "KANAREK";
    }
    else if (Waz* waz = dynamic_cast<Waz*>(this)) {
        typZwierzeciaTekst = "WAZ";
    }
    else if (Pajak* pajak = dynamic_cast<Pajak*>(this)) {
        typZwierzeciaTekst = "PAJAK";
    }
    else {

    }

    string plecTeks;
    if (plec == Plec::SAMICA) {
        plecTeks = "Samica";

    }
    else if (plec == Plec::SAMIEC) {
        plecTeks = "Samiec";
    }
    return to_string(id) + "|" + imie + "|" + plecTeks + "|" + to_string(wiek) + "|" + to_string(liczbaNog) + "|" + to_string(idWlasciciela)
        + "|" + umaszczenie + "|" + kolor + "|" + typZwierzeciaTekst + "|" + to_string(wagaWGramach);
}

