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

	std::vector<Studentas> stud = nuskaityti_faila_greitas("studentai1000.txt");
	std::vector<Studentas> vargsai, galvos;

	kategorizuoti(stud, vargsai, galvos);
	std::cout << "Baigta kategorizuot\n";

	isvesti_faila_greitas(vargsai, "vargsai.txt");
	isvesti_faila_greitas(galvos, "galvos.txt");

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