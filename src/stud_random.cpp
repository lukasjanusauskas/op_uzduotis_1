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

void generuoti_atsitiktinius(std::string file, unsigned int n) {
	// Atsitiktinio studentu rinkinio genervaimas su vis kitokia "sekla", kad kas kart skirtusi rezultatas
	auto time_now = std::chrono::high_resolution_clock::now();
	std::random_device rd;
	std::mt19937 mt(rd());
	std::uniform_int_distribution<> unif(0, 9);

	Studentas s;
	int paz_skaicius = unif(mt) + 3;
	s.nd_pazymiai.reserve(paz_skaicius);

	std::stringstream output;
	output << std::left << std::setw(20) << "Vardas"
					<< std::setw(20) << "Pavardė";

	for (int i = 0; i < paz_skaicius; i++)
		output << std::setw(6) << "ND" + std::to_string(i+1);
	output << "Egz.\n";

	for (int i = 0; i < n; i++){
		s.vardas = "Vardas" + std::to_string(i);
		s.pavarde = "Pavarde" + std::to_string(i);

		s.nd_pazymiai.clear();
		s.nd_pazymiai.reserve(paz_skaicius);

		for (int i = paz_skaicius; i > 0; i--)
			s.nd_pazymiai.push_back(unif(mt) + 1);

		s.egz_pazymys = unif(mt) + 1;

		output << std::setw(20) << s.vardas 
		   << std::setw(20) << s.pavarde;

		for(auto& p: s.nd_pazymiai)
			output << std::setw(6) << p;

		output << s.egz_pazymys << "\n";
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
