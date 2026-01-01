/**
@file PlanerWizyt.h
*/
#pragma once
#include <iostream>
#include <list>
#include <iomanip>
#include <ctime>
#include <chrono>
#include <sstream>
#include "GodzinyPracy.h"
#include "DniTygodnia.h"
#include "SerwisGrafikuPracy.h"
#include "SerwisWizyt.h"
#include <unordered_map>

using namespace std;

/**
@class PlanerWizyt
@brief Klasa odpowiedzialna za planowanie wizyt oraz wszelkie manipulacje data i czasem
*/
class PlanerWizyt
{
private:
	unordered_map<DniTygodnia, GodzinyPracy> dniOtwarcia;
	shared_ptr<SerwisGrafikuPracy> serwisGrafikuPracy;
	shared_ptr<SerwisWizyt> serwisWizyt;
	string zaladuj(time_t aktualnyCzas, std::string format);
public:
/**
@brief Konstruktor argumentowy, ustawiajacy serwis grafiku pracy i serwis wizyt
*/
	PlanerWizyt(shared_ptr<SerwisGrafikuPracy> serwisGrafikuPracy, shared_ptr<SerwisWizyt> serwisWizty);
/**
@brief Funkcja zwracajaca aktualny dzien tygodnia z przekazanego czasu
@return Aktualny dzien tygodnia (Poniedzialek - Niedziela) po angelsku
@param currentTime - zmienna opisujaca czas, dla ktorego ma byc wyciagniety dzien tygodnia
*/
	string zaladujAktualnyDzienTygodnia(time_t currentTime);
/**
@brief Funkcja zwracajaca miesiac z przekazanego czasu
@return Miesiac (Styczen - Grudzien) po angelsku
@param currentTime - zmienna opisujaca czas, dla ktorego ma byc wyciagniety miesiac
*/
	string zaladujMiesiac(time_t currentTime);
/**
@brief Funkcja zwracajaca dzien miesiaca z przekazanego czasu
@return Dzien miesiaca (1 - 31)/(1-30)/(1-28/29)
@param currentTime - zmienna opisujaca czas, dla ktorego ma byc wyciagniety dzien miesiaca
*/
	string zaladujDzienMiesiaca(time_t currentTime);
/**
@brief Funkcja zwracajaca rok z przekazanego czasu
@return Rok
@param czas - zmienna opisujaca czas, dla ktorego ma byc wyciagniety rok
*/
	string zaladujRok(time_t czas);
/**
@brief Funkcja zwracajaca pierwsza dostepna godzine na aktualny dzien tygodnia i za dana godzine.
Jest to funkcja pomocnicza uzywana w metodzie znajdzPierwszyDostepnyTermin()
@return Zwraca pare, ktorej pierwszym elementem jest dzien tygodnia, a drugim godzina - reprezentuja one pierwszy mozliwy termin
@param aktualnyDzienTygodnia - parametr opisujacy aktualny dzien tygodnia, dla ktorego chcemy sprawdzic dostepnosc
@param terminNaNastepnyDzien - parametr opisujacy nastepny dzien tygodnia z dostepna wizyta po aktualnym dniu tygodnia
@param aktualnaGodzina - parametr opisujacy aktualnie rozwazana godzine wizyty
@param pierwszaDostepnaGodzinaWizty - parametr opisujacy pierwsza dostepna godzine
*/	
	pair<DniTygodnia, int> zaladujDostepnaGodzineNaDzienTygodnia(DniTygodnia aktualnyDzienTygodnia, DniTygodnia terminNaNastepnyDzien, int aktualnaGodzina, int pierwszaDostepnaGodzinaWizty);
/**
@brief Funkcja zwracajaca pierwszy dostepny termin. Uzywa ona roznych warjacji metod zaladujDostepnaGodzineNaDzienTygodnia()
@return Zwraca pare, ktorej pierwszym elementem jest dzien tygodnia, a drugim godzina - reprezentuja one pierwszy mozliwy termin
*/	
	pair<DniTygodnia, int> znajdzPierwszyDostepnyTermin();
/**
@brief Funkcja zwracajaca pierwszy dostepna date bazujac na aktualnym czasie.
@return Zwraca pare, ktorej pierwszym elementem jest dzien tygodnia, a drugim godzina - reprezentuja one pierwszy mozliwy termin
*/	
	pair<string, time_t> zaladujPierszaDostepnaDate();

/**
@brief Funkcja zwracajaca ostatnia mozliwa date do rezerwacji wizyty
@return Zwraca pare, ktorej pierwszym elementem jest sformatowana data, a drugim czas (typ time_t) - reprezentuja one ostatni mozliwy termin
@param poczaktowyCzas - parametr typu time_t, w ktorym jest zapisany czas poczatkowy
@param format - format wyjsciowy ostatniej dostepnej daty
*/
	pair<string, time_t> zaladujOstatniaDostepnaDate(time_t poczaktowyCzas, string format);

/**
@brief Funkcja dodajaca do zadanego czasu dana liczne dni.
Np. 
time_t czas = 01-01-2000 
int liczba_dni = 10
dodajDzien(czas, liczba_dni) -> 11-01-2000
@return zmieniony czas o dodanej liczbnie dni
@param poczaktowyCzas - czas do ktorego chcemy dodac zadana liczbe dni
@param liczbaDni - liczba dni, ktora zostanie dodana do istniejacego czasu
*/
	time_t dodajDzien(time_t poczaktowyCzas, int liczbaDni);
	
/**	
@brief Funkcja dodajaca do zadanego czasu dana liczne godzin.
Np. 
time_t czas = 01-01-2000 10:00 
int liczba_godzin = 10
dodajGodzine(czas, liczba_godzin) -> 01-01-2000 20:00
@return zmieniony czas o dodanej liczbnie godzin
@param poczaktowyCzas - czas do ktorego chcemy dodac zadana liczbe godzin
@param liczbaGodzin - liczba godzin, ktora zostanie dodana do istniejacego czasu
*/
	time_t dodajGodzine(time_t poczaktowyCzas, int liczbaGodzin);
/**	
@brief Funkcja ustawiajaca godzine dla danego czasu
Np. 
time_t poczaktowyCzas = 01-01-2000 10:00 
int godzina = 8
int minuta = 30
dodajGodzine(poczaktowyCzas, liczba_godzin) -> 01-01-2000 8:30
@return ustawCzas zwraca zmieniony czas z ustawiona zadana godzina
@param poczaktowyCzas - czas dla ktorego chcemy ustawic zadana godzine i minute
@param godzina - godzina, ktoa chcemy ustawic
@param minuta - minuta, ktora chcemy ustawic
*/
	time_t ustawCzas(time_t poczaktowyCzas, int godzina, int minuta);
/**	
@brief Funkcja zaokraglajaca godzine
Np. 
time_t poczaktowyCzas = 01-01-2000 10:00 
int liczbaGodzin = 1
dodajGodzinePlusZaokraglenie(poczaktowyCzas, liczbaGodzin) -> 01-01-2000 11:00

Np. 
time_t poczaktowyCzas = 01-01-2000 10:01 
int liczbaGodzin = 1
dodajGodzinePlusZaokraglenie(poczaktowyCzas, liczbaGodzin) -> 01-01-2000 12:00

@return zmieniony czas z zaokraglona godzina
@param poczaktowyCzas - czas dla ktorego chcemy zaokraglic godzine
@param liczbaGodzin - liczba godzin dla ktorej chcemy zaokraglic w gore
*/
	time_t dodajGodzinePlusZaokraglenie(time_t poczaktowyCzas, int liczbaGodzin);
/**	
@brief Funkcja zamieniaca angielski dzien tygodnia na tym enum zawiarajacy polskie dnia tygodnia
Np. 
string dniTygodniaTekst = "Monday"
zamienNaDniTygonida(dniTygodniaTekst) -> DniTygodnia::PONIEDZIALEK

@return dzien tygodnia, bedacy polskim odpowiednikiem
@param dniTygodniaTekst - dzien tygodnia po angielski
*/
	DniTygodnia zamienNaDniTygonida(string dniTygodniaTekst);
		/**	
@brief Funkcja zwracajaca nastepny dostepny dzien tygodnia
Np. 
zaladujNastepnyDzienTygodnia(DniTygodnia::PONIEDZIALEK) -> DniTygodnia::WTOREK
zaladujNastepnyDzienTygodnia(DniTygodnia::NIEDZIELA) -> DniTygodnia::PONIEDZIALEK
zaladujNastepnyDzienTygodnia(DniTygodnia::SOBOTA) -> DniTygodnia::PONIEDZIALEK - w niedziele jest zamkniete
@return nastepny dostepny dzien tygodnia, na ktory mozna zarezerwowac wizyte
@param aktualnyDzienTygodnia - zadany dzien tygodnia, dla ktorego szukamy nastepnego dnia ktory bedzie dostepny
*/
	DniTygodnia zaladujNastepnyDzienTygodnia(DniTygodnia aktualnyDzienTygodnia);
/**	
@brief Funkcja zwracajaca pierwszy dostepny czas - zwraca ona pare, w ktorej jest zawarty dzien tygodnia i czas
@return zwraca pierwszy dostepny czas dla wizyty - typem zwracanym jest para, gdzie pierwszym elementem jest pierwszy dosteny dzien tygodnia oraz czas
@param aktualnyCzas - zadany czas dla ktorego chcemy znalezc pierwszy dostepny dzien tygodnia z czasem (typ time_t)
*/
	std::pair<DniTygodnia, time_t> zaladujDostepyCzas(time_t aktualnyCzas);
/**	
@brief Funkcja wyswietlajaca dany czas o zadanym formacie
@param currentTime - czas, ktory chcemy odpowiednio sformatowac
@param format - zadany format czasu
*/
	void wyswietl(time_t currentTime, string format);
/**	
@brief Funkcja zamieniaca dany czas na tym enum DniTygodnia
@return dzien tygodnia odpowiadajacy zadanemu czasowi
@param czas - parametr czasu, dla ktorego sprawdzic jakim jest dniem tygodnia
*/
	DniTygodnia zamienNaDniTygonida(time_t czas);
/**	
@brief Funkcja godzine zamkniecia w danym dniu
@return czas w ktorym jest zamkniecie w danym dniu
@param czas - parametr czasu, dla ktorego sprawdzic jaka jest godzina zamkniecia
@param ostatniDostepnyDzienTygodnia - parametr dnia tygodnia, dla ktorego chcemy sprawdzic godzine zamkniecia
*/
	time_t getGodzinaZamknieciaWDniu(DniTygodnia ostatniDostepnyDzienTygodnia, time_t czas);

	/**	
@brief Funkcja generujaca wszystkie dostepne miesiace, w ktorych mozna zarezerwowac wizyte
@return mapa, ktora zawmiera miesac i czas - oznaczaja one dostepne miesiace do rezerwacji wizty
@param czasRozpoczecia - parametr czasu, od ktorego bedziemy generowac pierwszy dostepny miesiac
@param czasZakonczenia - parametr czasu, do ktorego bedziemy generowac ostatni dostepny miesiac
*/
	unordered_map<int, time_t> wygenerujMiesiace(time_t czasRozpoczecia, time_t czasZakonczenia);

/**	
@brief Funkcja dodajaca do zadanego czasu dana liczne miesiecy.
Np. 
time_t czas = 01-01-2000
int liczbaMiesiecy = 3
dodajMiesiac(czas, liczbaMiesiecy) -> 01-04-2000
@return zmieniony czas o dodanej liczbnie miesiecy
@param poczaktowyCzas - czas do ktorego chcemy dodac zadana liczbe miesiecy
@param liczbaMiesiecy - liczba miesiecy, ktora zostanie dodana do istniejacego czasu
*/
	time_t dodajMiesiac(time_t poczaktowyCzas, int liczbaMiesiecy);
/**	
@brief Funkcja zwracajaca liczbe okreslajaca indeks miesiaca dla danego czasu
Np. 
time_t czas = 01-04-2000

getMiesiac(czas) -> 3 - indeskacja jest z przedzialu [0..11]
@return indeks miesiaca - przedzial 0-11
@param czas - czas, z ktorego chcemy wycjagnac miesiac
*/
	int getMiesiac(time_t czas);

/**	
@brief Funkcja zamieniaca czas na dany miesiac po polsku
Np. 
time_t czas = 01-01-2000
zamienNaMiesiac(czas) -> "Styczen"
@return miesiac po polsku
@param czas - czas, dla ktorego chcemy zwrocic miesiac po polsku
*/	
	string zamienNaMiesiac(time_t czas);

/**	
@brief Funkcja zamieniaca miesiac z anigelskiego na miesiac po polsku
Np. 
string miesiacPoAngielsku = "January"
zamienZAngielskiegoNaPolski(miesiacPoAngielsku) -> "Styczen"
@return miesiac po polsku
@param miesiacPoAngielsku - miesiac w jezyku angielskim
*/	
	std::string zamienZAngielskiegoNaPolski(const string& miesiacPoAngielsku);

/**	
@brief Funkcja wyswietlajaca kalenarz dla danego miesiaca
@param rok - rok, ktory ma byc uwzgledniony przy wyswietlaniu kalenarza 
@param miesiac - miesac dla ktorgo rysujemy kalenarz
@param dzienPoczatkowy - dzien poczatkowy - dni przed tym dniem w ramach tego samego miesiaca nie beda wswietlane
@param dzienKoncowy - dzien koncowy - dni po tym dniu w ramach tego samego miesiaca nie beda wswietlane
*/	
	void wypiszKalendarz(int rok, int miesiac, int dzienPoczatkowy, int dzienKoncowy);
/**	
@brief Funkcja zwaracajaca czy zadany miesiac jest pierwszym dostepny miesiacem
@param miesiace - wygenerowana mapa wszystkich dostepnych miesiecy
@param miesiac - miesac ktory chcemy sprawdzic czy jest pierwsztm dostem
@return - true jesli zadany miesiac jest pierwszym dostepnym miesiacem, false jesli nim nie jest
*/		
	bool czyPierwszDostepnyMiesiac(unordered_map<int, time_t> miesiace, time_t miesiac);
/**	
@brief Funkcja zwaracajaca czy zadany miesiac jest ostatnim dostepny miesiacem
@param miesiace - wygenerowana mapa wszystkich dostepnych miesiecy
@param miesiac - miesac ktory chcemy sprawdzic czy jest ostatnim dostem
@return - true jesli zadany miesiac jest ostatnim dostepnym miesiacem, false jesli nim nie jest
*/	
	bool czyOstatniDostepnyMiesiac(unordered_map<int, time_t> miesiace, time_t miesiac);

/**	
@brief Funkcja ostatni dzien miesiaca
@param czasWMillisekundach - czas dla ktorego chcemy sprawdzic jaki jest ostatni dzien miesiaca np. 31,30,29,28
@return ostatni dzien miesiaca. Mozliwe liczby to: 31,30,29,28
*/
	int ostatniDzienMiesiaca(time_t czasWMillisekundach);

/**	
@brief Funkcja generujaca dni na zadany miesiac uwzgledniajac rok oraz dzien poczatkowy i koncowy
@param rok - rok potrzebny to wygenerowania dni na caly miesiac
@param miesiac - miesiac dla ktorego chcemy wygnerowac dni
@param dzienPoczatkowy - pierwszy dzien miesiaca, od ktorego chcemy zaczac generowac mape z dniami
@param dzienKoncowy - ostatni dzien miesiaca, do ktorego chcemy zaczac generowac mape z dniami
@return mapa z wygenerowanymi dniami miesiaca, kluczem tej mapy jest dzien miesiaca np. 1 jest pierwszym dniem, a wartoscia jest czas dla danego dnia
*/
	unordered_map<int, time_t> wygenerujDni(int rok, int miesiac, int dzienPoczatkowy, int dzienKoncowy);

/**	
@brief Funkcja sprawdzjaca czy podany dzien tygodnia jest dniem tygodnia z czasu

time_t czas = 01-01-2023 // ten czas to niedziela
czyJestDniem(DniTygodnia::PONIEDZIALEK, czas) -> false
czyJestDniem(DniTygodnia::NIEDZIELA, czas) -> true

@param wybranyDzien - wybrany dzien tygodnia np. DniTygodnia::PONIEDZIALEK
@param wybranyCzas - wybrany czas, ktory chcemy sprawdzic czy jest podanym dniem tygodnia (pierwszy paramter)
@return true jest wybrany dzien tygodnia jest dniem tygodnia z podaego czasu
*/
	bool czyJestDniem(DniTygodnia wybranyDzien, time_t wybranyCzas);
/**	
@brief Funkcja generujaca bloki godzinowe.
@param wybranyDzien - dzien dla ktorego chcemy wygenerowac dostepne bloki godzinowe
@param lekarze - dosepni lekarze w danym dniu
@return mapa zawieraca bloki godzinowe bedace kluczem ten mapy. Watoscia tej mapy jest mapa zawierjaca int bedacy id lekarza a waroscia jest obiekt lekarza
*/	
	unordered_map <int, unordered_map<int, shared_ptr<Lekarz>>> wygenerujBlokiGodzinowe(time_t wybranyDzien, list<shared_ptr<Lekarz>> lekarze);
/**	
@brief Funkcja towrzaca wizyte i zapusjaca ja do bazy,
@param wizyta - obiekt wiyzty, ktory chcemy zapisac do bazy
*/	
	void utworzWizyte(Wizyta wizyta);

	/**	
@brief Funkcja generujaca kolejne Id dla wizty
@return id kolejnej wiyzty, ktora mozemy zapisac w bazie
*/	
	int wygenerujIdWizyty();
};

