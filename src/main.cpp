#include "studentas.h"
#include "skaiciavimai.h"
#include "util.h"

#include "studentas_io.cpp"
#include "stud_random.cpp"
#include "stud_rikiavimas.cpp"

#include <chrono>

void testas();

int main() {
	std::setlocale(LC_ALL, "Lithuanian");

	testas();

	char input;
	std::vector<Studentas> stud;

//  input_option:

// 	std::cout << "Kaip įvesti studentus? Terminale - (t), Faile - (f)\n";
// 	std::cin >> input;

	// switch (input)
	// {
	// case 't':
	// 	stud = irasyti_studentus();
	// 	break;

	// case 'f':
	// 	stud = nuskaityti_faila("studentai10000.txt");
	// 	break;
	
	// default:
	//  	goto input_option;
	// }

	// isvesti_faila(stud, "rezultatas.txt");
	return 0;
}

void testas(){
	auto start = std::chrono::system_clock::now();

	std::vector<Studentas> stud = nuskaityti_faila_greitas("studentai10000.txt");

	auto end = std::chrono::system_clock::now();
	std::chrono::duration<double> elapsed = end - start;

	std::cout << elapsed.count() << std::endl;


	start = std::chrono::system_clock::now();

	stud = nuskaityti_faila_greitas("studentai10000.txt");

	end = std::chrono::system_clock::now();
	elapsed = end - start;

	std::cout << elapsed.count() << std::endl;
	isvesti_faila(stud, "stud100000.txt");
}