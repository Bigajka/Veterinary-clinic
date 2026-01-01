#include "WlascicielZwierzecia.h"


WlascicielZwierzecia::WlascicielZwierzecia(string imie, int id, string miasto, string kodPocztowy, string ulicaINumerDomu, string numerTelefonu, Uzytkownik& uzytkownik) : Uzytkownik(uzytkownik)
{
	
	this->imie = imie;
	this->id = id;
	this->miasto = miasto;
	this->kodPocztowy = kodPocztowy;
	this->ulicaINumerDomu = ulicaINumerDomu;
	this->numerTelefonu = numerTelefonu;
}

string WlascicielZwierzecia::getImie()
{
	return this->imie;
}

int WlascicielZwierzecia::getId()
{
	return this->id;
}

string WlascicielZwierzecia::getMiasto()
{
	return this->miasto;
}

string WlascicielZwierzecia::getKodPoczowy()
{
	return this->kodPocztowy;
}

string WlascicielZwierzecia::getUlicaINumerDomu()
{
	return this->ulicaINumerDomu;
}

string WlascicielZwierzecia::getNumerTelefonu()
{
	return this->numerTelefonu;
}

void WlascicielZwierzecia::setMiasto(string miasto)
{
	this->miasto = miasto;
}

void WlascicielZwierzecia::setKodPocztowy(string kodPocztowy)
{
	this->kodPocztowy = kodPocztowy;
}

void WlascicielZwierzecia::setUlicaINumerDomu(string ulicaINumerDomu)
{
	this->ulicaINumerDomu = ulicaINumerDomu;
}

void WlascicielZwierzecia::setNumerTelefonu(string numerTelefonu)
{
	this->numerTelefonu = numerTelefonu;
}
