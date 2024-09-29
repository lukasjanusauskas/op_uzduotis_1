#include "studentas.h"
#include "skaiciavimai.h"
#include "util.h"

#include "studentas_io.cpp"
#include "stud_random.cpp"
#include "stud_rikiavimas.cpp"

#include <chrono>

void testas(std::string file_path);

int main() {
	std::setlocale(LC_ALL, "Lithuanian");
	// Generavimui:
	// generuoti_penkis();
	testas("studentai10000000.txt");

	return 0;
}

void testas(std::string file_path){
	// Ivedimas
	auto start = std::chrono::system_clock::now();

	std::vector<Studentas> stud = nuskaityti_faila_greitas(file_path);
	std::vector<Studentas> vargsai, galvos;

	auto end = std::chrono::system_clock::now();
	std::chrono::duration<double> elapsed = end - start;

	std::cout << "Nuskaitymas failo " << file_path << " užtruko " << elapsed.count() << "s\n";

	// Kategorizavimas
	start = std::chrono::system_clock::now();

	kategorizuoti(stud, vargsai, galvos);

	end = std::chrono::system_clock::now();
	elapsed = end - start;

	std::cout << "Kategorizavimas studentų iš failo " << file_path << " užtruko " << elapsed.count() << "s\n";

	// Isvedimas
	start = std::chrono::system_clock::now();

	isvesti_faila_greitas(vargsai, "vargsai.txt");
	isvesti_faila_greitas(galvos, "galvos.txt");

	end = std::chrono::system_clock::now();
	elapsed = end - start;

	std::cout << "Kateogrizuotų studentų iš " << file_path << " išvedimas užtruko " << elapsed.count() << "s\n";
}

void konsoles_dialogas(){
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