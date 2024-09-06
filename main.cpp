#include <iostream>
#include <string>
#include <vector>

struct Studentas;
Studentas irasyti_studenta();
std::vector<Studentas> irasyti_studentus();

int main() {
	std::setlocale(LC_ALL, "Lithuanian");

	irasyti_studentus();

	return 0;
}

struct Studentas {
	std::string vardas;
	std::string pavarde;
	std::vector<int> nd_pazymiai;
	int egz_pazymys{};
};

Studentas irasyti_studenta() {
	Studentas stud;

	std::cout << "�ra�yti varda ir pavarde(ivedus vard� paspausti Enter):\n";
	std::cin >> stud.vardas >> stud.pavarde;

	int paz;
	std::cout << "�vesti pa�ymius(nor�dami u�baigti, �veskite 0):\n";
	while (true) {
		std::cin >> paz;

		if (paz == 0)
			break;

		stud.nd_pazymiai.push_back(paz);
	}

	std::cout << "�veskite egzamino pa�ym�:\n";
	std::cin >> stud.egz_pazymys;

	return stud;
}

std::vector<Studentas> irasyti_studentus() {
	std::vector<Studentas> sarasas;
	char testi{ 't' };

	while (true) {
		std::cout << "�ra�yti student�? (t/n)\n";
		std::cin >> testi;

		switch (testi)
		{
		case 't':
			sarasas.push_back(irasyti_studenta());
			continue;
		case 'n':
			goto break_loop;
		default:
			continue;
		}
	}
break_loop: return sarasas;
}