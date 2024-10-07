#include "studentas.h"
#include "skaiciavimai.h"
#include "util.h"

#include "studentas_io.cpp"
#include "stud_random.cpp"
#include "stud_rikiavimas.cpp"

#include <chrono>

void testas(std::string file_path);
void pasirinkti_rikiavima(std::vector<Studentas>& stud);

int main() {
	std::setlocale(LC_ALL, "Lithuanian");
	// Generavimui:
	// generuoti_penkis();
	testas("studentai1000.txt");
	std::cout << std::endl;
	testas("studentai10000.txt");
	testas("studentai100000.txt");
	testas("studentai1000000.txt");
	testas("studentai10000000.txt");

	return 0;
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
	start = std::chrono::system_clock::now();
	rikiuoti_studentus(stud, [](Studentas const& s1, Studentas const& s2){
									return s1.vardas.compare(s2.vardas) > 0;});

	end = std::chrono::system_clock::now();
	elapsed = end - start;

	std::cout << "Rikiavimas studentų iš failo " << file_path << " užtruko " << elapsed.count() << "s\n";

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
		stud = nuskaityti_faila("studentai10000.txt");
		break;
	
	default:
	 	goto input_option;
	}

	pasirinkti_rikiavima(stud);

	isvesti_faila(stud, "rezultatas.txt");
}

void pasirinkti_rikiavima(std::vector<Studentas>& stud){
	char input;
	std::chrono::time_point<std::chrono::system_clock> start, end;
	std::chrono::duration<double> elapsed;

 sort_option:
	std::cout << "Rikiuoti pagal: (v)ardus ar (p)avardes?\n";
	std::cin >> input;

	start = std::chrono::system_clock::now();
	switch (input)
	{
	case 'v':
		rikiuoti_studentus(stud, [](Studentas const& s1, Studentas const& s2){
										return s1.vardas.compare(s2.vardas) > 0;});
		break;

	case 'p':
		rikiuoti_studentus(stud, [](Studentas const& s1, Studentas const& s2){
										return s1.vardas.compare(s2.vardas) > 0;
									});
		break;
	
	default:
	 	goto sort_option;
	}

	end = std::chrono::system_clock::now();
	elapsed = end - start;
}