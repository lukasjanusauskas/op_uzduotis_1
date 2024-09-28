#include <random>

#include "studentas.h"

#define MAX_RAND_PAZ 10

Studentas generuoti_rand_stud(int n_tasis, int paz_skaicius) {
	// Atsitiktinis studento generatorius
	std::string vardai[] = { "Lukas", "Petras", "Jonas", "Algis" };
	std::string pavard[] = { "Petraitis", "Jonaitis", "Kazlauskas", "Valančiūnas" };

	// Apskaiciuojami masyvu ilgiai
	int vardai_ilgis = sizeof(vardai) / sizeof(std::string);
	int pavard_ilgis = sizeof(pavard) / sizeof(std::string);

	// rand() * vardai_ilgis duoda pseudo-atsitiktini indeksa
	Studentas s;
	s.vardas = vardai[rand() % vardai_ilgis] + std::to_string(n_tasis);
	s.pavarde = pavard[rand() % pavard_ilgis] + std::to_string(n_tasis);

	// rand() % MAX_RAND_PAZ duoda naturalu skaiciu [0, MAX_RAND_PAX)
	// Taigi reikia prideti vieneta
	for (paz_skaicius; paz_skaicius > 0; paz_skaicius--)
		s.nd_pazymiai.push_back(rand() % 10 + 1);

	s.egz_pazymys = rand() % 10 + 1;

	return s;
}

std::vector<Studentas> generuoti_atsitiktinius(unsigned int n) {
	// Atsitiktinio studentu rinkinio genervaimas su vis kitokia "sekla", kad kas kart skirtusi rezultatas
	srand(time(0));

	std::vector<Studentas> stud;
	int paz_skaicius = rand() % MAX_RAND_PAZ + 1;

	for (int i = 0; i < n; i++)
		stud.push_back(generuoti_rand_stud(i, paz_skaicius));

	return stud;
}

void generuoti_penkis() {
	std::vector<Studentas> stud;

	stud = generuoti_atsitiktinius(1000);
	isvesti_faila(stud, "studentai1000.txt");

	stud = generuoti_atsitiktinius(10000);
	isvesti_faila(stud, "studentai10000.txt");

	stud = generuoti_atsitiktinius(100000);
	isvesti_faila(stud, "studentai100000.txt");

	stud = generuoti_atsitiktinius(1000000);
	isvesti_faila(stud, "studentai1000000.txt");

	stud = generuoti_atsitiktinius(10000000);
	isvesti_faila(stud, "studentai10000000.txt");
}