#include <algorithm>
#include <functional>
#include "studentas.h"

bool pagal_varda(Studentas pirmas, Studentas antras) { return pirmas.vardas.compare(antras.vardas) < 0; }
bool pagal_pavarde(Studentas pirmas, Studentas antras) { return pirmas.pavarde.compare(antras.vardas) < 0; }

template <typename container>
void rikiuoti_studentus(container& stud, std::function<bool(Studentas const&, Studentas const&)> func) {
	// Rikiavimas su custom metodu
	std::sort(stud.begin(), stud.end(), func);
}

template <typename container>
void kategorizuoti(container &stud, container &vargsai, container &galvos) {
	for(auto& s: stud){
		float med = mediana(s.nd_pazymiai);

		if(galutinis(med, s.egz_pazymys) < 5)
			vargsai.push_back(s);
		else
			galvos.push_back(s);
	}

	stud.clear();
}