#include <iostream>
#include <fstream>
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
std::vector<Studentas> nuskaityti_faila(std::string failas);

float vidurkis(std::vector<int> pazymiai);
float mediana(std::vector<int> pazymiai);
float galutinis(float paz_agg, int egz_paz);

int main() {
	std::setlocale(LC_ALL, "Lithuanian"); // Lietuviu lokalizavimas

	std::vector<Studentas> stud = generuoti_atsitiktinius(25);
	spausdinti_rezultatus(stud);

	return 0;
}

Studentas irasyti_studenta() {
	// Vieno studento irasimas
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
	// Visu studentu irasimas komandineje eiluteje
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
			return sarasas;
		default:
			break;
		}
	}
}

float vidurkis(std::vector<int> pazymiai) {
	int sum = 0;
	for (int paz : pazymiai)
		sum += paz;
		
	float ret = ((float)sum) / (pazymiai.size());

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
	// Spausdinti vieno studento duomenis
	float vid = vidurkis(stud.nd_pazymiai);
	float med = mediana(stud.nd_pazymiai);

	std::cout << stud.vardas << "\t" << stud.pavarde << "\t";
	std::cout << galutinis(vid, stud.egz_pazymys) << "\t\t" << galutinis(med, stud.egz_pazymys) << std::endl;
}

void spausdinti_rezultatus(std::vector<Studentas> stud) {
	// Spausdinti visu studentu duomenis
	std::cout << "Vardas\tPavardë\tGalutinis (vid.) / Galutinis(med.)\n";
	std::cout << "-----------------------------------------------------\n";
	std::cout << std::setprecision(2);
	for (auto s : stud)
		spausdinti_stud_duom(s);
}

Studentas generuoti_rand_stud() {
	// Atsitiktinis studento generatorius
	std::string vardai[] = { "Lukas", "Petras", "Jonas", "Algis" };
	std::string pavard[] = { "Petraitis", "Jonaitis", "Kazlauskas", "Valanèiûnas" };

	int vardai_ilgis = sizeof(vardai) / sizeof(std::string);
	int pavard_ilgis = sizeof(pavard) / sizeof(std::string);

	Studentas s;
	s.vardas = vardai[rand() % vardai_ilgis];
	s.pavarde = pavard[rand() % pavard_ilgis];

	int paz_skaicius = rand() % MAX_RAND_PAZ + 1;
	for (paz_skaicius; paz_skaicius > 0; paz_skaicius--)
		s.nd_pazymiai.push_back(rand() % 10 + 1);

	s.egz_pazymys = rand() % 10 + 1;

	return s;
}

std::vector<Studentas> generuoti_atsitiktinius(unsigned int n) {
	// Atsitiktinio studentu rinkinio genervaimas
	srand(time(0));

	std::vector<Studentas> stud;
	for (int i = 0; i < n; i++)
		stud.push_back(generuoti_rand_stud());

	return stud;
}

std::vector<Studentas> nuskaityti_faila(std::string failas) {
	// Studentu suvedimas is failo

	std::vector<Studentas> stud;
	std::ifstream fr(failas);

	// Praleisti pirmaja eilute
	std::string tmp_str;
	std::getline(fr, tmp_str, '\n');

	while (!fr.eof()) {
		Studentas s;
		int nd_paz[5];

		fr >> s.vardas >> s.pavarde >> nd_paz[0] >> nd_paz[1] >> nd_paz[2] 
			>> nd_paz[3] >> nd_paz[4] >> s.egz_pazymys;
		s.nd_pazymiai.assign(nd_paz, nd_paz + 5);

		stud.push_back(s);
	}

	return stud;
}