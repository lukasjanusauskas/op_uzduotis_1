#include <iostream>
#include <regex>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>
#include <iomanip>
#include <random>
#include <time.h>

#include "studentas.h"
#include "skaiciavimai.h"
#include "util.h"

#include "studentas_io.cpp"
#include "stud_random.cpp"
#include "stud_rikiavimas.cpp"

int main() {
	std::vector<Studentas> stud = nuskaityti_faila("kursiokai.txt");

	rikiuoti_studentus(stud);
	spausdinti_rezultatus(stud);

	return 0;
}