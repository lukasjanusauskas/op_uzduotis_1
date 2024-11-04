#include <algorithm>
#include <list>
#include <functional>
#include "studentas.h"
#include "skaiciavimai.h"

bool pagal_varda(Studentas pirmas, Studentas antras) { return pirmas.vardas.compare(antras.vardas) < 0; }
bool pagal_pavarde(Studentas pirmas, Studentas antras) { return pirmas.pavarde.compare(antras.vardas) < 0; }

void rikiuoti_studentus(std::vector<Studentas>& stud,
						std::function<bool(Studentas const&, Studentas const&)> func) {
	// Rikiavimas su custom metodu
	std::sort(stud.begin(), stud.end(), func);
}

void rikiuoti_studentus(std::list<Studentas>& stud,
							std::function<bool(Studentas const&, Studentas const&)> func) {
	// Rikiavimas su custom metodu
	stud.sort(func);
}

template <typename container>
void kategorizuoti1(container &stud, container &vargsai, container &galvos) {
	for(auto& s: stud){
		float med = mediana(s.nd_pazymiai);

		if(galutinis(med, s.egz_pazymys) < 5)
			vargsai.push_back(s);
		else
			galvos.push_back(s);
	}

	stud.clear();
}

template <typename container>
void kategorizuoti2(container &stud, container &vargsai, container &galvos) {
	auto it = stud.begin();

	while(it != stud.end()){
		float med = mediana(it->nd_pazymiai);

		if(galutinis(med, it->egz_pazymys) < 5){
			vargsai.push_back(*it);

			auto next = std::next(it, 1);
			stud.erase(it);

			it = next;
		}

		else it = next(it, 1);
	}

	galvos = stud;
}

template <typename container>
void kategorizuoti3(container &stud, container &vargsai, container &galvos) {
	for(auto& s: stud){
		float med = mediana(s.nd_pazymiai);

		if(galutinis(med, s.egz_pazymys) < 5)
			vargsai.push_back(s);
		else
			galvos.push_back(s);
	}

	stud.clear();
}