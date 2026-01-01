#pragma warning(disable : 4996)
#include "PlanerWizyt.h"
#include <map>
#include <unordered_map>
#include <memory>

using namespace std;
PlanerWizyt::PlanerWizyt(shared_ptr<SerwisGrafikuPracy> serwisGrafikuPracy, shared_ptr<SerwisWizyt> serwisWizyt)
{
    this->serwisGrafikuPracy = serwisGrafikuPracy;
    this->serwisWizyt = serwisWizyt;
    GodzinyPracy domyslne = GodzinyPracy(8, 0, 20, 0);
    GodzinyPracy weekendowe = GodzinyPracy(9, 0, 23, 0);
    dniOtwarcia.insert(pair<DniTygodnia, GodzinyPracy>(DniTygodnia::Poniedzialek, domyslne));
    dniOtwarcia.insert(pair<DniTygodnia, GodzinyPracy>(DniTygodnia::Wtorek, domyslne));
    dniOtwarcia.insert(pair<DniTygodnia, GodzinyPracy>(DniTygodnia::Sroda, domyslne));
    dniOtwarcia.insert(pair<DniTygodnia, GodzinyPracy>(DniTygodnia::Czwartek, domyslne));
    dniOtwarcia.insert(pair<DniTygodnia, GodzinyPracy>(DniTygodnia::Piatek, domyslne));
    dniOtwarcia.insert(pair<DniTygodnia, GodzinyPracy>(DniTygodnia::Sobota, weekendowe));
}

std::string PlanerWizyt::zaladujAktualnyDzienTygodnia(time_t aktualnyCzas) {
    return zaladuj(aktualnyCzas, "%A");
}

std::string PlanerWizyt::zaladujMiesiac(time_t aktualnyCzas) {
    return zaladuj(aktualnyCzas, "%B");
}

std::string PlanerWizyt::zaladujRok(time_t aktualnyCzas) {
    return zaladuj(aktualnyCzas,  "%Y");
}

std::string PlanerWizyt::zaladuj(time_t aktualnyCzas, std::string format) {

    struct tm* tmAktualnyCzas = localtime(&aktualnyCzas);  // Konwersja na lokalny czas

    char bufor[20];  // Bufor na przechowanie nazwy dnia tygodnia
    strftime(bufor, sizeof(bufor), format.c_str(), tmAktualnyCzas);  // Formatowanie nazwy dnia

    string miesiac(bufor);  // Konwersja z C-stringa na std::string

    return miesiac;
}

std::string PlanerWizyt::zamienZAngielskiegoNaPolski(const string& miesiacPoAngielsku) {
    std::map<string, string> slownik;
    slownik["January"] = "Styczen";
    slownik["February"] = "Luty";
    slownik["March"] = "Marzec";
    slownik["April"] = "Kwiecien";
    slownik["May"] = "Maj";
    slownik["June"] = "Czerwiec";
    slownik["July"] = "Lipiec";
    slownik["August"] = "Sierpien";
    slownik["September"] = "Wrzesien";
    slownik["October"] = "Pazdziernik";
    slownik["November"] = "Listopad";
    slownik["December"] = "Grudzien";

    auto it = slownik.find(miesiacPoAngielsku);
    if (it != slownik.end()) {
        return it->second;
    }

    return "";
}

unordered_map <int, unordered_map<int, shared_ptr<Lekarz>>> PlanerWizyt::wygenerujBlokiGodzinowe(time_t wybranyDzien, list<shared_ptr<Lekarz>> lekarze) {
    DniTygodnia wybranyDzienTygodnia = zamienNaDniTygonida(wybranyDzien);
    unordered_map <int, unordered_map<int, shared_ptr<Lekarz>>> blokiGodzinowe;
    for (auto &&lekarz : lekarze) {
        unordered_map< DniTygodnia, GodzinyPracy> grafikPracyDlaLekarza = serwisGrafikuPracy->zaladujGrafik(lekarz);
        GodzinyPracy godzinyPracyLekarzaWDniu = grafikPracyDlaLekarza[wybranyDzienTygodnia];
        for (int aktualnaGodzina = godzinyPracyLekarzaWDniu.getGodzinaRozpoczecia(); aktualnaGodzina < godzinyPracyLekarzaWDniu.getGodzinaZakonczenia(); aktualnaGodzina++) {
            if (blokiGodzinowe.find(aktualnaGodzina) == blokiGodzinowe.end()) {
                // nie znaleziona innego lekarza ktory jest dostepny w tej godzinie, wiec dodajemy nowa mape z jednym elementem
                unordered_map<int, shared_ptr<Lekarz>> lekarzeWbloku;
                lekarzeWbloku[lekarz->getId()] = lekarz;
                blokiGodzinowe[aktualnaGodzina] = lekarzeWbloku;
            }
            else {
                // jest juz lekarz ktory jest dostepny w tych godzianch - dodajemy go do mapy jako kolejny element
                unordered_map<int, shared_ptr<Lekarz>> lekarzeWbloku = blokiGodzinowe[aktualnaGodzina];
                lekarzeWbloku[lekarz->getId()] = lekarz;
                blokiGodzinowe[aktualnaGodzina] = lekarzeWbloku;
            }
        }
    }

    tm* tmWybranyDzien = localtime(&wybranyDzien);
    list<shared_ptr<Wizyta>> wizyty = serwisWizyt->zaladujWizytyDlaDaty(tmWybranyDzien->tm_year + 1900, tmWybranyDzien->tm_mon + 1, tmWybranyDzien->tm_mday);
    for (auto&& wizyta : wizyty) {
        for (auto &blok : blokiGodzinowe) {
            if (blok.first == wizyta->getDataGodzina().getGodzina()) {
                // znaleniono rezerwacje na dana godzine - sprawdz czy lekarz powinien zostac usuniety
                unordered_map<int, shared_ptr<Lekarz>> mapIdLekarza = blok.second;
                unordered_map<int, shared_ptr<Lekarz>>::iterator it;
         
                for (it = mapIdLekarza.begin(); it != mapIdLekarza.end(); it++) {
                    if (wizyta->getIdLekarza() == it->second->getId()) {
                        blok.second.erase(wizyta->getIdLekarza());
                    }
               
                }
            }
        }
    }

    return blokiGodzinowe;
}

void PlanerWizyt::utworzWizyte(Wizyta wizyta)
{
    serwisWizyt->zarezerujWizyte(wizyta);
}

int PlanerWizyt::wygenerujIdWizyty()
{
    return this->serwisWizyt->getNastepneId();
}

//dstepne miesiace do rezerwacji, element 0 to pierwszy dostepny, a ostatni elelment to ostatni dostepny 
bool PlanerWizyt::czyPierwszDostepnyMiesiac(unordered_map<int, time_t> miesiace, time_t miesiac)
{
    time_t pierwszyDostpenyMiesiac = miesiace[1];
    return pierwszyDostpenyMiesiac == miesiac;
}

bool PlanerWizyt::czyOstatniDostepnyMiesiac(unordered_map<int, time_t> miesiace, time_t miesiac)
{
    
    time_t pierwszyDostpenyMiesiac = miesiace[miesiace.size()];
    return pierwszyDostpenyMiesiac == miesiac;
}

unordered_map<int, time_t> PlanerWizyt::wygenerujDni(int rok, int miesiac, int dzienPoczatkowy, int dzienKoncowy) {
    unordered_map<int, time_t> dostepneDni;
    std::tm timeinfo = {};
    timeinfo.tm_year = rok;
    timeinfo.tm_mon = miesiac - 1; // Miesiace indeksowane od 0 do 11
    timeinfo.tm_mday = 0; // Pierwszy dzien miesiaca
    timeinfo.tm_hour = 0; // Ustawienie godziny na 0
    timeinfo.tm_min = 0; // Ustawienie minut na 0
    timeinfo.tm_sec = 0; // Ustawienie sekund na 0
    timeinfo.tm_isdst = -1; // Informacja o letnim czasie (Daylight Saving Time) nieznana

    std::mktime(&timeinfo); // Konwersja na time_t

    int dzienTygodnia = timeinfo.tm_wday; // Dzien tygodnia dla pierwszego dnia miesiaca (0 - niedziela, 1 - poniedzialek, ..., 6 - sobota)
    int liczbaDniWMiesiacu = dzienKoncowy; //31 - (dzienTygodnia - 1);

    int dzien = 1;
    for (; dzien <= liczbaDniWMiesiacu; dzien++) {
        if (dzien >= dzienPoczatkowy && dzien <= dzienKoncowy) {
            tm tmDostepnyDzien = {};
            tmDostepnyDzien.tm_year = rok;
            tmDostepnyDzien.tm_mon = miesiac - 1;
            tmDostepnyDzien.tm_mday = dzien;
            tmDostepnyDzien.tm_hour = 0; // Ustawienie godziny na 0
            tmDostepnyDzien.tm_min = 0; // Ustawienie minut na 0
            tmDostepnyDzien.tm_sec = 0; // Ustawienie sekund na 0
            tmDostepnyDzien.tm_isdst = -1; // Informacja o letnim czasie (Daylight Saving Time) nieznana
            dostepneDni[dzien] = mktime(&tmDostepnyDzien);
           
        }
    }

    return dostepneDni;
}

bool PlanerWizyt::czyJestDniem(DniTygodnia wybranyDzien, time_t wybranyCzas)
{
    DniTygodnia dzienTygodniaDlaPodanegoCzasu = zamienNaDniTygonida(wybranyCzas);
    return dzienTygodniaDlaPodanegoCzasu == wybranyDzien;
}


void PlanerWizyt::wypiszKalendarz(int rok, int miesiac, int dzienPoczatkowy, int dzienKoncowy) {
    std::tm timeinfo = {};
    timeinfo.tm_year = rok; 
    timeinfo.tm_mon = miesiac - 1; // Miesiace indeksowane od 0 do 11
    timeinfo.tm_mday = 0; // Pierwszy dzien miesiaca
    timeinfo.tm_hour = 0; // Ustawienie godziny na 0
    timeinfo.tm_min = 0; // Ustawienie minut na 0
    timeinfo.tm_sec = 0; // Ustawienie sekund na 0
    timeinfo.tm_isdst = -1; // Informacja o letnim czasie (Daylight Saving Time) nieznana

    std::mktime(&timeinfo); // Konwersja na time_t

    std::cout << "---------------------------" << std::endl;
    std::cout << "   Kalendarz " << std::setw(4) << (rok+1900) << " - " << std::setw(2) << miesiac << std::endl;
    std::cout << "---------------------------" << std::endl;
    std::cout << " Pn  Wt  Sr  Cz  Pt  So  Nd" << std::endl;

    int dzienTygodnia = timeinfo.tm_wday; // Dzien tygodnia dla pierwszego dnia miesiaca (0 - niedziela, 1 - poniedzialek, ..., 6 - sobota)
    int liczbaDniWMiesiacu = dzienKoncowy; //31 - (dzienTygodnia - 1);

    for (int i = 0; i < dzienTygodnia; i++) {
        std::cout << "    ";
    }

    int dzien = 1;
    for (; dzien <= liczbaDniWMiesiacu; dzien++) {
        if (dzien >= dzienPoczatkowy && dzien <= dzienKoncowy) {
            std::cout << std::setw(3) << dzien << " ";
        }
        else {
            std::cout << "    ";
        }

        if ((dzien + dzienTygodnia) % 7 == 0) {
            std::cout << std::endl;
        }
    }

    if (dzienKoncowy > liczbaDniWMiesiacu) {
        std::cout << std::endl;
    }
}


int PlanerWizyt::ostatniDzienMiesiaca(time_t czasWMillisekundach) {
    const time_t kopiaWybranegoMiesiaca = time_t(czasWMillisekundach);
    time_t czas = time_t(kopiaWybranegoMiesiaca);

    tm* timeinfo = localtime(&czas);

    int rok = timeinfo->tm_year + 1900; // Rok + 1900
    int miesiac = timeinfo->tm_mon + 1; // Miesiace indeksowane od 0 do 11

    // Ustawienie daty na pierwszy dzien nastepnego miesiaca
    timeinfo->tm_year = rok - 1900;
    timeinfo->tm_mon = miesiac;
    timeinfo->tm_mday = 1;
    timeinfo->tm_hour = 0;
    timeinfo->tm_min = 0;
    timeinfo->tm_sec = 0;

    // Pomniejszenie o 1 sekunde, aby otrzymac ostatni dzien biezacego miesiaca
    time_t ostatniDzien = std::mktime(timeinfo) - 1;

    std::tm* lastDayInfo = localtime(&ostatniDzien);
    int rezultat = lastDayInfo->tm_mday;
    return rezultat;
}

std::pair<string, time_t> PlanerWizyt::zaladujOstatniaDostepnaDate(time_t poczaktowyCzas, string format) {
    tm* obecnyCzas = localtime(&poczaktowyCzas);

    obecnyCzas->tm_mon += 3;

   time_t maksymalnaMozliwaData = mktime(obecnyCzas);
   DniTygodnia ostatniDostepnyDzienTygodnia = zamienNaDniTygonida(maksymalnaMozliwaData);
 
   if (ostatniDostepnyDzienTygodnia == DniTygodnia::Niedziela) {
       obecnyCzas = localtime(&maksymalnaMozliwaData);
       obecnyCzas->tm_mday -= 1;
       maksymalnaMozliwaData = mktime(obecnyCzas);
   }

    char bufor[80];

    strftime(bufor, sizeof(bufor), format.c_str(), localtime(&maksymalnaMozliwaData));
    string dataTekst(bufor);

    return pair<string, int>(dataTekst, maksymalnaMozliwaData);
}

time_t PlanerWizyt::dodajDzien(time_t poczaktowyCzas, int liczbaDni) {
    tm* obecnyCzas = localtime(&poczaktowyCzas);

    obecnyCzas->tm_mday += liczbaDni;

    time_t dataZDodnymDniem = mktime(obecnyCzas);
    char bufor[80];

    strftime(bufor, sizeof(bufor), "%c", localtime(&dataZDodnymDniem));

    string dataTekst(bufor);

    return dataZDodnymDniem;
}

time_t PlanerWizyt::dodajMiesiac(time_t poczaktowyCzas, int liczbaMiesiecy) {
    tm* obecnyCzas = localtime(&poczaktowyCzas);
    obecnyCzas->tm_mon += liczbaMiesiecy;
    obecnyCzas->tm_mday = 1;
    obecnyCzas->tm_hour = 0;
    obecnyCzas->tm_min = 0;
    obecnyCzas->tm_sec = 0;
    time_t dataZDodnymMiesiacem = mktime(obecnyCzas);
    return dataZDodnymMiesiacem;
}

time_t PlanerWizyt::dodajGodzine(time_t poczaktowyCzas, int liczbaGodzin) {
    tm* obecnyCzas = localtime(&poczaktowyCzas);

    obecnyCzas->tm_hour += liczbaGodzin;

    time_t dataZDodanaGodzina = mktime(obecnyCzas);
    char bufor[80];

    strftime(bufor, sizeof(bufor), "%R", localtime(&dataZDodanaGodzina));

    string dataTekst(bufor);

    return dataZDodanaGodzina;
}

time_t PlanerWizyt::dodajGodzinePlusZaokraglenie(time_t poczaktowyCzas, int liczbaGodzin) {
    tm* obecnyCzas = localtime(&poczaktowyCzas);

    if (obecnyCzas->tm_min == 0) 
    {
        return dodajGodzine(poczaktowyCzas, liczbaGodzin);
    }
    else {
        obecnyCzas->tm_hour += liczbaGodzin;
        obecnyCzas->tm_hour += 1;
        obecnyCzas->tm_min = 0;
        time_t dataZDodanaGodzina = mktime(obecnyCzas);
        char bufor[80];

        strftime(bufor, sizeof(bufor), "%R", localtime(&dataZDodanaGodzina));

        string dataTekst(bufor);

        return dataZDodanaGodzina;
    }
}

time_t PlanerWizyt::ustawCzas(time_t poczaktowyCzas, int godzina, int minuta) {
    tm* obecnyCzas = localtime(&poczaktowyCzas);

    obecnyCzas->tm_hour = godzina;
    obecnyCzas->tm_min = minuta;
    obecnyCzas->tm_sec = 0;

    time_t dataZDodanaGodzina = mktime(obecnyCzas);
    char bufor[80];

    strftime(bufor, sizeof(bufor), "%c", localtime(&dataZDodanaGodzina));

    string dataTekst(bufor);

    return dataZDodanaGodzina;
}

std::string PlanerWizyt::zaladujDzienMiesiaca(time_t currentTime) {
    time(&currentTime);  // Pobranie aktualnego czasu

    struct tm* localTime = localtime(&currentTime);  // Konwersja na lokalny czas

    char dayBuffer[20];  // Bufor na przechowanie nazwy dnia tygodnia
    strftime(dayBuffer, sizeof(dayBuffer), "%d", localTime);  // Formatowanie nazwy dnia

    string dayOfWeek(dayBuffer);  // Konwersja z C-stringa na std::string

    return dayOfWeek;
}

void PlanerWizyt::wyswietl(time_t currentTime, string format) {
   
    struct tm* localTime = localtime(&currentTime);  // Konwersja na lokalny czas

    char bufor[80];  // Bufor na przechowanie nazwy dnia tygodnia
    strftime(bufor, sizeof(bufor), format.c_str(), localTime);  // Formatowanie nazwy dnia

    string dataTekst(bufor);

    cout << dataTekst;
}

std::pair<DniTygodnia, int> PlanerWizyt::zaladujDostepnaGodzineNaDzienTygodnia(DniTygodnia aktualnyDzienTygodnia, DniTygodnia terminNaNastepnyDzien, int aktualnaGodzina, int pierwszaDostepnaGodzinaWizty) {
    if (aktualnaGodzina >= dniOtwarcia[aktualnyDzienTygodnia].getGodzinaZakonczenia() - 2) {
        GodzinyPracy godzinyPracyWNastepnymDniu = dniOtwarcia[terminNaNastepnyDzien];
        return pair<DniTygodnia, int>(terminNaNastepnyDzien, godzinyPracyWNastepnymDniu.getGodzinaRozpoczecia());
    }
    else if (aktualnaGodzina <= dniOtwarcia[aktualnyDzienTygodnia].getGodzinaRozpoczecia() - 2) {
        GodzinyPracy godzinyOtwarciaWAktualnyDzien = dniOtwarcia[aktualnyDzienTygodnia];
        return pair<DniTygodnia, int>(aktualnyDzienTygodnia, godzinyOtwarciaWAktualnyDzien.getGodzinaRozpoczecia());
    }
    else {
        return  pair<DniTygodnia, int>(aktualnyDzienTygodnia, pierwszaDostepnaGodzinaWizty);
    }
}

DniTygodnia PlanerWizyt::zamienNaDniTygonida(time_t czas) {
    string dzienTygodniaTekst = zaladujAktualnyDzienTygodnia(czas);
    return zamienNaDniTygonida(dzienTygodniaTekst);
}

unordered_map<int, time_t> PlanerWizyt::wygenerujMiesiace(time_t czasRozpoczecia, time_t czasZakonczenia) 
{
    tm* tmCzasRozpoczecia = localtime(&czasRozpoczecia);
    tmCzasRozpoczecia->tm_hour = 0;
    tmCzasRozpoczecia->tm_min = 0;
    tmCzasRozpoczecia->tm_sec = 0;
    time_t tmWyzerowanyCzasRozpoczecia = mktime(tmCzasRozpoczecia);
    const time_t x = time(nullptr);
    localtime(&x);
    tm* tmCzasZakonczenia = localtime(&czasZakonczenia);
    tmCzasZakonczenia->tm_hour = 0;
    tmCzasZakonczenia->tm_min = 0;
    tmCzasZakonczenia->tm_sec = 0;
    time_t tmWyzerowanyCzasZakonczenia = mktime(tmCzasZakonczenia);



    tm* tmPomocnicznyCzas = localtime(&tmWyzerowanyCzasRozpoczecia);
    time_t pomocniczyCzas = tmWyzerowanyCzasRozpoczecia;
 
 
    unordered_map<int, time_t> miesiace; 
    miesiace.insert(pair<int, time_t>(1, tmWyzerowanyCzasRozpoczecia));
    for (int i = 2; pomocniczyCzas < tmWyzerowanyCzasZakonczenia; i++) {
        int aktualnyMiesiac = tmPomocnicznyCzas->tm_mon + 1;

        if (aktualnyMiesiac > 11) {
            tmPomocnicznyCzas->tm_year += 1;
            tmPomocnicznyCzas->tm_mon = 0;
            pomocniczyCzas = mktime(tmPomocnicznyCzas);
            miesiace.insert(pair<int, time_t>(i, pomocniczyCzas));
        }
        else {
            tmPomocnicznyCzas->tm_mon += 1;
            pomocniczyCzas = mktime(tmPomocnicznyCzas);
            miesiace.insert(pair<int, time_t>(i, pomocniczyCzas));
        }
  
    }

    return miesiace;

}

int PlanerWizyt::getMiesiac(time_t czas) {
    struct tm* tmCzas = localtime(&czas);
    return tmCzas->tm_mon;
}

string PlanerWizyt::zamienNaMiesiac(time_t czas)
{
    string miesiacPoAngielsku = zaladujMiesiac(czas);
    string miesiacPoPolsku = zamienZAngielskiegoNaPolski(miesiacPoAngielsku);
    return miesiacPoPolsku;
}

time_t PlanerWizyt::getGodzinaZamknieciaWDniu(DniTygodnia ostatniDostepnyDzienTygodnia, time_t czas)
{
    GodzinyPracy godzinyPracy = dniOtwarcia.at(ostatniDostepnyDzienTygodnia);
    time_t dataZGodzinaZamkniecia = ustawCzas(czas, godzinyPracy.getGodzinaZakonczenia()-1, 0);
    return dataZGodzinaZamkniecia;
}

DniTygodnia PlanerWizyt::zamienNaDniTygonida(string dniTygodniaTekst) {
    if (dniTygodniaTekst == "Sunday") {
        return DniTygodnia::Niedziela;
    }
    else if (dniTygodniaTekst == "Saturday") {
        return DniTygodnia::Sobota;
    }
    else if (dniTygodniaTekst == "Monday")
    {
        return DniTygodnia::Poniedzialek;
    }
    else if (dniTygodniaTekst == "Tuesday")
    {
        return DniTygodnia::Wtorek;
    }
    else if (dniTygodniaTekst == "Wednesady")
    {
        return DniTygodnia::Sroda;
    }
    else if (dniTygodniaTekst == "Thursday")
    {
        return DniTygodnia::Czwartek;
    }
    else if (dniTygodniaTekst == "Friday")
    {
        return  DniTygodnia::Piatek;
    }
    else {
        return DniTygodnia::Poniedzialek;
    }
}

DniTygodnia PlanerWizyt::zaladujNastepnyDzienTygodnia(DniTygodnia aktualnyDzienTygodnia) {
    if (aktualnyDzienTygodnia == DniTygodnia::Niedziela) {
        return DniTygodnia::Poniedzialek;
    }
    else if (aktualnyDzienTygodnia == DniTygodnia::Sobota) {
        return DniTygodnia::Poniedzialek;
    }
    else if (aktualnyDzienTygodnia == DniTygodnia::Poniedzialek)
    {
        return DniTygodnia::Wtorek;
    }
    else if (aktualnyDzienTygodnia == DniTygodnia::Wtorek)
    {
        return DniTygodnia::Sroda;
    }
    else if (aktualnyDzienTygodnia == DniTygodnia::Sroda)
    {
        return DniTygodnia::Czwartek;
    }
    else if (aktualnyDzienTygodnia == DniTygodnia::Czwartek)
    {
        return DniTygodnia::Piatek;
    }
    else if (aktualnyDzienTygodnia == DniTygodnia::Piatek)
    {
        return  DniTygodnia::Sobota;
    }
    else {
        return DniTygodnia::Poniedzialek;
    }
}

std::pair<DniTygodnia, time_t> PlanerWizyt::zaladujDostepyCzas(time_t aktualnyCzas) {
    tm* obecnyCzas = localtime(&aktualnyCzas);
    string dzienTygodniaTekst = zaladujAktualnyDzienTygodnia(aktualnyCzas);
    DniTygodnia aktualnyDzienTygodnia = zamienNaDniTygonida(dzienTygodniaTekst);
    if (obecnyCzas->tm_hour >= dniOtwarcia[aktualnyDzienTygodnia].getGodzinaZakonczenia() - 2) {
        DniTygodnia nastepnyDzienTygodnia = zaladujNastepnyDzienTygodnia(aktualnyDzienTygodnia);
        GodzinyPracy godzinyPracyWNastepnymDniu = dniOtwarcia[nastepnyDzienTygodnia];
        time_t nastepnyDzien = dodajDzien(aktualnyCzas, 1);
        time_t nastepnyDzienZGodzinaOtwarcia = ustawCzas(nastepnyDzien, godzinyPracyWNastepnymDniu.getGodzinaRozpoczecia(), 0);
     
        return pair<DniTygodnia, time_t>(nastepnyDzienTygodnia, nastepnyDzienZGodzinaOtwarcia);
    }
    else if (obecnyCzas->tm_hour <= dniOtwarcia[aktualnyDzienTygodnia].getGodzinaRozpoczecia() - 2) {
        GodzinyPracy godzinyOtwarciaWAktualnyDzien = dniOtwarcia[aktualnyDzienTygodnia];
        time_t aktualnyDzienZGodzinaOtwarcia = ustawCzas(aktualnyCzas, godzinyOtwarciaWAktualnyDzien.getGodzinaRozpoczecia(), 0);
        return pair<DniTygodnia, time_t>(aktualnyDzienTygodnia, aktualnyDzienZGodzinaOtwarcia);
    }
    else {
        time_t aktualnyDzienZGodzina = dodajGodzinePlusZaokraglenie(aktualnyCzas, 1);
        return  pair<DniTygodnia, time_t>(aktualnyDzienTygodnia, aktualnyDzienZGodzina);
    }
}

std::pair<DniTygodnia, int> PlanerWizyt::znajdzPierwszyDostepnyTermin() {
    const long jednaGodzina = 3600;
    const int mnoznikMinut = 60;
    time_t const teraz = time(0);
    tm* aktualnyCzas = localtime(&teraz);
    long terazPlusGodzina = teraz + time_t(jednaGodzina);

    time_t timeTerazPlusGodzina = time_t(terazPlusGodzina);

    tm* localTimeTerazPlusGodzina = localtime(&timeTerazPlusGodzina);
    if (localTimeTerazPlusGodzina->tm_min != 0) {
        timeTerazPlusGodzina = timeTerazPlusGodzina + time_t(jednaGodzina - (localTimeTerazPlusGodzina->tm_min * mnoznikMinut) - localTimeTerazPlusGodzina->tm_sec);
    }
    int pierwszaDostepnaGodzinaWizty = localtime(&timeTerazPlusGodzina)->tm_hour;
    string dzienTygodnia = zaladujAktualnyDzienTygodnia(timeTerazPlusGodzina);
    int aktualnaGodzina = localTimeTerazPlusGodzina->tm_hour;
    if (dzienTygodnia == "Sunday") {
        GodzinyPracy godzinyPracyWPoniedzialek = dniOtwarcia[DniTygodnia::Poniedzialek];
        return pair<DniTygodnia, int>(DniTygodnia::Poniedzialek, godzinyPracyWPoniedzialek.getGodzinaRozpoczecia());
    }
    else if (dzienTygodnia == "Saturday") {
        return zaladujDostepnaGodzineNaDzienTygodnia(DniTygodnia::Sobota, DniTygodnia::Poniedzialek, aktualnaGodzina, pierwszaDostepnaGodzinaWizty);
    }
    else if (dzienTygodnia == "Monday")
    {
        return zaladujDostepnaGodzineNaDzienTygodnia(DniTygodnia::Poniedzialek, DniTygodnia::Wtorek, aktualnaGodzina, pierwszaDostepnaGodzinaWizty);
    }
    else if (dzienTygodnia == "Tuesday")
    {
        return zaladujDostepnaGodzineNaDzienTygodnia(DniTygodnia::Wtorek, DniTygodnia::Sroda, aktualnaGodzina, pierwszaDostepnaGodzinaWizty);
    }
    else if (dzienTygodnia == "Wednesady")
    {
        return zaladujDostepnaGodzineNaDzienTygodnia(DniTygodnia::Sroda, DniTygodnia::Czwartek, aktualnaGodzina, pierwszaDostepnaGodzinaWizty);
    }
    else if (dzienTygodnia == "Thursday")
    {
        return zaladujDostepnaGodzineNaDzienTygodnia(DniTygodnia::Czwartek, DniTygodnia::Piatek, aktualnaGodzina, pierwszaDostepnaGodzinaWizty);
    }
    else if (dzienTygodnia == "Friday")
    {
        return zaladujDostepnaGodzineNaDzienTygodnia(DniTygodnia::Piatek, DniTygodnia::Sobota, aktualnaGodzina, pierwszaDostepnaGodzinaWizty);
    }
}