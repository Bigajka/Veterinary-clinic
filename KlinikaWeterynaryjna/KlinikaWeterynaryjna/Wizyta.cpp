#include "Wizyta.h"
#include <string>

Wizyta::Wizyta(DataGodzinaWizyty dataWizyty, int idWizyty, int idWlasciciela, int idZwierzecia, int idLekarza, string typUslugi)
{
	this->idWizyty = idWizyty;
	this->dataWizyty = dataWizyty;
	this->idLekarza = idLekarza;
	this->idWlasciciela = idWlasciciela;
	this->idZwierzecia = idZwierzecia;
	this->typUslugi = typUslugi;
}

string Wizyta::zamieNaTekst()
{
	return to_string(idWizyty) + "|" + to_string(idLekarza) + "|" + to_string(idWlasciciela) + "|" + to_string(idZwierzecia) + "|" + to_string(dataWizyty.getGodzina()) + "|" +
	 to_string(dataWizyty.getDzien()) + "|" + to_string(dataWizyty.getMiesiac())+ "|" + to_string(dataWizyty.getRok()) + "|" + typUslugi;

}

DataGodzinaWizyty Wizyta::getDataGodzina()
{
	return dataWizyty;
}

int Wizyta::getIdWizyty()
{
	return idWizyty;
}

int Wizyta::getIdWlasciciela()
{
	return idWlasciciela;
}

int Wizyta::getIdLekarza()
{
	return idLekarza;
}

int Wizyta::getIdZwierzecia()
{
	return idZwierzecia;
}

string Wizyta::getTypUslugi()
{
	return typUslugi;
}

string Wizyta::getData()
{
	string miesiacTekst;
	int miesiac = dataWizyty.getMiesiac();
	if (miesiac <= 9) {
		miesiacTekst = "0" + to_string(miesiac);
	}
	else {
		miesiacTekst = to_string(miesiac);
	}

	string dzienTekst;
	int dzien = dataWizyty.getDzien();
	if (dzien <= 9) {
		dzienTekst = "0" + to_string(dzien);
	}
	else {
		dzienTekst = to_string(dzien);
	}

	return dzienTekst + "-" + miesiacTekst + "-" + to_string(dataWizyty.getRok());
}

string Wizyta::getGodzina()
{
	string godzinaTekst;
	int godzina = dataWizyty.getGodzina();
	if (godzina <= 9) {
		godzinaTekst = "0" + to_string(godzina);
	}
	else {
		godzinaTekst = to_string(godzina);
	}
	return godzinaTekst + ":00";
}

DataGodzinaWizyty::DataGodzinaWizyty(int godzina, int dzien, int miesiac, int rok)
{
	this->godzina = godzina;
	this->dzien = dzien;
	this->miesiac = miesiac;
	this->rok = rok;
}

DataGodzinaWizyty::DataGodzinaWizyty()
{
}

int DataGodzinaWizyty::getDzien()
{
	return dzien;
}

int DataGodzinaWizyty::getMiesiac()
{
	return miesiac;
}

int DataGodzinaWizyty::getRok()
{
	return rok;
}

int DataGodzinaWizyty::getGodzina()
{
	return godzina;
}
