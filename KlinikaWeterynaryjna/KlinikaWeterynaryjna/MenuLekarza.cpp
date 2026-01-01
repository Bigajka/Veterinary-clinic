#include "MenuLekarza.h"
#include "Usluga.h"
#include "SesjaWlascicielaZwierzecia.h"
#include <iostream>
#include "SprawdzaczLiczb.h"

MenuLekarza::MenuLekarza(shared_ptr<SesjaLekarza> sesjaLekarza)
{
    this->sesjaLekarza = sesjaLekarza;
}

OPCJA_POCZATKOWA_LEKARZA MenuLekarza::wyswietlMenuPoczatkowe()
{
    cout << "Wybierz opcje" << endl;
    cout << "1 - Przeglad wizty" << endl;
    cout << "2 - Anuluj wizyte" << endl;
    cout << "3 - Wyjdz" << endl;

    string wybranaOpcja;
    std::cin >> wybranaOpcja;

    if (wybranaOpcja == "1") {
        return OPCJA_POCZATKOWA_LEKARZA::PRZEGLAD_WIZYT;
    }
    else if (wybranaOpcja == "2") {
        return OPCJA_POCZATKOWA_LEKARZA::ANULUJ_WIZYTE;
    }
    else if (wybranaOpcja == "3") {
        return OPCJA_POCZATKOWA_LEKARZA::WYJDZ;
    }
    else {
        return OPCJA_POCZATKOWA_LEKARZA::NIE_WYBRANO_ZADNEJ_OPCJI;
    }
}

void MenuLekarza::przegladWizyt()
{
    shared_ptr<SerwisWizyt> serwisWizyt = sesjaLekarza->getSerwisWizyt();
    shared_ptr<SerwisZwierzat> serwisZwierzat = sesjaLekarza->getSerwisZwierzat();
    shared_ptr<SerwisWlasicielaZwierzecia> serwisWlasiciela = sesjaLekarza->getSerwisWlasicielaZwierzecia();
    shared_ptr<SerwisUslug> serwisUslug = sesjaLekarza->getFabrykaUslug();
    int idLekarza = sesjaLekarza->getLekarz()->getId();
    list<shared_ptr<Wizyta>> wizytyLekarza = serwisWizyt->przegladWizytPoIdLekarza(idLekarza);
  

    if (wizytyLekarza.size() == 0) {
        cout << "Brak wizyt!" << endl;
    }
    else {
        cout << "Twoje zlecenia:" << endl;
        int liczbaWizyt = 0;
        for (auto&& wizyta : wizytyLekarza) {
            liczbaWizyt += 1;
        
            shared_ptr<Zwierze> zwierzak = serwisZwierzat->zaladujZwierzePoId(wizyta->getIdZwierzecia());
            shared_ptr<Usluga> usluga = serwisUslug->znajdzPoTypie(wizyta->getTypUslugi());
            shared_ptr<WlascicielZwierzecia> wlasciciel = serwisWlasiciela->zaladujWlascicielaZwierzeciaPoId(wizyta->getIdWlasciciela());
            if ( zwierzak == NULL || usluga == NULL) {
                continue;
            }

            cout << to_string(liczbaWizyt) << ". ";
            cout << "Data: " << wizyta->getData() << endl;
            cout << "Godzina: " << wizyta->getGodzina() << endl;
            cout << "Wlasiciel: " << wlasciciel->getImie() << " tel: " << wlasciciel->getNumerTelefonu() << endl;
            cout << "Pacjent: " << zwierzak->getImie() << endl;
            cout << "Typ uslugi: " << usluga->getNazwaUslugi() << endl;
            cout << "-----------------------------------------------" << endl;
        }

    }
}

void MenuLekarza::anulujWizyte()
{
    int idLekarza = sesjaLekarza->getLekarz()->getId();
    shared_ptr<SerwisUslug> serwisUslug = sesjaLekarza->getFabrykaUslug();
    shared_ptr<SerwisWizyt> serwisWizyt = sesjaLekarza->getSerwisWizyt();
    list<shared_ptr<Wizyta>> wizytyLekarza = serwisWizyt->przegladWizytPoIdLekarza(idLekarza);
    shared_ptr<SerwisZwierzat> serwisZwierzat = sesjaLekarza->getSerwisZwierzat();
    shared_ptr<SerwisWlasicielaZwierzecia> serwisWlasiciela = sesjaLekarza->getSerwisWlasicielaZwierzecia();

    if (wizytyLekarza.size() == 0) {
        cout << "Brak wizyt!" << endl;
    }
    else {

        unordered_map<int, shared_ptr<Wizyta>> mapaWybranaOpcjaIdWizyty;
        cout << "Twoje wizyty:" << endl;
        int liczbaWizyt = 0;
        for (auto&& wizyta : wizytyLekarza) {
            liczbaWizyt += 1;
            mapaWybranaOpcjaIdWizyty[liczbaWizyt] = wizyta;
            
            shared_ptr<Zwierze> zwierzak = serwisZwierzat->zaladujZwierzePoId(wizyta->getIdZwierzecia());
            shared_ptr<Usluga> usluga = serwisUslug->znajdzPoTypie(wizyta->getTypUslugi());
            shared_ptr<WlascicielZwierzecia> wlasciciel = serwisWlasiciela->zaladujWlascicielaZwierzeciaPoId(wizyta->getIdWlasciciela());
            if (wlasciciel == NULL || zwierzak == NULL || usluga == NULL) {
                continue;
            }

            cout << to_string(liczbaWizyt) << ". ";
            cout << "Data: " << wizyta->getData() << " | ";
            cout << "Godzina: " << wizyta->getGodzina();
            cout << "Wlasiciel: " << wlasciciel->getImie() << " |";
            cout << "Tel. " << wlasciciel->getNumerTelefonu() << " | ";
            cout << "Zwierze: " << zwierzak->getImie() << " | ";
            cout << "Typ uslugi: " << usluga->getNazwaUslugi() << " | " << endl;
        }
        SprawdzaczLiczb sprawdzaczLiczb;
        while (true) {
            cout << endl << "Wybierz wizyte do usiniecia: " << "(Mozliwe opcje: " << to_string(1) << "-" << to_string(liczbaWizyt) << ")" << endl;
            string wybranaOpcjaWizyty;
            cin >> wybranaOpcjaWizyty;

            if (!sprawdzaczLiczb.jestLiczba(wybranaOpcjaWizyty)) {
                cout << "Wybrana opcja nie jest liczba!" << endl;
                continue;
            }

            int intWybranaOpcjaWizyty = stoi(wybranaOpcjaWizyty);

            if (intWybranaOpcjaWizyty >= 1 && intWybranaOpcjaWizyty <= liczbaWizyt) {
                shared_ptr<Wizyta> wizyta = mapaWybranaOpcjaIdWizyty[intWybranaOpcjaWizyty];
                serwisWizyt->anulujWizyte(wizyta->getIdWizyty());
                cout << "Usunieto wizyte: " << to_string(intWybranaOpcjaWizyty) << " " << "z dnia: " << wizyta->getData() << endl;
                break;
            }

        }

    }
}
