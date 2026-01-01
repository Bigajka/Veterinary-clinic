#include "CzytaczPlikow.h"
#include <string>
#include <fstream>
#include <iostream>
#include <sstream>
#include <vector>
#include <filesystem>

using namespace std;

string CzytaczPlikow::wczytajPlik()
{
    std::string nazwaPliku = podajNazwePliku();

    std::ifstream plik(nazwaPliku);
    if (plik.fail()) {
        std::cout << "Nie znaleziono pliku: " << nazwaPliku;
    }

    string zawartoscPliku = zapiszZawartoscPlikuDoZmiennej(plik);
    return zawartoscPliku;
}

void CzytaczPlikow::dopiszDoPliku(string& nowyWiersz)
{
    std::ifstream plik;
    plik.open(podajNazwePliku(), std::ios_base::app);
    bool jestPusty = plik.peek() == std::ifstream::traits_type::eof();
    plik.close();
    std::ofstream plikDoZapisu;
    plikDoZapisu.open(podajNazwePliku(), std::ios_base::app);
    
    if (!jestPusty) {
        plikDoZapisu << "\n";
    }
    
    plikDoZapisu << nowyWiersz;
    plikDoZapisu.close();
}

vector<string> CzytaczPlikow::zmaienNaWiersze(string& trescPliku) {
    vector<string> wierszePliku;
    std::stringstream bufor;
    int indeksOstatniegoZnaku = trescPliku.length() -1;
    for (int indeksZnaku = 0; indeksZnaku <= indeksOstatniegoZnaku; indeksZnaku++) {
        char znak = trescPliku[indeksZnaku];
        bool czyOstatniZnak = indeksZnaku == indeksOstatniegoZnaku;
        if(znak == '\n' || czyOstatniZnak) {
            if (czyOstatniZnak) {
                bufor << znak;
            }
            string calyWiersz = bufor.str();
            wierszePliku.push_back(calyWiersz);
            bufor.str("");
            bufor.clear();
        }
        else {
            bufor << znak;
        }
    }

    return wierszePliku;
}

void CzytaczPlikow::usunWieszPoId(int indeksId, int id, bool czyJestUnikalny) {
    string zawartoscpliku = wczytajPlik();
    vector<string> wiersze = zmaienNaWiersze(zawartoscpliku);
    vector<int> pozycjeDoUsuniecia;
    string idTekst = to_string(id);

    vector<string>::iterator wierszIterator = wiersze.begin();
    while (wierszIterator != wiersze.end()) {
        string aktualneId = getPozycjaTextu(*wierszIterator, indeksId);
        if (aktualneId == idTekst) {
            wierszIterator = wiersze.erase(wierszIterator);
            if (czyJestUnikalny) {
                break;
            }
        }
        else {
            ++wierszIterator;
        }
    }

    zapiszDoPliku(wiersze, podajNazwePliku());
}

void CzytaczPlikow::zapiszDoPliku(const vector<string>& wektor, const string& nazwaPliku) {
    // Otwieranie pliku w trybie czyszczenia i zapisu
    //std::ofstream plik(nazwaPliku, std::ios::out | std::ios::trunc);
    //plik.clear();
    //plik.seekp(0, std::ios::beg);
    //plik.close();

    std::ofstream plikDoZapisu(nazwaPliku, std::ios::out | std::ios::trunc);
    if (plikDoZapisu.is_open()) {
        // Zapisywanie wektora lancuchow do pliku
        int i = 0;
        for (const std::string& s : wektor) {
            i++;
            bool czyOstatniElement = i == wektor.size();
            if (czyOstatniElement) {
                plikDoZapisu << s ;
            }
            else {
                plikDoZapisu << s << std::endl;
            }
            
        }

        // Zamykanie pliku
        plikDoZapisu.close();
    }
    else {
        std::cout << "Nie mozna otworzyc pliku: " << nazwaPliku << std::endl;
    }
}

int CzytaczPlikow::getPozycjaWiersza(vector<string> wiersze, string wiersz) {
    for (int i = 0; i < wiersze.size(); i++) {
        if (wiersze.at(i) == wiersz) {
            return i;
        }
    }

    return -1;
}


string CzytaczPlikow::getPozycjaTextu(string calyTekst, int pozycja) {
    int liczbaKolumn = 0;
    int indeks = 0;
    while (calyTekst[indeks] != '\0') {
        if (calyTekst[indeks] == '|') {
            liczbaKolumn++;
        }
        indeks++;
    }
    std::stringstream bufor;
    if (pozycja == 0) { // czytamy pierwsz kolumne
        int indeksPozycji = 0;
        while (calyTekst[indeksPozycji] != '|') {
            char znak = calyTekst[indeksPozycji];
            bufor << znak;
            indeksPozycji++;
        }

        return bufor.str();
    }
    else if (pozycja == liczbaKolumn) { // czytamy ostania kolumne
        int indeksPozycji = znajdzIndeksOstatniejKolumny(calyTekst);
        for (int i = indeksPozycji +1; i < calyTekst.length(); i++) {
            char znak = calyTekst[i];
            bufor << znak;
        }

        return bufor.str();
    }
    else { // czytamy srodowa kolumne
        // a|baba|c|d -> czytamy baba
        int indeksStartu = znajdzWystapienieSrodkowejKolumny(calyTekst, pozycja);
        int indeksKonca = znajdzWystapienieSrodkowejKolumny(calyTekst, pozycja+1);
        for (int i = indeksStartu +1; i < indeksKonca; i++) {
            char znak = calyTekst[i];
            bufor << znak;
        }

        return bufor.str();
    }
}

int CzytaczPlikow::znajdzIndeksOstatniejKolumny(string& calyTekst) {
    int indeksOstatniegoZnaku = calyTekst.length()-1;
    for (int i = indeksOstatniegoZnaku; i > 0; i--) {
        if (calyTekst[i] == '|') {
            return i;
        }
    }

    return -1;
}

int CzytaczPlikow::znajdzWystapienieSrodkowejKolumny(string& calyTekst, int n) {
    int zliczoneKolumny = 0;

    for (int i = 0; i < calyTekst.length() - 1; i++) {
        if (calyTekst[i] == '|') {
            zliczoneKolumny++;
        }
        if (zliczoneKolumny == n) {
            return i;
        }
    }

    return -1;
}

std::string CzytaczPlikow::zapiszZawartoscPlikuDoZmiennej(std::ifstream& plik) {
    std::stringstream bufor;

    char znak;
    while (plik.get(znak))
    {
        bufor << znak;
    }

    plik.close();

    std::string zawartoscPliku = bufor.str();

    return zawartoscPliku;
};

int CzytaczPlikow::getNastepneId(int indeksId)
{
    string calyPlik = wczytajPlik();
    vector <string> wiersze = zmaienNaWiersze(calyPlik);

    int aktualnyMaksId = 0;

    if (wiersze.size() == 0) {
        return 1;
    }

    for (auto wiersz : wiersze) {
        bool czyPoprawneId = wiersz.find_first_not_of(" \t\n\v\f\r") != std::string::npos;
        if (!czyPoprawneId) {
            continue;
        }

        string idTekst = getPozycjaTextu(wiersz, indeksId);

        int id = stoi(idTekst);
        if (id > aktualnyMaksId) {
            aktualnyMaksId = id;
        }
    }

    return ++aktualnyMaksId;
}
