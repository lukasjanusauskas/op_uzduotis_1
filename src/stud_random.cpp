#include <random>
#include <stdlib.h>
#include <stdio.h>
#include <chrono>

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

	std::stringstream output;
	output << std::left << std::setw(20) << "Vardas"
					<< std::setw(20) << "Pavardė";

	for (int i = 0; i < paz_skaicius; i++)
		output << std::setw(6) << "ND" + std::to_string(i+1);
	output << "Egz.\n";

	for (int i = 0; i < n; i++){
		stud = generuoti_rand_stud(i, paz_skaicius);	
		output << std::setw(20) << stud.vardas 
		   << std::setw(20) << stud.pavarde;

		for(auto& p: stud.nd_pazymiai)
			output << std::setw(6) << p;

		output << stud.egz_pazymys << "\n";
	}

	std::ofstream fr(file);
	fr << output.str().c_str();
	fr.close();
}

void generuoti_penkis() {
	auto start = std::chrono::system_clock::now();
	generuoti_atsitiktinius("studentai1000.txt", 1000);
	auto end = std::chrono::system_clock::now();
	std::chrono::duration<double> elapsed = end - start;
	std::cout << "Generavimas užtruko" << elapsed.count() << "\n";

	start = std::chrono::system_clock::now();
	generuoti_atsitiktinius("studentai10000.txt", 10000);
	end = std::chrono::system_clock::now();
 	elapsed = end - start;
	std::cout << "Generavimas užtruko" << elapsed.count() << "\n";

	start = std::chrono::system_clock::now();
	generuoti_atsitiktinius("studentai100000.txt", 100000);
	end = std::chrono::system_clock::now();
 	elapsed = end - start;
	std::cout << "Generavimas užtruko" << elapsed.count() << "\n";

	start = std::chrono::system_clock::now();
	generuoti_atsitiktinius("studentai1000000.txt", 1000000);
	end = std::chrono::system_clock::now();
 	elapsed = end - start;
	std::cout << "Generavimas užtruko" << elapsed.count() << "\n";

	start = std::chrono::system_clock::now();
	generuoti_atsitiktinius("studentai10000000.txt", 10000000);
	end = std::chrono::system_clock::now();
 	elapsed = end - start;
	std::cout << "Generavimas užtruko" << elapsed.count() << std::endl;
}