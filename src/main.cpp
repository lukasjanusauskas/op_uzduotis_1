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
	// Generavimui:
	// generuoti_penkis();

	

	return 0;
}

void testas(){
	auto start = std::chrono::system_clock::now();

	auto end = std::chrono::system_clock::now();
	std::chrono::duration<double> elapsed = end - start;
}

void main01(){
	char input;
	std::vector<Studentas> stud;

input_option:

	std::cout << "Kaip įvesti studentus? Terminale - (t), Faile - (f)\n";
	std::cin >> input;

	switch (input)
	{
	case 't':
		stud = irasyti_studentus();
		break;

	case 'f':
		stud = nuskaityti_faila("studentai10000.txt");
		break;
	
	default:
	 	goto input_option;
	}

	isvesti_faila(stud, "rezultatas.txt");
}