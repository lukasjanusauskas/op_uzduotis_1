#include <iostream>
#include <regex>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>
#include <iomanip>
#include <random>
#include <time.h>

#include "studentas.h"
#include "skaiciavimai.h"
#include "util.h"

#define MAX_RAND_PAZ 10

int main() {
	std::vector<Studentas> stud = nuskaityti_faila("kursiokai.txt");

	rikiuoti_studentus(stud);
	spausdinti_rezultatus(stud);

	return 0;
}

Studentas irasyti_studenta() {
	// Vieno studento irasymas
	Studentas stud;

	std::cout << "Árağyti varda ir pavarde(ivedus vardà paspausti Enter):\n";
	std::cin >> stud.vardas >> stud.pavarde;

	int paz;
	std::cout << "Ávesti paşymius(norëdami uşbaigti, áveskite 0):\n";
	while (true) {
		std::cin >> paz;

		if (paz == 0) // Irasoma, kol nepaspaudzia 0
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
		// Jei nuspaudzia 't', ivyksta irsaymas
		case 't':
			sarasas.push_back(irasyti_studenta());
			break;
		// Jei nuspaudzia 'n', grazinama, nevyksta irasymas
		case 'n':
			return sarasas;
		// Jei nuspaudzia kazka kito, kartojamas klausimas
		default:
			break;
		}
	}
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

	// Klasikine medianos formule
	// Jei vektoriaus ilgis nelyginis, paimamas floor(n/2) (arba paparastai: vidurinis)
	// Jei lyginis, paimamas viduriniu vidurkis
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

	// Spausdinama, nustatant plocio minimuma(kuris retai virsijamas, tai beveik visada toks ir yra)
	std::cout << std::setw(10) << stud.vardas
			  << std::setw(15) << stud.pavarde;
	std::cout << std::left
			  << std::setw(17) << galutinis(vid, stud.egz_pazymys) 
			  << std::setw(17) << galutinis(med, stud.egz_pazymys) << std::endl;
}

void spausdinti_rezultatus(std::vector<Studentas> stud) {
	// Spausdinti visu studentu duomenis
	std::cout << std::left << std::setw(10) << "Vardas" 
						   << std::setw(15) << "Pavardë" 
						   << "Galutinis (vid.) " << "Galutinis(med.)\n ";
	std::cout << "-------------------------------------------------------\n";
	// Nustatomas tikslumas ir tik tada spausdinama
	std::cout << std::fixed << std::setprecision(2);
	for (auto& s : stud)
		spausdinti_stud_duom(s);
}

Studentas generuoti_rand_stud() {
	// Atsitiktinis studento generatorius
	std::string vardai[] = { "Lukas", "Petras", "Jonas", "Algis" };
	std::string pavard[] = { "Petraitis", "Jonaitis", "Kazlauskas", "Valanèiûnas" };

	// Apskaiciuojami masyvu ilgiai
	int vardai_ilgis = sizeof(vardai) / sizeof(std::string);
	int pavard_ilgis = sizeof(pavard) / sizeof(std::string);

	// rand() * vardai_ilgis duoda pseudo-atsitiktini indeksa
	Studentas s;
	s.vardas = vardai[rand() % vardai_ilgis];
	s.pavarde = pavard[rand() % pavard_ilgis];

	// rand() % MAX_RAND_PAZ duoda naturalu skaiciu [0, MAX_RAND_PAX)
	// Taigi reikia prideti vieneta
	int paz_skaicius = rand() % MAX_RAND_PAZ + 1;
	for (paz_skaicius; paz_skaicius > 0; paz_skaicius--)
		s.nd_pazymiai.push_back(rand() % 10 + 1);

	s.egz_pazymys = rand() % 10 + 1;

	return s;
}

std::vector<Studentas> generuoti_atsitiktinius(unsigned int n) {
	// Atsitiktinio studentu rinkinio genervaimas su vis kitokia "sekla", kad kas kart skirtusi rezultatas
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

	// Nuskaityti failo antraste(stulpelius)
	// Parasyta su prielaida, kad pirmi du stulpeliai: Vardas, Pavarde, o paskutinis: Egz.
	std::string header_str;
	std::getline(fr, header_str, '\n');
	
	int nd_skaicius = 0;

	// Nuskaitomas namu darbu kiekis su regex
	// Daroma prielaida, kad namu darbu stulpeliai zymimi ND(skaicius)
	const std::regex reg_expr("ND\\d+");

	auto iterator = std::sregex_iterator(header_str.begin(), header_str.end(), reg_expr);
	auto empty = std::sregex_iterator();

	nd_skaicius = std::distance(iterator, empty);

	// Skaitomos eilutes, kol neprieis failo galo
	while (!fr.eof()) {
		Studentas s;

		fr >> s.vardas >> s.pavarde;

		int tmp_paz;
		for (int i = 0; i < nd_skaicius; i++) {
			fr >> tmp_paz;
			s.nd_pazymiai.push_back(tmp_paz);
		}
		fr >> s.egz_pazymys;

		stud.push_back(s);
	}

	return stud;
}

bool palyginti_rikiavimui(Studentas pirmas, Studentas antras) {
	// Eilutems lyginti naudojame compare metoda
	int cmp = pirmas.vardas.compare(antras.vardas);

	// Jei lygios eilutes, lyginam pavardes
	if (cmp == 0)
		return pirmas.pavarde.compare(antras.pavarde) < 0;

	// Jei nelygios, grazinam rezultata
	else
		return cmp < 0;
}

void rikiuoti_studentus(std::vector<Studentas>& stud) {
	// Rikiavimas su custom metodu
	std::sort(stud.begin(), stud.end(), &palyginti_rikiavimui);
}