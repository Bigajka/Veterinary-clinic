#include "MenuLogowania.h"
#include <iostream>

using namespace std;
string MenuLogowania::getLogin()
{
	return login;
}

string MenuLogowania::getHaslo()
{
	return haslo;
}

MenuLogowaniaStatusu MenuLogowania::wyswietlMenuPoczatkowe()
{
	cout << "Wcisnij 1, zeby sie zalogowac lub 0 aby wyjsc" << endl;
	string wybranaOpcja;
	std::cin >> wybranaOpcja;
	if (wybranaOpcja == "0") {
		return MenuLogowaniaStatusu::WYBRANO_WYSJSCIE;
	}
	else if (wybranaOpcja == "1") {
		return MenuLogowaniaStatusu::WYBRANO_LOGOWANIE;
	}
	else {
		cout << "Podales bledna opcje";
		return MenuLogowaniaStatusu::BLAD_WYBRANEJ_OPCJI;
	}
}

void MenuLogowania::wyswietMenuLogowania() {
	cout << "Podaj logi i haslo:" << endl;
	std::cin >> login >> haslo;
}
