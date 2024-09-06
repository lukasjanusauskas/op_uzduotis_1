#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <iomanip>
#include <random>
#include <time.h>

#define MAX_RAND_PAZ 10

struct Studentas {
	std::string vardas;
	std::string pavarde;
	std::vector<int> nd_pazymiai;
	int egz_pazymys{};
};

Studentas irasyti_studenta();
std::vector<Studentas> irasyti_studentus();
void spausdinti_stud_duom(Studentas stud);
void spausdinti_rezultatus(std::vector<Studentas> stud);

Studentas generuoti_rand_stud();
std::vector<Studentas> generuoti_atsitiktinius(unsigned int n);
//std::vector<Studentas> nuskaityti_faila();

float vidurkis(std::vector<int> pazymiai);
float mediana(std::vector<int> pazymiai);
float galutinis(float paz_agg, int egz_paz);

int main() {
	std::setlocale(LC_ALL, "Lithuanian");

	std::vector<Studentas> stud = generuoti_atsitiktinius(20);
	spausdinti_rezultatus(stud);

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

void spausdinti_stud_duom(Studentas stud) {
	float vid = vidurkis(stud.nd_pazymiai);
	float med = mediana(stud.nd_pazymiai);

	std::cout << stud.vardas << "\t" << stud.pavarde << "\t";
	std::cout << galutinis(vid, stud.egz_pazymys) << "\t\t" << galutinis(med, stud.egz_pazymys) << std::endl;
}

void spausdinti_rezultatus(std::vector<Studentas> stud) {
	std::cout << "Vardas\tPavardë\tGalutinis (vid.) / Galutinis(med.)\n";
	std::cout << "-----------------------------------------------------\n";
	std::cout << std::setprecision(2);
	for (auto s : stud)
		spausdinti_stud_duom(s);
}

Studentas generuoti_rand_stud() {
	std::string vardai[] = { "Lukas", "Petras", "Jonas", "Algis" };
	std::string pavard[] = { "Petraitis", "Jonaitis", "Kazlauskas", "Valanèiûnas" };

	int vardai_ilgis = sizeof(vardai) / sizeof(std::string);
	int pavard_ilgis = sizeof(pavard) / sizeof(std::string);

	Studentas s;
	s.vardas = vardai[rand() % vardai_ilgis];
	s.pavarde = pavard[rand() % pavard_ilgis];

	int paz_skaicius = rand() % MAX_RAND_PAZ;
	for (paz_skaicius; paz_skaicius > 0; paz_skaicius--)
		s.nd_pazymiai.push_back(rand() % 10 + 1);

	s.egz_pazymys = rand() % 10 + 1;

	return s;
}

std::vector<Studentas> generuoti_atsitiktinius(unsigned int n) {
	srand(time(0));

	std::vector<Studentas> stud;
	for (int i = 0; i < n; i++)
		stud.push_back(generuoti_rand_stud());

	return stud;
}