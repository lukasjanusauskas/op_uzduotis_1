#include "studentas.h"
#include "skaiciavimai.h"
#include "util.h"

#include "studentas_io.cpp"
#include "stud_random.cpp"
#include "stud_rikiavimas.cpp"

void testas();

int main() {
	std::setlocale(LC_ALL, "Lithuanian");

	testas();
	return 0;
}

void testas(){
	std::vector<Studentas> stud = nuskaityti_faila("studentai10000.txt");
	spausdinti_rezultatus(stud);
	stud = nuskaityti_faila("studentai100000.txt");
	spausdinti_rezultatus(stud);
	stud = nuskaityti_faila("studentai1000000.txt");
	spausdinti_rezultatus(stud);
}