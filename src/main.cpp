#include "studentas.h"
#include "skaiciavimai.h"
#include "util.h"

#include "studentas_io.cpp"
#include "stud_random.cpp"
#include "stud_rikiavimas.cpp"

int main() {
	std::setlocale(LC_ALL, "Lithuanian");
	std::vector<Studentas> stud = nuskaityti_faila("studentai10000.txt");

	spausdinti_rezultatus(stud);

	return 0;
}