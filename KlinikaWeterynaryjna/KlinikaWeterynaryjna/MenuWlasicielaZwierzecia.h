/**
@file MenuWlascicielaZwierzecia.h
*/
#pragma once
#include "SesjaWlascicielaZwierzecia.h"
#include "PlanerWizyt.h"
#include "SerwisLekarza.h"
#include "SerwisUslug.h"
#include "SerwisZwierzat.h"
#include "SerwisWizyt.h"

/**
@enum OPCJA_POCZATKOWE_WLASICIELA
@brief Dostepne opcje logowania dostepne po wyborze typu uzytkownika (wlasciciel zwierzecia)
*/
enum OPCJA_POCZATKOWE_WLASICIELA
{
	ZAPLANUJ_WIZYTE, PRZEGLAD_WIZYT, ANULUJ_WIZYTE, WYJDZ, DODAJ_ZWIERZAKA, NIE_WYBRANO_ZADNEJ_OPCJI, EDYCJA_ZWIERZAKA
};

/**
@enum OPCJA_PLANOWANIA_WIZYTY
@brief Dostepne opcje logowania dostepne po wyborze ZAPLANUJ_WIZYTE
*/
enum OPCJA_PLANOWANIA_WIZYTY {
	WYBRANO_ZWIERZAKA, BLEDNA_OPCJA_WIZYTY
};

/**
@enum OPCJA_USLUGI
@brief Dostepne opcje logowania dostepne po wyborze ZAPLANUJ_WIZYTE -> WYBIERZ_ZWIERZAKA
*/
enum OPCJA_USLUGI {
	WYBRANO_USLUGE, BLEDNA_OPCJA, USLUGA_POZA_ZAKRESEM
};

/**
@enum OPCJA_TERMINU_WIZYTY
@brief Dostepne opcje logowania dostepne po wyborze ZAPLANUJ_WIZYTE -> WYBIERZ_ZWIERZAKA -> WYBRANO_ZWIERZE
*/
enum class OPCJA_TERMINU_WIZYTY {
	WYBRANO_TERMIN, BLEDNA_OPCJA_TERMINU, TERMIN_POZA_ZAKRESEM
};

/**
@class MenuWlasicielaZwierzecia
@brief Klasa opisujaca cale menu wlascicela zwierzecia
*/
class MenuWlasicielaZwierzecia
{
private:
	shared_ptr<SesjaWlascicielaZwierzecia> sesja;
	shared_ptr<PlanerWizyt> planer;
	shared_ptr<SerwisUslug> serwisUslug;
	shared_ptr<SerwisLekarza> serwisLekarza;
	shared_ptr<SerwisWizyt> serwisWizyt;
	shared_ptr<SerwisZwierzat> serwisZwierzat;
public:
/**
@brief Konstruktor argumentowy, ustawiajacy sesje, planner, serwis uslug, serwis lekarza, serwis zwierzat, serwis wizyt
*/
	MenuWlasicielaZwierzecia(shared_ptr<SesjaWlascicielaZwierzecia> sesja, shared_ptr<PlanerWizyt> planer, shared_ptr<SerwisUslug> serwisUslug, shared_ptr<SerwisLekarza> serwisLekarza, shared_ptr<SerwisWizyt> serwisWizyt, shared_ptr<SerwisZwierzat> serwisZwierzat);
/**	
@brief Funkcja wyswietlajaca menu poczatkowe dla wlasciciela zwierzecia
@return zwraca 6 dostepnych opcji menu
*/
OPCJA_POCZATKOWE_WLASICIELA wyswietlMenuPoczatkowe();
/**	
@brief Funkcja wyswietla menu do planowania wizyty
Wyswietlaja sie wszystkie zwierzeta jakie mozemy wybrac
@return zwraca wybrana opcje dla planowania wizyty
*/
	OPCJA_PLANOWANIA_WIZYTY wyswietlMenuDoPlanowaniaWizyty();
/**	
@brief Funkcja wyswietlajaca wszytskie uslugi dla danego zwierzaka
@return  zwraca wybrana opcje uslugi
*/	
	OPCJA_USLUGI wswietlMenuUslug();
/**	
@brief Funkcja wyswietlajaca menu wyboru terminu
Najpierw wybieramy jeden miesiac z 3/4 podanych, nastepnie dzien, kolejno odpowiedni blok godzinowy z wybranym lekarzem, ktory nas interesuje
@return zwraca wybrany termin wizyty przez wlasciciela zwierzaka
*/	
	OPCJA_TERMINU_WIZYTY wyswietlMenuWyboruTerminu();
/**	
@brief Funkcja wyswietlajaca wszytskie wizyty, ktore mozemy anulowac
*/
	void wyswietlAnulowanieWizyty();
/**	
@brief Funkcja wyswietlajaca wizyty dla wlasciceila, dla wszytskich jego zwierzat
*/
	void wyswieltWizyty();
/**	
@brief Funkcja wyswietlajaca menu dodania zwierzaka
Wybieramy imie, typ, kolor, umaszczenie, wiek, wage (w gramach), plec
*/
	void dodajZwierzaka();
/**	
@brief Funkcja wyswietlajaca menu edycji zwierzaka (jego imie lub wage)
*/
	void edycjaZwierzat();
};