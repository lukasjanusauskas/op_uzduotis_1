#include "studentas.h"
#include "skaiciavimai.h"
#include "util.h"

#include "studentas_io.cpp"
#include "stud_random.cpp"
#include "stud_rikiavimas.cpp"

#include <chrono>

void testas(std::string file_path);
void konsoles_dialogas();
void testuoti_eiga();
void testuoti_generavima();

int main() {
	// generuoti_penkis();
	konsoles_dialogas();

	return 0;
}

void testuoti_generavima(){
	for(int i = 0; i < 5; i++){
		generuoti_penkis();
	}
}

void testuoti_eiga(){
	testas("studentai1000.txt");
	testas("studentai10000.txt");
	testas("studentai100000.txt");
	testas("studentai1000000.txt");
	testas("studentai10000000.txt");
}

void testas(std::string file_path){
	std::vector<Studentas> stud;
	std::vector<Studentas> vargsai, galvos;

	// Ivedimas
	auto start = std::chrono::system_clock::now();

	stud = nuskaityti_faila_greitas(file_path);

	auto end = std::chrono::system_clock::now();
	std::chrono::duration<double> elapsed = end - start;

	std::cout << "Nuskaitymas failo " << file_path << " užtruko " << elapsed.count() << "s\n";

	// Rikiavimas
	pasirinkti_rikiavima(stud, file_path);

	end = std::chrono::system_clock::now();
	elapsed = end - start;

	// Kategorizavimas
	start = std::chrono::system_clock::now();

	kategorizuoti(stud, vargsai, galvos);

	std::cout << "Kategorizavimas studentų iš failo " << file_path << " užtruko " << elapsed.count() << "s\n";

	// Isvedimas
	start = std::chrono::system_clock::now();

	isvesti_faila_greitas(vargsai, "vargsai.txt");
	isvesti_faila_greitas(galvos, "galvos.txt");

	end = std::chrono::system_clock::now();
	elapsed = end - start;

	std::cout << "Kateogrizuotų studentų iš " << file_path << " išvedimas užtruko " << elapsed.count() << "s\n";
	std::cout << std::endl;
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
	 	testas("studentai1000000.txt");
		break;
	
	default:
	 	goto input_option;
	}
}

void pasirinkti_rikiavima(std::vector<Studentas>& stud, std::string file_path){
	char input;
	std::chrono::time_point<std::chrono::system_clock> start, end;
	std::chrono::duration<double> elapsed;

 sort_option:
	std::cout << "Rikiuoti pagal: (v)ardus ar (p)avardes?\n";
	std::cin >> input;

	switch (input)
	{
	case 'v':
		start = std::chrono::system_clock::now();

		rikiuoti_studentus(stud, [](Studentas const& s1, Studentas const& s2){
										return s1.vardas.compare(s2.vardas) > 0;});

		end = std::chrono::system_clock::now();
		elapsed = end - start;
		break;

	case 'p':
		start = std::chrono::system_clock::now();

		rikiuoti_studentus(stud, [](Studentas const& s1, Studentas const& s2){
										return s1.vardas.compare(s2.vardas) > 0;
									});

		end = std::chrono::system_clock::now();
		elapsed = end - start;
		break;
	
	default:
	 	goto sort_option;
	}

	std::cout << "Rikiavimas studentų iš failo " << file_path << " užtruko " << elapsed.count() << "s\n";
}