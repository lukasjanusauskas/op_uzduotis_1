#ifndef STUDENTAS_H
#define STUDENTAS_H

#include <string>
#include <vector>

struct Studentas {
	std::string vardas;
	std::string pavarde;
	std::vector<int> nd_pazymiai;
	int egz_pazymys{};
	float galutinis;
};

Studentas irasyti_studenta();
std::vector<Studentas> irasyti_studentus();
void spausdinti_stud_duom(Studentas stud);
void spausdinti_rezultatus(std::vector<Studentas> stud);

#endif
