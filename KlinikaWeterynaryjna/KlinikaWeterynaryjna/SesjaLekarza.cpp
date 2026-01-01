#include "SesjaLekarza.h"

SesjaLekarza::SesjaLekarza(shared_ptr<Lekarz> lekarz, shared_ptr<SerwisWizyt> serwisWizyt, shared_ptr<SerwisZwierzat> serwisZwierzat, shared_ptr<SerwisUslug> fabrykaUslug, shared_ptr<SerwisWlasicielaZwierzecia> serwisWlasicielaZwierzecia)
{
	this->lekarz = lekarz;
	this->serwisWizyt = serwisWizyt;
	this->serwisZwierzat = serwisZwierzat;
	this->serwisUslug = fabrykaUslug;
	this->serwisWlasicielaZwierzecia = serwisWlasicielaZwierzecia;
}

shared_ptr<Lekarz> SesjaLekarza::getLekarz()
{
	return lekarz;
}

shared_ptr<SerwisWizyt> SesjaLekarza::getSerwisWizyt()
{
	return serwisWizyt;
}

shared_ptr<SerwisZwierzat> SesjaLekarza::getSerwisZwierzat()
{
	return serwisZwierzat;
}

shared_ptr<SerwisUslug> SesjaLekarza::getFabrykaUslug()
{
	return serwisUslug;
}

shared_ptr<SerwisWlasicielaZwierzecia> SesjaLekarza::getSerwisWlasicielaZwierzecia()
{
	return serwisWlasicielaZwierzecia;
}
