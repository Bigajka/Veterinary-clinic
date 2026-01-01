#include "SerwisUslug.h"
#include "Usluga.h"

using namespace std;

shared_ptr<Usluga> SerwisUslug::znajdzPoTypie(string typ) {
	for (auto&& usluga : dostepneUslugi) {
		if (usluga->getTypUslugi() == typ) {
			return usluga;
		}
	}

	return shared_ptr<Usluga>(new Usluga(-1, "", ""));
}

SerwisUslug::SerwisUslug()
{
    zainicjalizujUslugi();
}

void SerwisUslug::zainicjalizujUslugi() {
    dostepneUslugi.push_back(shared_ptr<Usluga>(new Usluga(150, "Szczepienie ochronne", "SZCZEPIENIE_OCHRONNE")));
    dostepneUslugi.push_back(shared_ptr<Usluga>(new Usluga(250, "Operacja konczyn", "OPERACJA_KONCZYN")));
    dostepneUslugi.push_back(shared_ptr<Usluga>(new Usluga(100, "Wizyta kontrolna", "WIZYTA_KONTROLNA")));
    dostepneUslugi.push_back(shared_ptr<Usluga>(new Usluga(90, "Badania labolatoryjne", "BADANIA_LABOLATORYJNE")));
    dostepneUslugi.push_back(shared_ptr<Usluga>(new Usluga(75, "Obcinanie pazurow", "OBCINANIE_PAZUROW")));
    dostepneUslugi.push_back(shared_ptr<Usluga>(new Usluga(100, "Odrobaczywienie", "ODROBACZYWIENIE")));
    dostepneUslugi.push_back(shared_ptr<Usluga>(new Usluga(300, "Sterylizacja", "STERYLIZACJA")));
    dostepneUslugi.push_back(shared_ptr<Usluga>(new Usluga(300, "Kastracja", "KASTARCJA")));
    dostepneUslugi.push_back(shared_ptr<Usluga>(new Usluga(150, "Porod", "POROD")));
    dostepneUslugi.push_back(shared_ptr<Usluga>(new Usluga(250, "Rehabilitacja", "REHABILITACJA")));
    dostepneUslugi.push_back(shared_ptr<Usluga>(new Usluga(185, "Stabilizacja zlaman", "STABILIZACJA_ZLAMAN")));
    dostepneUslugi.push_back(shared_ptr<Usluga>(new Usluga(120, "USG", "USG")));
    dostepneUslugi.push_back(shared_ptr<Usluga>(new Usluga(85, "Strzyzenie siersci", "STRZYZENIE_SIERSCI")));
    dostepneUslugi.push_back(shared_ptr<Usluga>(new Usluga(165, "Korekta dzioba", "KOREKTA_DZIOBA")));
    dostepneUslugi.push_back(shared_ptr<Usluga>(new Usluga(150, "Nastawienie skrzydla", "NASTAWIENIE_SKRZYDLA")));
    dostepneUslugi.push_back(shared_ptr<Usluga>(new Usluga(200, "Zalozenie obraczki rejestrujacej", "ZAKLADANIE_OBRACZKI")));
    dostepneUslugi.push_back(shared_ptr<Usluga>(new Usluga(150, "Zalozenie chipa namierzajacego", "ZAKLADANIE_CHIPA")));
    dostepneUslugi.push_back(shared_ptr<Usluga>(new Usluga(200, "Korekta odnozy", "KOREKTA_ODNOZY")));
    dostepneUslugi.push_back(shared_ptr<Usluga>(new Usluga(150, "Szczepienie na roztocza", "SZCZEPIENIE_PRZECIWKO_ROZTOCZA")));
    dostepneUslugi.push_back(shared_ptr<Usluga>(new Usluga(185, "Sciagniecie wylinki", "SCIAGNIECIE_WYLINKI")));
    dostepneUslugi.push_back(shared_ptr<Usluga>(new Usluga(250, "Sciagniecie jadu", "SCIAGNIECIE_JADU")));
}

vector<shared_ptr<Usluga>> SerwisUslug::stworzUslugeDlaZwierzaka(shared_ptr<Zwierze> zwierze) {
    if (Pies* piek = dynamic_cast<Pies*>(zwierze.get())) {
        vector< shared_ptr<Usluga>> listaUslugDlaPsa;
        listaUslugDlaPsa.push_back(znajdzPoTypie("SZCZEPIENIE_OCHRONNE"));
        listaUslugDlaPsa.push_back(znajdzPoTypie("OPERACJA_KONCZYN"));
        listaUslugDlaPsa.push_back(znajdzPoTypie("BADANIA_LABOLATORYJNE"));
        listaUslugDlaPsa.push_back(znajdzPoTypie("OBCINANIE_PAZUROW"));
        listaUslugDlaPsa.push_back(znajdzPoTypie("ODROBACZYWIENIE"));
        if (zwierze->getPlec() == SAMICA) {
            listaUslugDlaPsa.push_back(znajdzPoTypie("STERYLIZACJA"));
        }
        else if (zwierze->getPlec() == SAMIEC) {
            listaUslugDlaPsa.push_back(znajdzPoTypie("KASTARCJA"));
        }
        listaUslugDlaPsa.push_back(znajdzPoTypie("POROD"));
        listaUslugDlaPsa.push_back(znajdzPoTypie("REHABILITACJA"));
        listaUslugDlaPsa.push_back(znajdzPoTypie("STABILIZACJA_ZLAMAN"));
        listaUslugDlaPsa.push_back(znajdzPoTypie("USG"));
        listaUslugDlaPsa.push_back(znajdzPoTypie("STRZYZENIE_SIERSCI"));
        return listaUslugDlaPsa;
    }
    else if (Kot* kot = dynamic_cast<Kot*>(zwierze.get())) {
        vector< shared_ptr<Usluga>> listaUslugDlaKota;
        listaUslugDlaKota.push_back(znajdzPoTypie("SZCZEPIENIE_OCHRONNE"));
        listaUslugDlaKota.push_back(znajdzPoTypie("OPERACJA_KONCZYN"));
        listaUslugDlaKota.push_back(znajdzPoTypie("BADANIA_LABOLATORYJNE"));
        listaUslugDlaKota.push_back(znajdzPoTypie("OBCINANIE_PAZUROW"));
        listaUslugDlaKota.push_back(znajdzPoTypie("ODROBACZYWIENIE"));
        if (zwierze->getPlec() == SAMICA) {
            znajdzPoTypie("STERYLIZACJA");
        }
        else if (zwierze->getPlec() == SAMIEC) {
            znajdzPoTypie("KASTARCJA");
        }
        listaUslugDlaKota.push_back(znajdzPoTypie("POROD"));
        listaUslugDlaKota.push_back(znajdzPoTypie("REHABILITACJA"));
        listaUslugDlaKota.push_back(znajdzPoTypie("STABILIZACJA_ZLAMAN"));
        listaUslugDlaKota.push_back(znajdzPoTypie("USG"));
        listaUslugDlaKota.push_back(znajdzPoTypie("STRZYZENIE_SIERSCI"));
        listaUslugDlaKota.push_back(znajdzPoTypie("ZAKLADANIE_CHIPA"));
        return listaUslugDlaKota;
    }
    else if (Kanarek* kanarek = dynamic_cast<Kanarek*>(zwierze.get())) {
        vector< shared_ptr<Usluga>> listaUslugDlaKanarka;
        listaUslugDlaKanarka.push_back(znajdzPoTypie("SZCZEPIENIE_OCHRONNE"));
        listaUslugDlaKanarka.push_back(znajdzPoTypie("OPERACJA_KONCZYN"));
        listaUslugDlaKanarka.push_back(znajdzPoTypie("BADANIA_LABOLATORYJNE"));
        listaUslugDlaKanarka.push_back(znajdzPoTypie("KOREKTA_DZIOBA"));
        listaUslugDlaKanarka.push_back(znajdzPoTypie("NASTAWIENIE_SKRZYDLA"));
        listaUslugDlaKanarka.push_back(znajdzPoTypie("ZAKLADANIE_OBRACZKI"));
        listaUslugDlaKanarka.push_back(znajdzPoTypie("ZAKLADANIE_CHIPA"));
        return listaUslugDlaKanarka;
    }
    else if (Pajak* pajak = dynamic_cast<Pajak*>(zwierze.get())) {
        vector<shared_ptr<Usluga>> listaUslugDlaPajaka;
        listaUslugDlaPajaka.push_back(znajdzPoTypie("SZCZEPIENIE_OCHRONNE"));
        listaUslugDlaPajaka.push_back(znajdzPoTypie("OPERACJA_KONCZYN"));
        listaUslugDlaPajaka.push_back(znajdzPoTypie("BADANIA_LABOLATORYJNE"));
        listaUslugDlaPajaka.push_back(znajdzPoTypie("KOREKTA_ODNOZY"));
        listaUslugDlaPajaka.push_back(znajdzPoTypie("SZCZEPIENIE_PRZECIWKO_ROZTOCZA"));
        return listaUslugDlaPajaka;
    }
    else if (Waz* waz = dynamic_cast<Waz*>(zwierze.get())) {
        vector< shared_ptr<Usluga>> listaUslugDlaWeza;
        listaUslugDlaWeza.push_back(znajdzPoTypie("SZCZEPIENIE_OCHRONNE"));
        listaUslugDlaWeza.push_back(znajdzPoTypie("OPERACJA_KONCZYN"));
        listaUslugDlaWeza.push_back(znajdzPoTypie("BADANIA_LABOLATORYJNE"));
        listaUslugDlaWeza.push_back(znajdzPoTypie("SCIAGNIECIE_WYLINKI"));
        listaUslugDlaWeza.push_back(znajdzPoTypie("SCIAGNIECIE_JADU"));
        return listaUslugDlaWeza;
    }
    else {
        vector< shared_ptr<Usluga>> pustaListaUslug;
        return pustaListaUslug;
    }
}

