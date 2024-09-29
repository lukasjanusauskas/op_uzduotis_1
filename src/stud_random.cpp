#include <random>
#include <stdlib.h>
#include <stdio.h>

#include "studentas.h"

#define MAX_RAND_PAZ 10

Studentas generuoti_rand_stud(int n_tasis, int paz_skaicius) {
	// rand() * vardai_ilgis duoda pseudo-atsitiktini indeksa
	Studentas s;
	s.vardas = "Vardas" + std::to_string(n_tasis);
	s.pavarde = "Pavarde" + std::to_string(n_tasis);

	// rand() % MAX_RAND_PAZ duoda naturalu skaiciu [0, MAX_RAND_PAX)
	// Taigi reikia prideti vieneta
	for (paz_skaicius; paz_skaicius > 0; paz_skaicius--)
		s.nd_pazymiai.push_back(rand() % 10 + 1);

	s.egz_pazymys = rand() % 10 + 1;

	return s;
}

void generuoti_atsitiktinius(std::string file, unsigned int n) {
	// Atsitiktinio studentu rinkinio genervaimas su vis kitokia "sekla", kad kas kart skirtusi rezultatas
	srand(time(0));

	Studentas stud;
	int paz_skaicius = rand() % MAX_RAND_PAZ + 3; // Minimum trys namu darbai

	std::ofstream fr(file);
	fr << std::left << std::setw(20) << "Vardas"
					<< std::setw(20) << "Pavardė";

	for (int i = 0; i < paz_skaicius; i++)
		fr << std::setw(6) << "ND" + std::to_string(i+1);
	fr << "Egz.";

	for (int i = 0; i < n; i++){
		stud = generuoti_rand_stud(i, paz_skaicius);	
		fr << std::setw(20) << stud.vardas 
		   << std::setw(20) << stud.pavarde;

		for(auto& p: stud.nd_pazymiai)
			fr << std::setw(6) << p;

		fr << stud.egz_pazymys << "\n";
	}
}

void generuoti_penkis() {
	std::vector<Studentas> stud;

	generuoti_atsitiktinius("studentai1000.txt", 1000);
	generuoti_atsitiktinius("studentai10000.txt", 10000);
	generuoti_atsitiktinius("studentai100000.txt", 100000);
	generuoti_atsitiktinius("studentai1000000.txt", 1000000);
	generuoti_atsitiktinius("studentai10000000.txt", 10000000);
}