#pragma warning(disable : 4996)

#include <iostream>
#include "CzytaczUzytkownikow.h"
#include "SerwisLogowaniaUzytkownika.h"
#include "Uzytkownik.h"
#include "SerwisZwierzat.h"
#include "SesjaWlascicielaZwierzecia.h"
#include "SerwisWlasicielaZwierzecia.h"
#include "SesjaLekarza.h"
#include "CzytaczWlasicielaZwierzecia.h"
#include "TypUzytkownika.h"
#include "MenuLogowania.h"
#include "SerwisLekarza.h"
#include <iomanip>
#include <ctime>
#include <chrono>
#include <sstream>
#include "GodzinyPracy.h"
#include "PlanerWizyt.h"
#include "MenuWlasicielaZwierzecia.h"
#include "SerwisUslug.h"
#include "MenuLekarza.h"
#include <memory>
using namespace std;


int main()
{

    unique_ptr<MenuLogowania> menuLogowania(new MenuLogowania());

    //Czytacze
    shared_ptr<CzytaczUzytkownikow> czytacz(new CzytaczUzytkownikow());
    shared_ptr<CzytaczGrafikuPracy> czytaczGrafikuPracay(new CzytaczGrafikuPracy());
    shared_ptr<CzytaczLekarza> czytaczLekarza(new CzytaczLekarza());
    shared_ptr<CzytaczWizyt> czytaczWizty(new CzytaczWizyt());
    shared_ptr<CzytaczWlasicielaZwierzecia> czytaczWlasicielaZwierzecia(new CzytaczWlasicielaZwierzecia());
    shared_ptr<CzytaczZwierzat> czytaczZwierzat(new CzytaczZwierzat());

    //Serwis
    shared_ptr<SerwisGrafikuPracy> serwisGrafikuPracy(new SerwisGrafikuPracy(czytaczGrafikuPracay));
    shared_ptr<SerwisLogowaniaUzytkownika> serwisLogowaniaUzytkownika(new SerwisLogowaniaUzytkownika(czytacz));
    shared_ptr<SerwisLekarza> serwisLekarza(new SerwisLekarza(czytaczLekarza, serwisLogowaniaUzytkownika));
    shared_ptr<SerwisWizyt> serwisWizyt(new SerwisWizyt(czytaczWizty));
    shared_ptr<SerwisWlasicielaZwierzecia> serwisWlascicielaZwierzecia(new SerwisWlasicielaZwierzecia(czytaczWlasicielaZwierzecia, serwisLogowaniaUzytkownika));
    shared_ptr<SerwisZwierzat> serwisZwierzat( new SerwisZwierzat(czytaczZwierzat));
    shared_ptr<SerwisUslug> fabryka(new SerwisUslug());

    shared_ptr < PlanerWizyt> planer(new PlanerWizyt(serwisGrafikuPracy, serwisWizyt));

    shared_ptr<Uzytkownik> zalogowanyUzytkownik = NULL;

    while (true)
    {
        MenuLogowaniaStatusu status = menuLogowania->wyswietlMenuPoczatkowe();
        if (status == MenuLogowaniaStatusu::WYBRANO_LOGOWANIE) {
            menuLogowania->wyswietMenuLogowania();
           //zalogowanyUzytkownik = serwisLogowaniaUzytkownika->zaloguj(menuLogowania->getLogin(), menuLogowania->getHaslo());
           zalogowanyUzytkownik = serwisLogowaniaUzytkownika->zaloguj("pacjent1@gmail.com", "haslo1234");
           //zalogowanyUzytkownik = serwisLogowaniaUzytkownika->zaloguj("dr.janusz@gmail.com","haslo123");
            break;
        }
        else if (status == MenuLogowaniaStatusu::WYBRANO_WYSJSCIE) {
            return 0;
        }
        else if (status == MenuLogowaniaStatusu::BLAD_WYBRANEJ_OPCJI) {

        }
    }

    if (zalogowanyUzytkownik->getId() == Uzytkownik::ID_DLA_NIEZNANEGO_UZYTKOWNIKA) {
        std::cout << "Nie ma takiego uzytkownika!\n";
        return 0;
    }

    if (zalogowanyUzytkownik->getTypUzytkownika() == TypUzytkownika::LEKARZ) {
        shared_ptr<Lekarz> lekarz = serwisLekarza->zaladujLekarza(zalogowanyUzytkownik);
        shared_ptr<SesjaLekarza> sesjaLekarza = shared_ptr<SesjaLekarza>(new SesjaLekarza(lekarz, serwisWizyt, serwisZwierzat, fabryka, serwisWlascicielaZwierzecia));


        unique_ptr<MenuLekarza> menu( new MenuLekarza(sesjaLekarza));
        while (true)
        {
            OPCJA_POCZATKOWA_LEKARZA opcja = menu->wyswietlMenuPoczatkowe();

            if (opcja == OPCJA_POCZATKOWA_LEKARZA::PRZEGLAD_WIZYT) {
                menu->przegladWizyt();
            }
            else if (opcja == OPCJA_POCZATKOWA_LEKARZA::ANULUJ_WIZYTE) {
                menu->anulujWizyte();
            }
            else if (opcja == OPCJA_POCZATKOWA_LEKARZA::WYJDZ) {
                break;
            }
        }
    }
    else if (zalogowanyUzytkownik->getTypUzytkownika() == TypUzytkownika::WLASCICIEL_ZWIERZECIA) {
        vector<shared_ptr<Zwierze>> zwierzeta = serwisZwierzat->zaladujZwierzetaDlaWlasciciela(zalogowanyUzytkownik->getId());

        shared_ptr<WlascicielZwierzecia> wlasiciel = serwisWlascicielaZwierzecia->zaladujWlascicielaZwierzecia(zalogowanyUzytkownik);
        shared_ptr<SesjaWlascicielaZwierzecia> sesja( new SesjaWlascicielaZwierzecia(wlasiciel, zwierzeta));

        shared_ptr<MenuWlasicielaZwierzecia> menu( new MenuWlasicielaZwierzecia(sesja, planer, fabryka, serwisLekarza, serwisWizyt, serwisZwierzat));

        while (true)
        {
            vector<shared_ptr<Zwierze>> noweZwierzetaPoDodaniu = serwisZwierzat->zaladujZwierzetaDlaWlasciciela(zalogowanyUzytkownik->getId());
            sesja->odswiezZwierzeta(noweZwierzetaPoDodaniu);
            OPCJA_POCZATKOWE_WLASICIELA opcja = menu->wyswietlMenuPoczatkowe();
            if (opcja == OPCJA_POCZATKOWE_WLASICIELA::ZAPLANUJ_WIZYTE) {
                OPCJA_PLANOWANIA_WIZYTY opcjaPlanowaniaWizty = menu->wyswietlMenuDoPlanowaniaWizyty();
                if (opcjaPlanowaniaWizty == OPCJA_PLANOWANIA_WIZYTY::WYBRANO_ZWIERZAKA) {
                    OPCJA_USLUGI wybranaOpcjaUslugi = menu->wswietlMenuUslug();
                    if (wybranaOpcjaUslugi == OPCJA_USLUGI::WYBRANO_USLUGE) {
                        menu->wyswietlMenuWyboruTerminu();
                    }
                    else if (wybranaOpcjaUslugi == OPCJA_USLUGI::BLEDNA_OPCJA) {

                    }
                    else if (wybranaOpcjaUslugi == OPCJA_USLUGI::USLUGA_POZA_ZAKRESEM) {

                    }
                }
                else if (opcjaPlanowaniaWizty == OPCJA_PLANOWANIA_WIZYTY::BLEDNA_OPCJA_WIZYTY) {

                }
            }
            else if (opcja == OPCJA_POCZATKOWE_WLASICIELA::PRZEGLAD_WIZYT) {
                menu->wyswieltWizyty();
            }
            else if (opcja == OPCJA_POCZATKOWE_WLASICIELA::DODAJ_ZWIERZAKA) {
                menu->dodajZwierzaka();
            }
            else if (opcja == OPCJA_POCZATKOWE_WLASICIELA::ANULUJ_WIZYTE) {
                menu->wyswietlAnulowanieWizyty();
            }
            else if (opcja == OPCJA_POCZATKOWE_WLASICIELA::EDYCJA_ZWIERZAKA) {
                menu->edycjaZwierzat();
            }
            else if (opcja == OPCJA_POCZATKOWE_WLASICIELA::WYJDZ) {
                break;
            }

        }
    }

    return 0;
}

