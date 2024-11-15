#include <algorithm>
#include <list>
#include <functional>
#include "studentas.h"

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
void kategorizuoti(container &stud, container &vargsai, container &galvos) {
	for(auto& s: stud){
		float vid = vidurkis(s.nd_pazymiai);

		if(galutinis(vid, s.egz_pazymys) < 5)
			vargsai.push_back(s);
		else
			galvos.push_back(s);
	}

	stud.clear();
}