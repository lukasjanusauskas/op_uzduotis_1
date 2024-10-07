#include <algorithm>
#include "studentas.h"

bool pagal_varda(Studentas pirmas, Studentas antras) { return pirmas.vardas.compare(antras.vardas) < 0; }
bool pagal_pavarde(Studentas pirmas, Studentas antras) { return pirmas.pavarde.compare(antras.vardas) < 0; }

void rikiuoti_studentus(std::vector<Studentas>& stud, std::function<bool(Studentas const&, Studentas const&)> func) {
	// Rikiavimas su custom metodu
	std::sort(stud.begin(), stud.end(), func);
}

void kategorizuoti(std::vector<Studentas> stud){
    std::vector<Studentas> vargsai;
    std::vector<Studentas> galvos;

    for(auto& s: stud){
        float med = mediana(s.nd_pazymiai);
		std::cout << s.vardas << std::endl;

        if(galutinis(med, s.egz_pazymys) >= 5.0)
            vargsai.push_back(s);
        else
            galvos.push_back(s);
    }

    stud.clear();
}

void kategorizuoti(std::vector<Studentas> stud, std::vector<Studentas>& vargsai, std::vector<Studentas>& galvos) {
	for(auto& s: stud){
		float med = mediana(s.nd_pazymiai);

		if(galutinis(med, s.egz_pazymys) < 5)
			vargsai.push_back(s);
		else
			galvos.push_back(s);
	}

	stud.clear();
}