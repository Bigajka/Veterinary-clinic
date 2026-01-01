#include "SerwisGrafikuPracy.h"

SerwisGrafikuPracy::SerwisGrafikuPracy(shared_ptr < CzytaczGrafikuPracy> czytaczGrafikuPracy)
{

	this->czytaczGrafikuPracy = czytaczGrafikuPracy;
}

unordered_map<DniTygodnia, GodzinyPracy> SerwisGrafikuPracy::zaladujGrafik(shared_ptr<Lekarz> lekarz)
{
	const int indeksId = 0;

	const int indeksPoniedzialku = 1;
	const int indeksPonStartGodz = 2;
	const int indeksPonStartMin = 3;
	const int indeksPonKoniecGodz = 4;
	const int indeksPonKoniecMin = 5;

	const int indeksWtorku = 6;
	const int indeksWtStartGodz = 7;
	const int indeksWtStartMin = 8;
	const int indeksWtKoniecGodz = 9;
	const int indeksWtKoniecMin = 10;

	const int indeksSrody = 11;
	const int indeksSrStartGodz = 12;
	const int indeksSrStartMin = 13;
	const int indeksSrKoniecGodz = 14;
	const int indeksSrKoniecMin = 15;

	const int indeksCzwartku = 16;
	const int indeksCzwStartGodz = 17;
	const int indeksCzwStartMin = 18;
	const int indeksCzwKoniecGodz = 19;
	const int indeksCzwKoniecMin = 20;

	const int indeksPiatku = 21;
	const int indeksPtStartGodz = 22;
	const int indeksPtStartMin = 23;
	const int indeksPtKoniecGodz = 24;
	const int indeksPtKoniecMin = 25;

	const int indeksSoboty = 26;
	const int indeksSobStartGodz = 27;
	const int indeksSobStartMin = 28;
	const int indeksSobKoniecGodz = 29;
	const int indeksSobKoniecMin = 30;

	string calyPlik = czytaczGrafikuPracy->wczytajPlik();
	vector <string> grafikPracyWiesze = czytaczGrafikuPracy->zmaienNaWiersze(calyPlik);
	unordered_map<DniTygodnia, GodzinyPracy> grafikPracy;
	for (auto grafikPracyWiersz : grafikPracyWiesze) {
		string niePracuje = "-";
		string tekstId = czytaczGrafikuPracy->getPozycjaTextu(grafikPracyWiersz, indeksId);
		int id = stoi(tekstId);
		if (lekarz->getId() == id) {
			//poniedzialek
			string textPoniedzialekGodzStart = czytaczGrafikuPracy->getPozycjaTextu(grafikPracyWiersz, indeksPonStartGodz);
			if (textPoniedzialekGodzStart != niePracuje) {
				int poniedzialekGodzStart = stoi(textPoniedzialekGodzStart);
				string textPoniedzialekMinStart = czytaczGrafikuPracy->getPozycjaTextu(grafikPracyWiersz, indeksPonStartMin);
				int poniedzialekMinStart = stoi(textPoniedzialekMinStart);

				string textPoniedzialekGodzKoniec = czytaczGrafikuPracy->getPozycjaTextu(grafikPracyWiersz, indeksPonKoniecGodz);
				int poniedzialekGodzKoniec = stoi(textPoniedzialekGodzKoniec);
				string textPoniedzialekMinKoniec = czytaczGrafikuPracy->getPozycjaTextu(grafikPracyWiersz, indeksPonKoniecMin);
				int poniedzialekMinKoniec = stoi(textPoniedzialekMinKoniec);

				grafikPracy[DniTygodnia::Poniedzialek] = GodzinyPracy(poniedzialekGodzStart, poniedzialekMinStart, poniedzialekGodzKoniec, poniedzialekMinKoniec);
			}
			
			
			//wtorek
			string textWtorekGodzStart = czytaczGrafikuPracy->getPozycjaTextu(grafikPracyWiersz, indeksWtStartGodz);
			if (textWtorekGodzStart != niePracuje) {
				int wtorekGodzStart = stoi(textPoniedzialekGodzStart);
				string textWtorekMinStart = czytaczGrafikuPracy->getPozycjaTextu(grafikPracyWiersz, indeksWtStartMin);
				int wtorekMinStart = stoi(textWtorekMinStart);

				string textWtorekGodzKoniec = czytaczGrafikuPracy->getPozycjaTextu(grafikPracyWiersz, indeksWtKoniecGodz);
				int wtorekGodzKoniec = stoi(textWtorekGodzKoniec);
				string textWtorekMinKoniec = czytaczGrafikuPracy->getPozycjaTextu(grafikPracyWiersz, indeksWtKoniecMin);
				int wtorekMinKoniec = stoi(textWtorekMinKoniec);

				grafikPracy[DniTygodnia::Wtorek] = GodzinyPracy(wtorekGodzStart, wtorekMinStart, wtorekGodzKoniec, wtorekMinKoniec);
			}

			//sroda
			string textSrodaGodzStart = czytaczGrafikuPracy->getPozycjaTextu(grafikPracyWiersz, indeksSrStartGodz);
			if (textSrodaGodzStart != niePracuje) {
				string textSrodaGodzStart = czytaczGrafikuPracy->getPozycjaTextu(grafikPracyWiersz, indeksSrStartGodz);
				int srodaGodzStart = stoi(textSrodaGodzStart);
				string textSrodaMinStart = czytaczGrafikuPracy->getPozycjaTextu(grafikPracyWiersz, indeksSrStartMin);
				int srodaMinStart = stoi(textSrodaMinStart);

				string textSrodaGodzKoniec = czytaczGrafikuPracy->getPozycjaTextu(grafikPracyWiersz, indeksSrKoniecGodz);
				int srodaGodzKoniec = stoi(textSrodaGodzKoniec);
				string textSrodaMinKoniec = czytaczGrafikuPracy->getPozycjaTextu(grafikPracyWiersz, indeksSrKoniecMin);
				int srodaMinKoniec = stoi(textSrodaMinKoniec);

				grafikPracy[DniTygodnia::Sroda] = GodzinyPracy(srodaGodzStart, srodaMinStart, srodaGodzKoniec, srodaMinKoniec);
			}
			

			//czwartek
			string textCzwartekGodzStart = czytaczGrafikuPracy->getPozycjaTextu(grafikPracyWiersz, indeksCzwStartGodz);
			if (textPoniedzialekGodzStart != niePracuje) {
				int czwartekGodzStart = stoi(textCzwartekGodzStart);
				string textCzwartekMinStart = czytaczGrafikuPracy->getPozycjaTextu(grafikPracyWiersz, indeksCzwStartMin);
				int czwartekMinStart = stoi(textCzwartekMinStart);

				string textCzwartekGodzKoniec = czytaczGrafikuPracy->getPozycjaTextu(grafikPracyWiersz, indeksCzwKoniecGodz);
				int czwartekGodzKoniec = stoi(textCzwartekGodzKoniec);
				string textCzwartekMinKoniec = czytaczGrafikuPracy->getPozycjaTextu(grafikPracyWiersz, indeksCzwKoniecMin);
				int czwartekMinKoniec = stoi(textCzwartekMinKoniec);

				grafikPracy[DniTygodnia::Czwartek] = GodzinyPracy(czwartekGodzStart, czwartekMinStart, czwartekGodzKoniec, czwartekMinKoniec);
			}
			

			//piatek
			string textPiatekGodzStart = czytaczGrafikuPracy->getPozycjaTextu(grafikPracyWiersz, indeksPtStartGodz);
			if (textPiatekGodzStart != niePracuje) {
				int piatekGodzStart = stoi(textPiatekGodzStart);
				string textPiatekMinStart = czytaczGrafikuPracy->getPozycjaTextu(grafikPracyWiersz, indeksPtStartMin);
				int piatekMinStart = stoi(textPiatekMinStart);

				string textPiatekGodzKoniec = czytaczGrafikuPracy->getPozycjaTextu(grafikPracyWiersz, indeksPtKoniecGodz);
				int piatekGodzKoniec = stoi(textPiatekGodzKoniec);
				string textPiatekMinKoniec = czytaczGrafikuPracy->getPozycjaTextu(grafikPracyWiersz, indeksPtKoniecMin);
				int piatekMinKoniec = stoi(textPiatekMinKoniec);

				grafikPracy[DniTygodnia::Piatek] = GodzinyPracy(piatekGodzStart, piatekMinStart, piatekGodzKoniec, piatekMinKoniec);
			}
			
			//sobota
			string textSobotaGodzStart = czytaczGrafikuPracy->getPozycjaTextu(grafikPracyWiersz, indeksSobStartGodz);
			if (textSobotaGodzStart != niePracuje) {
				int sobotaGodzStart = stoi(textSobotaGodzStart);
				string textSobotaMinStart = czytaczGrafikuPracy->getPozycjaTextu(grafikPracyWiersz, indeksSobStartMin);
				int sobotaMinStart = stoi(textSobotaMinStart);

				string textSobotaGodzKoniec = czytaczGrafikuPracy->getPozycjaTextu(grafikPracyWiersz, indeksSobKoniecGodz);
				int sobotaGodzKoniec = stoi(textSobotaGodzKoniec);
				string textSobotaMinKoniec = czytaczGrafikuPracy->getPozycjaTextu(grafikPracyWiersz, indeksSobKoniecMin);
				int sobotaMinKoniec = stoi(textSobotaMinKoniec);

				grafikPracy[DniTygodnia::Sobota] = GodzinyPracy(sobotaGodzStart, sobotaMinStart, sobotaGodzKoniec, sobotaMinKoniec);
			}
		}
	}

	return grafikPracy;
}
