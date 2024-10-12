#include <iostream>
#include <iomanip>
#include <fstream>
#include <random>
#include <stdlib.h>
#include <stdio.h>
#include <chrono>

#include "studentas.h"
#include "timer.h"

#define MAX_RAND_PAZ 10

Studentas generuoti_rand_stud(int n_tasis,
							  int paz_skaicius,
							  std::mt19937 mt,
							  std::uniform_int_distribution<int> unif) {
	Studentas s;
	s.vardas = "Vardas" + std::to_string(n_tasis);
	s.pavarde = "Pavarde" + std::to_string(n_tasis);

	for (paz_skaicius; paz_skaicius > 0; paz_skaicius--)
		s.nd_pazymiai.push_back(unif(mt) + 1);

	s.egz_pazymys = unif(mt) + 1;

	return s;
}

void generuoti_atsitiktinius(std::string file, unsigned int n) {
	// Atsitiktinio studentu rinkinio genervaimas su vis kitokia "sekla", kad kas kart skirtusi rezultatas
	auto time_now = std::chrono::high_resolution_clock::now();
	std::mt19937 mt(time_now.time_since_epoch().count());
	std::uniform_int_distribution<int> unif(0, 9);

	Studentas stud;
	int paz_skaicius = unif(mt) + 3;

	std::stringstream output;
	output << std::left << std::setw(20) << "Vardas"
					<< std::setw(20) << "Pavardė";

	for (int i = 0; i < paz_skaicius; i++)
		output << std::setw(6) << "ND" + std::to_string(i+1);
	output << "Egz.\n";

	for (int i = 0; i < n; i++){
		stud = generuoti_rand_stud(i, paz_skaicius, mt, unif);	
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
	Timer t;
	// Ivedimas
	t.start_timer();
	generuoti_atsitiktinius("studentai1000.txt", 1000);
	std::cout << "1000 atsitiktinių generavimas užtruko " << t.get_time() << " s\n";

	t.restart_timer();
	generuoti_atsitiktinius("studentai10000.txt", 10000);
	std::cout << "10000 atsitiktinių generavimas užtruko " << t.get_time() << " s\n";

	t.restart_timer();
	generuoti_atsitiktinius("studentai100000.txt", 100000);
	std::cout << "100000 atsitiktinių generavimas užtruko " << t.get_time() << " s\n";

	t.restart_timer();
	generuoti_atsitiktinius("studentai1000000.txt", 1000000);
	std::cout << "1000000 atsitiktinių generavimas užtruko " << t.get_time() << " s\n";


	t.restart_timer();
	generuoti_atsitiktinius("studentai10000000.txt", 10000000);
	std::cout << "10000000 atsitiktinių generavimas užtruko " << t.get_time() << " s\n";
}
