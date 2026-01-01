#include "SesjaWlascicielaZwierzecia.h"
#include "WlascicielZwierzecia.h"


SesjaWlascicielaZwierzecia::SesjaWlascicielaZwierzecia(shared_ptr<WlascicielZwierzecia> wlascicielZwierzecia, vector<shared_ptr<Zwierze>> zwierzeta)
{
	this->wlascicielZwierzecia = wlascicielZwierzecia;
	this->zwierzetaUztkownika = zwierzeta;
}

vector<shared_ptr<Zwierze>> SesjaWlascicielaZwierzecia::getZwierzeta()
{
	return this->zwierzetaUztkownika;
}

shared_ptr<Zwierze> SesjaWlascicielaZwierzecia::getWybarneZwierze()
{
	return this->wybraneZwierze;
}

shared_ptr<WlascicielZwierzecia> SesjaWlascicielaZwierzecia::getWlasicielZwierzecia()
{
	return this->wlascicielZwierzecia;
}

void SesjaWlascicielaZwierzecia::setWybraneZwierze(shared_ptr<Zwierze> zwierze)
{
	this->wybraneZwierze = zwierze;
}

void SesjaWlascicielaZwierzecia::setWybranaUsluga(shared_ptr<Usluga> usluga)
{
	this->wybranaUsluga = usluga;
}

shared_ptr<Usluga> SesjaWlascicielaZwierzecia::getWybranaUsluga()
{
	return wybranaUsluga;
}

void SesjaWlascicielaZwierzecia::setWybranyMiesiac(shared_ptr<pair<int, time_t>> wybranyMeisiac)
{
	this->wybranyMiesiac = wybranyMeisiac;
}

shared_ptr<pair<int, time_t>> SesjaWlascicielaZwierzecia::getWybranyMiesiac()
{
	return wybranyMiesiac;
}

void SesjaWlascicielaZwierzecia::setWybranyDzien(shared_ptr<pair<int, time_t>> wybranyDzien)
{
	this->wybranyDzien = wybranyDzien;
}

shared_ptr<pair<int, time_t>> SesjaWlascicielaZwierzecia::getWybranyDzien()
{
	return wybranyDzien;
}

void SesjaWlascicielaZwierzecia::setWybranaGodzina(int wybranaGodzina)
{
	this->wybranaGodzina = wybranaGodzina;
}

shared_ptr<pair<int, time_t>> SesjaWlascicielaZwierzecia::getWybranyRok()
{
	return wybranyRok;
}

void SesjaWlascicielaZwierzecia::setWybranyRok(shared_ptr<pair<int, time_t>> wybranyRok)
{
	this->wybranyRok = wybranyRok;
}

int SesjaWlascicielaZwierzecia::getWybranaGodzina()
{
	return this->wybranaGodzina;
}

void SesjaWlascicielaZwierzecia::setIdWybranegoLekarza(int idLekarza)
{
	this->idWybranegoLekarza = idLekarza;
}

int SesjaWlascicielaZwierzecia::getIdWybranegoLekarza()
{
	return this->idWybranegoLekarza;
}

bool SesjaWlascicielaZwierzecia::czyMoznaUtworzycWizyte()
{
	return wybranaUsluga != nullptr && wybranyMiesiac != nullptr && wybranyDzien != nullptr && wybraneZwierze != nullptr && wybranaGodzina != 0 && idWybranegoLekarza != 0 ;
}

void SesjaWlascicielaZwierzecia::odswiezZwierzeta(vector<shared_ptr<Zwierze>> zwierzeta)
{
	this->zwierzetaUztkownika = zwierzeta;
}
