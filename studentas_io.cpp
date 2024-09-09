#include <iostream>
#include <fstream>
#include <regex>
#include <iomanip>

#include "studentas.h"
#include "skaiciavimai.cpp"

Studentas irasyti_studenta() {
	// Vieno studento irasymas
	Studentas stud;

	std::cout << "�ra�yti varda ir pavarde(ivedus vard� paspausti Enter):\n";
	std::cin >> stud.vardas >> stud.pavarde;

	int paz;
	std::cout << "�vesti pa�ymius(nor�dami u�baigti, �veskite 0):\n";
	while (true) {
		std::cin >> paz;

		if (paz == 0) // Irasoma, kol nepaspaudzia 0
			break;

		stud.nd_pazymiai.push_back(paz);
	}

	std::cout << "�veskite egzamino pa�ym�:\n";
	std::cin >> stud.egz_pazymys;

	return stud;
}

std::vector<Studentas> irasyti_studentus() {
	// Visu studentu irasimas komandineje eiluteje
	std::vector<Studentas> sarasas;
	char testi{ 't' };

	while (true) {
		std::cout << "�ra�yti student�? (t/n)\n";
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
						   << std::setw(15) << "Pavard�" 
						   << "Galutinis (vid.) " << "Galutinis(med.)\n ";
	std::cout << "-------------------------------------------------------\n";
	// Nustatomas tikslumas ir tik tada spausdinama
	std::cout << std::fixed << std::setprecision(2);
	for (auto& s : stud)
		spausdinti_stud_duom(s);
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
