#include <algorithm>
#include <list>
#include <functional>
#include "studentas.h"
#include "skaiciavimai.h"

template <typename f>
void rikiuoti_studentus(std::vector<Studentas>& stud, f func) {
	std::sort(stud.begin(), stud.end(), func);
}

template <typename f>
void rikiuoti_studentus(std::list<Studentas>& stud, f func) {
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
void kategorizuoti3(container &stud, container  &vargsai, container &galvos) {
	// Partition
	auto it = std::partition(stud.begin(), stud.end(),
													 [](Studentas &s) { return s.galutinis < 5; });

	// Copy 
	vargsai.insert (vargsai.begin(), stud.begin(), it);
	galvos.insert (galvos.begin(), it, stud.end());
}