#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

struct Studentas {
	std::string vardas;
	std::string pavarde;
	std::vector<int> nd_pazymiai;
	int egz_pazymys{};
};

Studentas irasyti_studenta();
float vidurkis(std::vector<int> pazymiai);
float mediana(std::vector<int> pazymiai);
float galutinis(float paz_agg, int egz_paz);
std::vector<Studentas> irasyti_studentus();

int main() {
	std::setlocale(LC_ALL, "Lithuanian");

	std::vector<Studentas> stud = irasyti_studentus();
	for (auto s : stud)
		std::cout << mediana(s.nd_pazymiai) << " " << vidurkis(s.nd_pazymiai) << std::endl;

	return 0;
}

Studentas irasyti_studenta() {
	Studentas stud;

	std::cout << "Árağyti varda ir pavarde(ivedus vardà paspausti Enter):\n";
	std::cin >> stud.vardas >> stud.pavarde;

	int paz;
	std::cout << "Ávesti paşymius(norëdami uşbaigti, áveskite 0):\n";
	while (true) {
		std::cin >> paz;

		if (paz == 0)
			break;

		stud.nd_pazymiai.push_back(paz);
	}

	std::cout << "Áveskite egzamino paşymá:\n";
	std::cin >> stud.egz_pazymys;

	return stud;
}

std::vector<Studentas> irasyti_studentus() {
	std::vector<Studentas> sarasas;
	char testi{ 't' };

	while (true) {
		std::cout << "Árağyti studentà? (t/n)\n";
		std::cin >> testi;

		switch (testi)
		{
		case 't':
			sarasas.push_back(irasyti_studenta());
			break;
		case 'n':
			goto break_loop;
		default:
			break;
		}
	}
break_loop: return sarasas;
}

float vidurkis(std::vector<int> pazymiai) {
	int sum = 0;
	for (int paz : pazymiai)
		sum += paz;

	return ((float)sum) / (pazymiai.size());
}

float mediana(std::vector<int> pazymiai) {
	int ilgis = pazymiai.size();
	if (ilgis == 0)
		return 0.0;

	std::sort(pazymiai.begin(), pazymiai.end());


	if (ilgis % 2 == 1)
		return pazymiai.at(ilgis / 2);
	else
		return (pazymiai.at(ilgis / 2) + pazymiai.at(ilgis / 2 - 1)) / 2.0;
}

float galutinis(float paz_agg, int egz_paz) {
	return 0.4 * paz_agg + 0.6 * egz_paz;
}