#include "GodzinyPracy.h"

GodzinyPracy::GodzinyPracy() {
    this->godzinaRozpoczecia = 0;
    this->minutaRozpoczecia = 0;
    this->godzinaZakonczenia = 0;
    this->minutaZakonczenia = 0;
}

GodzinyPracy::GodzinyPracy(int godzinaRozpoczecia, int minutaRozpoczecia, int godzinaZakonczenia, int minutaZakonczenia) {
    this->godzinaRozpoczecia = godzinaRozpoczecia;
    this->minutaRozpoczecia = minutaRozpoczecia;
    this->godzinaZakonczenia = godzinaZakonczenia;
    this->minutaZakonczenia = minutaZakonczenia;
}

int GodzinyPracy::getGodzinaRozpoczecia() {
    return godzinaRozpoczecia;
}

int GodzinyPracy::getGodzinaZakonczenia() {
    return godzinaZakonczenia;
}

int GodzinyPracy::getMinutaRozpoczecia() {
    return minutaRozpoczecia;
}

int GodzinyPracy::getMinutaZakonczenia() {
    return minutaZakonczenia;
}
/*
* GodzinyPracy godziny1(8, 00, 16, 0);
  GodzinyPracy godziny2(1, 00, 1, 00);
  GodzinyPracy sumaGodzin = godziny1 + godziny2; <- 9:00 i 17:00
*/
GodzinyPracy operator+(GodzinyPracy& godziny1, GodzinyPracy& godziny2) {
    int godzinaRozpoczecia = godziny1.getGodzinaRozpoczecia() + godziny2.getGodzinaRozpoczecia();
    int minutaRozpoczecia = godziny1.getMinutaRozpoczecia() + godziny2.getMinutaRozpoczecia();
    int godzinaZakonczenia = godziny1.getGodzinaZakonczenia() + godziny2.getGodzinaZakonczenia();
    int minutaZakonczenia = godziny1.getMinutaZakonczenia() + godziny2.getMinutaZakonczenia();

    // Jesli minuty przekraczaja 60, dodaj godzine
    if (minutaRozpoczecia >= 60) {
        godzinaRozpoczecia++;
        minutaRozpoczecia -= 60;
    }
    if (minutaZakonczenia >= 60) {
        godzinaZakonczenia++;
        minutaZakonczenia -= 60;
    }

    // Jesli godziny przekraczaja 24, zastosuj modulo 24
    godzinaRozpoczecia %= 24;
    godzinaZakonczenia %= 24;

    // Zwroc nowy obiekt GodzinyPracy
    return GodzinyPracy(godzinaRozpoczecia, minutaRozpoczecia, godzinaZakonczenia, minutaZakonczenia);
}
