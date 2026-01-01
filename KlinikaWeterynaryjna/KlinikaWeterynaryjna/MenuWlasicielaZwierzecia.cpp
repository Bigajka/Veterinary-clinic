#pragma warning(disable : 4996)
#include "MenuWlasicielaZwierzecia.h"
#include <iostream>
#include "SerwisUslug.h"
#include "Lekarz.h"
#include "Usluga.h"
#include <cctype>
#include <unordered_map>
#include "WlascicielZwierzecia.h"
#include <list>
#include "Wizyta.h"
#include "SprawdzaczLiczb.h"
#include <memory>
using namespace std;

MenuWlasicielaZwierzecia::MenuWlasicielaZwierzecia(shared_ptr<SesjaWlascicielaZwierzecia> sesja, shared_ptr<PlanerWizyt> planer, shared_ptr<SerwisUslug> serwisUslug, shared_ptr<SerwisLekarza> serwisLekarza, shared_ptr<SerwisWizyt> serwisWizyt, shared_ptr<SerwisZwierzat> serwisZwierzat)
{
    this->planer = planer;
    this->sesja = sesja;
    this->serwisUslug = serwisUslug;
    this->serwisLekarza = serwisLekarza;
    this->serwisZwierzat = serwisZwierzat;
    this->serwisWizyt = serwisWizyt;
}

OPCJA_POCZATKOWE_WLASICIELA MenuWlasicielaZwierzecia::wyswietlMenuPoczatkowe()
{
    cout << "Wybierz opcje" << endl;
    cout << "1 - Dodaj zwierze" << endl;
    cout << "2 - Edycja zwierzaka" << endl;
    cout << "3 - Zaplanuj wizyte" << endl;
    cout << "4 - Przeglad wizyt" << endl;
    cout << "5 - Anuluj wizyte" << endl;
    cout << "6 - Wyjdz" << endl;

    string wybranaOpcja;
    std::cin >> wybranaOpcja;

    if (wybranaOpcja == "1") {
        return OPCJA_POCZATKOWE_WLASICIELA::DODAJ_ZWIERZAKA;
    }
    else if (wybranaOpcja == "2") {
        return OPCJA_POCZATKOWE_WLASICIELA::EDYCJA_ZWIERZAKA;
    }
    else if (wybranaOpcja == "3") {
        return OPCJA_POCZATKOWE_WLASICIELA::ZAPLANUJ_WIZYTE;
    }
    else if (wybranaOpcja == "4") {
        return OPCJA_POCZATKOWE_WLASICIELA::PRZEGLAD_WIZYT;
    }
    else if (wybranaOpcja == "5") {
        return OPCJA_POCZATKOWE_WLASICIELA::ANULUJ_WIZYTE;
    }
    else if (wybranaOpcja == "6") {
        return OPCJA_POCZATKOWE_WLASICIELA::WYJDZ;
    }
    else {
        return OPCJA_POCZATKOWE_WLASICIELA::NIE_WYBRANO_ZADNEJ_OPCJI;
    }
}

OPCJA_PLANOWANIA_WIZYTY MenuWlasicielaZwierzecia::wyswietlMenuDoPlanowaniaWizyty()
{
    vector<shared_ptr<Zwierze>> zwierzeta = sesja->getZwierzeta();
    unordered_map<int, shared_ptr<Zwierze>> mapaZwierzat;
    cout << "Wybierz zwierze:" << endl;
    for (int i = 1; i <= zwierzeta.size(); i++) {
        shared_ptr<Zwierze> zwierze = zwierzeta.at(i - 1);
        mapaZwierzat.insert(pair<int, shared_ptr<Zwierze>>(i, zwierze));
        cout << zwierze->getImie() << " - " << to_string(i) << endl;
    }

    string wybranaOpcja;
    std::cin >> wybranaOpcja;

    int wybranaOpcjaInt = stoi(wybranaOpcja);
    if (wybranaOpcjaInt >= 1 && wybranaOpcjaInt <= zwierzeta.size()) {
        sesja->setWybraneZwierze(mapaZwierzat.at(wybranaOpcjaInt));
        return OPCJA_PLANOWANIA_WIZYTY::WYBRANO_ZWIERZAKA;
    }
    else {
        return OPCJA_PLANOWANIA_WIZYTY::BLEDNA_OPCJA_WIZYTY;
    }
}

OPCJA_USLUGI MenuWlasicielaZwierzecia::wswietlMenuUslug()
{
    vector<shared_ptr<Usluga>> uslugi = serwisUslug->stworzUslugeDlaZwierzaka(sesja->getWybarneZwierze());
    unordered_map<int, shared_ptr<Usluga>> mapaUslug;
    cout << "Wybierz usluge:" << endl;
    for (int i = 1; i <= uslugi.size(); i++) {
        shared_ptr<Usluga> usluga = uslugi.at(i - 1);
        mapaUslug.insert(pair<int, shared_ptr<Usluga>>(i, usluga));
        cout << usluga->getNazwaUslugi() << " - " << to_string(i) << endl;
    }

    string wybranaOpcja;
    std::cin >> wybranaOpcja;

    for (int i = 0; i < wybranaOpcja.length(); i++) {
        if (!isdigit(wybranaOpcja[i])) {
            cout << "Wprowadzo niepoprawna opcje! Wprowadzona opcja zawiera litere" << endl;
            return OPCJA_USLUGI::BLEDNA_OPCJA;
        }
    }
   
    int wybranaOpcjaInt = stoi(wybranaOpcja);
    if (wybranaOpcjaInt >= 1 && wybranaOpcjaInt <= uslugi.size()) {
        shared_ptr<Usluga> wybranaUsluga = mapaUslug.at(wybranaOpcjaInt);
        sesja->setWybranaUsluga(wybranaUsluga);
        cout << "Wybrano usluge: " << wybranaUsluga->getNazwaUslugi()  << endl;
        return OPCJA_USLUGI::WYBRANO_USLUGE; 
    }
    else {
        cout << "Wprowadzo niepoprawna opcje! Wprowadzona opcja nie miesci sie w zakresie opcji" << endl;
        return OPCJA_USLUGI::USLUGA_POZA_ZAKRESEM;
    }
}

OPCJA_TERMINU_WIZYTY MenuWlasicielaZwierzecia::wyswietlMenuWyboruTerminu()
{
    pair<DniTygodnia, time_t> dostapneCzas = planer->zaladujDostepyCzas(time(0));
    pair<string, time_t> ostatniDostepnyCzas = planer->zaladujOstatniaDostepnaDate(dostapneCzas.second, "%Y-%m-%d %H:%M");
    DniTygodnia ostatniDostepnyDzienTygodnia = planer->zamienNaDniTygonida(ostatniDostepnyCzas.second);
    time_t ostatniDzienRezerwacjiZGodzinaZamkniecia = planer->getGodzinaZamknieciaWDniu(ostatniDostepnyDzienTygodnia, ostatniDostepnyCzas.second);
    cout << "Pierwszy mozliwy termin:  " << endl;
    planer->wyswietl(dostapneCzas.second, "%Y-%m-%d %H:%M");
    cout << endl << "Ostatni mozliwy termin: " << endl;
    planer->wyswietl(ostatniDzienRezerwacjiZGodzinaZamkniecia, "%Y-%m-%d %H:%M");


    cout << endl << endl << "Wybierz miesiac:" << endl;
    unordered_map<int, time_t> miesiace = planer->wygenerujMiesiace(dostapneCzas.second, ostatniDzienRezerwacjiZGodzinaZamkniecia);

    for (auto miesiac : miesiace) {
        string miesiacTekst = planer->zamienNaMiesiac(miesiac.second);
        cout << miesiacTekst << " - " << to_string(miesiac.first) << endl;
    }

    while (true)
    {
        string wybranaOpcja;
        cout << "Wybierz miesiac: " << endl;
        cin >> wybranaOpcja;

        int wybranaOpcjaInt = stoi(wybranaOpcja);
        if (wybranaOpcjaInt >= 1 && wybranaOpcjaInt <= miesiace.size()) {
            time_t wybranyMiesiac = miesiace.at(wybranaOpcjaInt);
            tm* tmWybranyMiesiac = localtime(&wybranyMiesiac);
            int wybranyMiesiacInt = tmWybranyMiesiac->tm_mon + 1;
            sesja->setWybranyMiesiac(shared_ptr<pair<int, time_t>>(new pair<int, time_t>(wybranyMiesiacInt, miesiace.at(wybranaOpcjaInt))));
            string rokTekst = planer->zaladujRok(wybranyMiesiac);
            int rok = stoi(rokTekst);
            sesja->setWybranyRok(shared_ptr<pair<int, time_t>>(new pair<int, time_t>(rok, wybranyMiesiac)));
            cout << "Wybrano miesiac: " << planer->zamienNaMiesiac(wybranyMiesiac) << endl;
            break;
        }
        else {
            cout << "Wybrano zly miesiac!" << endl;
        }
    }

    time_t* pWybranyMiesiac = &sesja->getWybranyMiesiac()->second;
    unordered_map<int, time_t> dostepneDni;

    if (planer->czyPierwszDostepnyMiesiac(miesiace, *pWybranyMiesiac))
    {
        int ostatniDzienMiesiaca = planer->ostatniDzienMiesiaca(*pWybranyMiesiac);
        tm* tmWybranyMiesiac = localtime(pWybranyMiesiac);
        planer->wypiszKalendarz(tmWybranyMiesiac->tm_year, tmWybranyMiesiac->tm_mon + 1, tmWybranyMiesiac->tm_mday, ostatniDzienMiesiaca);
        dostepneDni = planer->wygenerujDni(tmWybranyMiesiac->tm_year, tmWybranyMiesiac->tm_mon + 1, tmWybranyMiesiac->tm_mday, ostatniDzienMiesiaca);
    }
    else if (planer->czyOstatniDostepnyMiesiac(miesiace, *pWybranyMiesiac)) {
        tm* tmOstatniDostepnyCzas = localtime(&ostatniDzienRezerwacjiZGodzinaZamkniecia);
        tm* tmWybranyMiesiac = localtime(&ostatniDzienRezerwacjiZGodzinaZamkniecia);
        planer->wypiszKalendarz(tmWybranyMiesiac->tm_year, tmWybranyMiesiac->tm_mon + 1, 0, tmOstatniDostepnyCzas->tm_mday);
        dostepneDni = planer->wygenerujDni(tmWybranyMiesiac->tm_year, tmWybranyMiesiac->tm_mon + 1, 0, tmOstatniDostepnyCzas->tm_mday);
    }
    else {
        int ostatniDzienMiesiaca = planer->ostatniDzienMiesiaca(*pWybranyMiesiac);
        tm* tmWybranyMiesiac = localtime(pWybranyMiesiac);
        planer->wypiszKalendarz(tmWybranyMiesiac->tm_year, tmWybranyMiesiac->tm_mon + 1, 0, ostatniDzienMiesiaca);
        dostepneDni = planer->wygenerujDni(tmWybranyMiesiac->tm_year, tmWybranyMiesiac->tm_mon + 1, 0, ostatniDzienMiesiaca);
    }

    const time_t* pWybranyMiesiacPoAktualizacji = &sesja->getWybranyMiesiac()->second;

    while (true)
    {
        string wybranaOpcja;
        cout << endl << "Wybierz dzien miesiaca: " << endl;
        cout << endl << "Dostepne dni: " << dostepneDni.begin()->first << "-" << (--dostepneDni.end())->first << endl;
        cin >> wybranaOpcja;

        int wybranaOpcjaInt = stoi(wybranaOpcja);

        if (dostepneDni.find(wybranaOpcjaInt) == dostepneDni.end()) {
            cout << "Podano dzien spoza zakrsu" << endl;
        }
        else {
            bool czyJestNiedziela = planer->czyJestDniem(DniTygodnia::Niedziela, dostepneDni[wybranaOpcjaInt]);
            if (czyJestNiedziela) {
                cout << "Wybrano niedziele! Wybierz dzien ponownie!" << endl;
            }
            else {
                cout << "Wybrano dzien: " << wybranaOpcjaInt << endl;
                sesja->setWybranyDzien(shared_ptr<pair<int, time_t>>(new pair<int, time_t>(wybranaOpcjaInt, dostepneDni[wybranaOpcjaInt])));
                break;
            }
        }
    }

    while (true)
    {
        string wybranaOpcja;
        cout << endl << "Wybierz blok godzinowy na wybrany dzien: " << endl;
        list<shared_ptr<Lekarz>> lekarze = serwisLekarza->zaladujWszystkichLekarzy();

        unordered_map<int, unordered_map<int, shared_ptr<Lekarz>>> dostepneBloki = planer->wygenerujBlokiGodzinowe(sesja->getWybranyDzien()->second, lekarze);
        unordered_map<int, int> mapaOpcjaWyboruGodzina;
        cout << "Dostenpne bloki godzinowe:" << endl;
        int i = 0;
        SprawdzaczLiczb sprawdzaczLiczb;
        for (auto dostepneBlok : dostepneBloki) {
            i++;
            cout << to_string(i) << ". ";
            cout << dostepneBlok.first << ":00 ";
            mapaOpcjaWyboruGodzina[i] = dostepneBlok.first;
            if (dostepneBlok.second.size() == 1) {
                cout << "Lekarz: ";
            }
            else {
                cout << "Lekarze: ";
            }

            for (auto lekarz : dostepneBlok.second) {
                cout << lekarz.second->getImie() << " " << lekarz.second->getNazwisko() << ", ";
            }

            cout << endl;


        }

        cout << endl << "Wybierz numer bloku: " << "(Mozliwe opcje: " << to_string(1) << "-" << to_string(i) << ")" << endl;
        cin >> wybranaOpcja;

        if (!sprawdzaczLiczb.jestLiczba(wybranaOpcja)) {
            cout << "Wybrana opcja nie jest liczba!" << endl;
            continue;
        }

        int wybranaOpcjaInt = stoi(wybranaOpcja);

        if (wybranaOpcjaInt >= 1 && wybranaOpcjaInt <= i) {
            cout << "Wybrano opcje: " << wybranaOpcja << endl;
            int wybranaGodzina = mapaOpcjaWyboruGodzina[wybranaOpcjaInt];
            sesja->setWybranaGodzina(wybranaGodzina);
            unordered_map<int, shared_ptr<Lekarz>> dostepniLekarze = dostepneBloki[wybranaGodzina];
            if (dostepniLekarze.size() == 1) {
                sesja->setIdWybranegoLekarza(dostepniLekarze.begin()->first);
            }
            else {
               
                while (true)
                {
                    cout << "Wybierz lekarza:" << endl;
                    int indeksLekarza = 0;
                    unordered_map<int, int> mapaWybranaOpcjaIdLekarza;
                    for (auto&& lekarz : dostepniLekarze) {
                        indeksLekarza++;
                        cout << to_string(indeksLekarza) << ". " << lekarz.second->getImie() << " " << lekarz.second->getNazwisko() << endl;
                        mapaWybranaOpcjaIdLekarza[indeksLekarza] = lekarz.first;
                    }

                    string wybranaOpcjaLekarza;
                    cin >> wybranaOpcjaLekarza;

                    if (!sprawdzaczLiczb.jestLiczba(wybranaOpcjaLekarza)) {
                        cout << "Wybrana opcja nie jest liczba!" << endl;
                        continue;
                    }

                    int intWybranaOpcjaLekarza = stoi(wybranaOpcjaLekarza);

                    if (intWybranaOpcjaLekarza >= 1 && intWybranaOpcjaLekarza <= mapaWybranaOpcjaIdLekarza.size()) {
                        int idLekarza = mapaWybranaOpcjaIdLekarza[intWybranaOpcjaLekarza];
                        shared_ptr<Lekarz> lekarz = dostepniLekarze[idLekarza];
                        cout << "Wybrano lekarza: " << lekarz->getImie() << " " << lekarz->getNazwisko() << endl;
                        sesja->setIdWybranegoLekarza(lekarz->getId());
                        break;
                    }
                    else {
                        cout << "Wybrana opcje spoza zakresu!" << endl;
                        continue;
                    }
                }
            }
            break;
        }
        else {
            cout << "Wybrano zla opcje! Wybierze jeszcze raz " << wybranaOpcja << endl;
            continue;
        }
    }


    if (sesja->czyMoznaUtworzycWizyte()) {
        DataGodzinaWizyty dataGodzinaWizyty = DataGodzinaWizyty(sesja->getWybranaGodzina(), sesja->getWybranyDzien()->first, sesja->getWybranyMiesiac()->first, sesja->getWybranyRok()->first);
        int idWizyty = planer->wygenerujIdWizyty();
        Wizyta wizyta = Wizyta(dataGodzinaWizyty, idWizyty, sesja->getWlasicielZwierzecia()->getId(), sesja->getWybarneZwierze()->getId(), sesja->getIdWybranegoLekarza(), sesja->getWybranaUsluga()->getTypUslugi());
        planer->utworzWizyte(wizyta);
        return OPCJA_TERMINU_WIZYTY::WYBRANO_TERMIN;
    }
    else {
        return OPCJA_TERMINU_WIZYTY::BLEDNA_OPCJA_TERMINU;
    }
   
}

void MenuWlasicielaZwierzecia::wyswieltWizyty()
{
    shared_ptr<WlascicielZwierzecia> wlasiciel = sesja->getWlasicielZwierzecia();
    list<shared_ptr<Wizyta>> wizytyUzytkownika = serwisWizyt->przegladWizytPoIdWlasiciela(wlasiciel->getId());
    list<shared_ptr<Lekarz>> lekarze = serwisLekarza->zaladujWszystkichLekarzy();
    vector<shared_ptr<Zwierze>> zwierzeta = serwisZwierzat->zaladujZwierzetaDlaWlasciciela(wlasiciel->getId());

    if (wizytyUzytkownika.size() == 0) {
        cout << "Brak wizyt!" << endl;
    }
    else {
        cout << "Twoje wizyty:" << endl;
        int liczbaWizyt = 0;
        for (auto&& wizyta : wizytyUzytkownika) {
            liczbaWizyt += 1;
            shared_ptr<Lekarz> lekarz = serwisLekarza->znajdzLekarzaPoId(wizyta->getIdLekarza(), lekarze);
            shared_ptr<Zwierze> zwierzak = serwisZwierzat->znajdzPoId(wizyta->getIdZwierzecia(), zwierzeta);
            shared_ptr<Usluga> usluga = serwisUslug->znajdzPoTypie(wizyta->getTypUslugi());

            if (lekarz == NULL || zwierzak == NULL || usluga == NULL) {
                continue;
            }

            cout << to_string(liczbaWizyt) << ". ";
            cout << "Data: " << wizyta->getData() << endl;
            cout << "Godzina: " << wizyta->getGodzina() << endl;
            cout << "Lekarz: " << lekarz->getImie() << " " << lekarz->getNazwisko() << endl;
            cout << "Zwierze: " << zwierzak->getImie() << endl;
            cout << "Typ uslugi: " << usluga->getNazwaUslugi() << endl;
            cout << "-----------------------------------------------" << endl;
        }
  
    }
}

void MenuWlasicielaZwierzecia::dodajZwierzaka()
{
    string imie;
    string typ;
    string kolor;
    string umaszczenie;
    int wiek;
    int wagaWGramach;
    Plec plec = Plec();
    SprawdzaczLiczb sprawdzaczLiczb;
    while (true)
    {
        cout << endl << "Podaj imie: " << endl;
        string wybierzImie;
        cin >> wybierzImie;

        if (sprawdzaczLiczb.jestLiczba(wybierzImie)) {
            cout << "Imie nie moze zawierac liczb" << endl;
        }
        else {
            imie = wybierzImie;
            break;
        }

    }

    while (true)
    {
        cout << endl << "Wybierz typ: (1-6)" << endl;
        cout << "Dostepne typy: " << endl;
        cout << "1. Kot" << endl;
        cout << "2. Pies" << endl;
        cout << "3. Pajak" << endl;
        cout << "4. Waz" << endl;
        cout << "5. Kanarek" << endl;
        unordered_map<int, string> dostepnOpcjeTypy = { { 1, "KOT" }, {2, "PIES"}, {3, "PAJAK"}, {4, "WAZ"}, {5, "KANAREK"}};
        string wybierzTyp;
        cin >> wybierzTyp;

        if (!sprawdzaczLiczb.jestLiczba(wybierzTyp)) {
            cout << "Typ musi byc liczba" << endl;
        }
        else if (stoi(wybierzTyp) > 0 && stoi(wybierzTyp) <= dostepnOpcjeTypy.size()) {
            typ = dostepnOpcjeTypy[stoi(wybierzTyp)];
            break;
        }
        else {
            cout << "Liczba spoza zakresu! Dozwolony zakres (1-6)" << endl;
        }

    }

    while (true)
    {
        cout << endl << "Wybierz kolor: " << endl;
        string wybierzKolor;
        cin >> wybierzKolor;

        if (sprawdzaczLiczb.jestLiczba(wybierzKolor)) {
            cout << "Kolor nie moze zwierac liczb" << endl;
        }
        else {
            kolor = wybierzKolor;
            break;
        }

    }

    while (true)
    {
        cout << endl << "Wybierz umaszczenie: " << endl;
        string wybierzUmaszczenie;
        cin >> wybierzUmaszczenie;

        if (sprawdzaczLiczb.jestLiczba(wybierzUmaszczenie)) {
            cout << "Umaszczenie nie moze zwierac liczb" << endl;
        }
        else {
            umaszczenie = wybierzUmaszczenie;
            break;
        }

    }

    while (true)
    {
        cout << endl << "Podaj wage (w gramach): " << endl;
        string wybierzWageWGramach;
        cin >> wybierzWageWGramach;

        if (!sprawdzaczLiczb.jestLiczba(wybierzWageWGramach)) {
            cout << "Waga musi byc liczba!" << endl;
        }
        else {
            wagaWGramach = stoi(wybierzWageWGramach);
            break;
        }

    }

    while (true)
    {
        cout << endl << "Wybierz plec" << endl;
        cout << "Dostepne typy: " << endl;
        cout << "1. Samica" << endl;
        cout << "2. Samiec" << endl;
        
        unordered_map<int, Plec> dostepnOpcjeTypy = { { 1, Plec::SAMICA }, {2, Plec::SAMIEC} };
        string wybierzPlec;
        cin >> wybierzPlec;

        if (!sprawdzaczLiczb.jestLiczba(wybierzPlec)) {
            cout << "Plec musi byc liczba" << endl;
        }
        else if (stoi(wybierzPlec) > 0 && stoi(wybierzPlec) <= dostepnOpcjeTypy.size()) {
            plec = dostepnOpcjeTypy[stoi(wybierzPlec)];
            break;
        }
        else {
            cout << "Liczba spoza zakresu! Dozwolony zakres (1-2)" << endl;
        }

    }

    while (true)
    {
        cout << endl << "Podaj wiek" << endl;
       
        string wybierzWiek;
        cin >> wybierzWiek;

        if (!sprawdzaczLiczb.jestLiczba(wybierzWiek)) {
            cout << "Wiek musi byc liczba" << endl;
        }
        else {
            time_t czas = time(nullptr);
            tm* aktualnyCzas = localtime(&czas);
            int intWiek = stoi(wybierzWiek);
            wiek = aktualnyCzas->tm_year + 1900 - intWiek;
            break;
        }
    }

    shared_ptr<Zwierze> zwierze = NULL;
    if (typ == "KOT") {
        zwierze = shared_ptr<Zwierze>(new Kot(serwisZwierzat->getNastepneId(), wiek, plec, 4, imie, sesja->getWlasicielZwierzecia()->getId(), umaszczenie, kolor, wagaWGramach));
    }
    else if (typ == "PIES") {
        zwierze = shared_ptr<Zwierze>(new Pies(serwisZwierzat->getNastepneId(), wiek, plec, 4, imie, sesja->getWlasicielZwierzecia()->getId(), umaszczenie, kolor, wagaWGramach));
    }
    else if (typ == "PAJAK") {
        zwierze = shared_ptr<Zwierze>(new Pajak(serwisZwierzat->getNastepneId(), wiek, plec, 8, imie, sesja->getWlasicielZwierzecia()->getId(), umaszczenie, kolor, wagaWGramach));
    }
    else if (typ == "WAZ") {
        zwierze = shared_ptr<Zwierze>(new Waz(serwisZwierzat->getNastepneId(), wiek, plec, 0, imie, sesja->getWlasicielZwierzecia()->getId(), umaszczenie, kolor, wagaWGramach));
    }
    else if (typ == "KANAREK") {
        zwierze = shared_ptr<Zwierze>(new Kanarek(serwisZwierzat->getNastepneId(), wiek, plec, 2, imie, sesja->getWlasicielZwierzecia()->getId(), umaszczenie, kolor, wagaWGramach));
    }

    if (zwierze != NULL) {
        cout << endl << zwierze->dzwiek() << endl;
        serwisZwierzat->dodaj(zwierze);
        string urodzonyTekst;
        string plecTeskt;
        if (plec == Plec::SAMICA) {
            urodzonyTekst = "Urodzona";
            plecTeskt = "Samica";
        }
        else if (plec == Plec::SAMIEC) {
            urodzonyTekst = "Urodzony";
            plecTeskt = "Samiec";
        }
        cout << "Dodano zwierzaka: " << zwierze->getImie() << " (" << plecTeskt << "), " << urodzonyTekst << ": " << to_string(wiek) << ", " << "Kolor: " << kolor << " Umaszczenie: " << umaszczenie << endl;
    }
}

void MenuWlasicielaZwierzecia::wyswietlAnulowanieWizyty()
{
    shared_ptr<WlascicielZwierzecia> wlasiciel = sesja->getWlasicielZwierzecia();
    list<shared_ptr<Wizyta>> wizytyUzytkownika = serwisWizyt->przegladWizytPoIdWlasiciela(wlasiciel->getId());
    list<shared_ptr<Lekarz>> lekarze = serwisLekarza->zaladujWszystkichLekarzy();
    vector<shared_ptr<Zwierze>> zwierzeta = serwisZwierzat->zaladujZwierzetaDlaWlasciciela(wlasiciel->getId());

    if (wizytyUzytkownika.size() == 0) {
        cout << "Brak wizyt!" << endl;
    }
    else {

        unordered_map<int, shared_ptr<Wizyta>> mapaWybranaOpcjaIdWizyty;
        cout << "Twoje wizyty:" << endl;
        int liczbaWizyt = 0;
        SprawdzaczLiczb sprawdzaczLiczb;
        for (auto&& wizyta : wizytyUzytkownika) {
            liczbaWizyt += 1;
            mapaWybranaOpcjaIdWizyty[liczbaWizyt] = wizyta;
            shared_ptr<Lekarz> lekarz = serwisLekarza->znajdzLekarzaPoId(wizyta->getIdLekarza(), lekarze);
            shared_ptr<Zwierze> zwierzak = serwisZwierzat->znajdzPoId(wizyta->getIdZwierzecia(), zwierzeta);
            shared_ptr<Usluga> usluga = serwisUslug->znajdzPoTypie(wizyta->getTypUslugi());

            if (lekarz == NULL || zwierzak == NULL || usluga == NULL) {
                continue;
            }

            cout << to_string(liczbaWizyt) << ". ";
            cout << "Data: " << wizyta->getData() << " | ";
            cout << "Godzina: " << wizyta->getGodzina();
            cout << "Lekarz: " << lekarz->getImie() << " " << lekarz->getNazwisko() << " | ";
            cout << "Zwierze: " << zwierzak->getImie() << " | ";
            cout << "Typ uslugi: " << usluga->getNazwaUslugi() << " | " << endl;
        }

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

void MenuWlasicielaZwierzecia::edycjaZwierzat()
{
    SprawdzaczLiczb sprawdzaczLiczb;
    shared_ptr<WlascicielZwierzecia> wlasiciel = sesja->getWlasicielZwierzecia();
    vector<shared_ptr<Zwierze>> zwierzeta = serwisZwierzat->zaladujZwierzetaDlaWlasciciela(wlasiciel->getId());
    if (zwierzeta.size() == 0) {
        cout << "Brak zwierzat!" << endl;
        return;
    }


    cout << "Twoje zwierzeta:" << endl;
    unordered_map<int, shared_ptr<Zwierze>> mapaWybranaOpcjaZwierze;
    shared_ptr<Zwierze> wybraneZwierze = NULL;
    int liczbaZwierzat = 0;
    for (auto&& zwierze : zwierzeta) {
        liczbaZwierzat += 1;
        mapaWybranaOpcjaZwierze[liczbaZwierzat] = zwierze;

        cout << to_string(liczbaZwierzat) << ". ";
        cout << "Imie: " << zwierze->getImie() << " | ";
        cout << "Kolor: " << zwierze->getKolor() << " | ";
        cout << "Umaszczenie: " << zwierze->getUmaszczenie() << " | ";
        cout << "Wiek: " << zwierze->getWiek() << " | ";
        cout << "Waga: " << zwierze->getWaga() << " | " << endl;
    }

    while (true) {
        cout << endl << "Wybierz zwierze do edycji: " << "(Mozliwe opcje: " << to_string(1) << "-" << to_string(liczbaZwierzat) << ")" << endl;
        string wybranaOpcjaZwierzecia;
        cin >> wybranaOpcjaZwierzecia;

        if (!sprawdzaczLiczb.jestLiczba(wybranaOpcjaZwierzecia)) {
            cout << "Wybrana opcja nie jest liczba!" << endl;
            continue;
        }

        int intWybranaOpcjaZwierzecia = stoi(wybranaOpcjaZwierzecia);

        if (intWybranaOpcjaZwierzecia >= 1 && intWybranaOpcjaZwierzecia <= liczbaZwierzat) {
            wybraneZwierze = mapaWybranaOpcjaZwierze[intWybranaOpcjaZwierzecia];
            break;
        }
        else {
            cout << "Wybrano opcje spoza zakresu!" << endl;
        }
    }
    bool czyWybranoEdycje = false;
    while (true) {
        cout << "Co chcesz zrobic?" << endl;
        cout << "1. Edycja" << endl;
        cout << "2. Usuniecie" << endl;

        string wybranaOpcja;
        cin >> wybranaOpcja;

        if (!sprawdzaczLiczb.jestLiczba(wybranaOpcja)) {
            cout << "Wybrana opcja nie jest liczba!" << endl;
            continue;
        }

        int intWybranaOpcja = stoi(wybranaOpcja);

        if (intWybranaOpcja >= 1 && intWybranaOpcja <= 2) {
            if (intWybranaOpcja == 1) {
                czyWybranoEdycje = true;
            }
            else if (intWybranaOpcja == 2) {
                czyWybranoEdycje = false;
                serwisZwierzat->usunZwierzaka(wybraneZwierze->getId());
                serwisWizyt->anulujWizyteDlaZwierzaka(wybraneZwierze->getId());
                cout << "Usunieto zwierzaka i jego wizyty!" << endl;
            }
            break;
        }
        else {
            cout << "Wybrano opcje spoza zakresu!" << endl;
        }
    }
   
    if (czyWybranoEdycje) {
        int wybranaOpcjaEdycji = 0;
        while (true) {
            cout << "Co chcesz zaedytowac?" << endl;
            cout << "1. Imie" << endl;
            cout << "2. Waga" << endl;

            string wybranaOpcja;
            cin >> wybranaOpcja;

            if (!sprawdzaczLiczb.jestLiczba(wybranaOpcja)) {
                cout << "Wybrana opcja nie jest liczba!" << endl;
                continue;
            }

            int intWybranaOpcja = stoi(wybranaOpcja);

            if (intWybranaOpcja >= 1 && intWybranaOpcja <= 2) {
                if (intWybranaOpcja == 1) {
                    wybranaOpcjaEdycji = intWybranaOpcja;
                }
                else if (intWybranaOpcja == 2) {
                    wybranaOpcjaEdycji = intWybranaOpcja;
                }
                break;
            }
            else {
                cout << "Wybrano opcje spoza zakresu!" << endl;
            }
        }


        if (wybranaOpcjaEdycji == 1) {
            cout << "Nadaj nowe imie" << endl;

            string wybranaOpcjaImienia;
            cin >> wybranaOpcjaImienia;

            if (wybraneZwierze != NULL) {
                wybraneZwierze->setImie(wybranaOpcjaImienia);
                serwisZwierzat->zaktualizuj(wybraneZwierze);
            }

        }
        else if (wybranaOpcjaEdycji == 2) {
            while(true) {
                cout << "Podaj nowa wage w gramach" << endl;

                string wybranaOpcjaWagi;
                cin >> wybranaOpcjaWagi;

                if (!sprawdzaczLiczb.jestLiczba(wybranaOpcjaWagi)) {
                    cout << "Wybrana opcja nie jest liczba!" << endl;
                    continue;
                }

                int intWybranaOpcjaWagi = stoi(wybranaOpcjaWagi);
                wybraneZwierze->setWagaWGramach(intWybranaOpcjaWagi);
                serwisZwierzat->zaktualizuj(wybraneZwierze);
                break;
            }
           
        }

    }
}


