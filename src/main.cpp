#include "studentas.h"
#include "skaiciavimai.h"
#include "util.h"

#include "studentas_io.cpp"
#include "stud_random.cpp"
#include "stud_rikiavimas.cpp"
#include "timer.cpp"

#include <chrono>

void testas(std::string file_path);
void pasirinkti_rikiavima(std::vector<Studentas>& stud);
void konsoles_dialogas();
void testuoti_eiga();
void testuoti_generavima();

int main() {
	// generuoti_penkis();
	// testuoti_eiga();
	testuoti_eiga();

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

	Timer t;
	// Ivedimas
	t.start_timer();
	stud = nuskaityti_faila_greitas(file_path);
	std::cout << "Nuskaitymas failo " << file_path << " užtruko " << t.get_time() << " s\n";

	// Rikiavimas
	t.restart_timer();
	rikiuoti_studentus(stud, [](Studentas const& s1, Studentas const& s2){
									return s1.vardas.compare(s2.vardas) > 0;});
	std::cout << "Rikiavimas " << file_path << " užtruko " << t.get_time() << " s\n";

	// Kategorizavimas
	t.restart_timer();
	kategorizuoti(stud, vargsai, galvos);
	std::cout << "Skirstymas " << file_path << " užtruko " << t.get_time() << " s\n";

	// Isvedimas
	t.restart_timer();
	isvesti_faila_greitas(vargsai, "vargsai.txt");
	isvesti_faila_greitas(galvos, "galvos.txt");
	std::cout << "Išvedimas " << file_path << " užtruko " << t.get_time() << " s\n";

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
		stud = nuskaityti_faila_greitas("studentai10000.txt");
		break;
	
	default:
	 	goto input_option;
	}

	pasirinkti_rikiavima(stud);

	isvesti_faila(stud, "rezultatas.txt");
}

void pasirinkti_rikiavima(std::vector<Studentas>& stud){
	char input;

 sort_option:
	std::cout << "Rikiuoti pagal: (v)ardus ar (p)avardes?\n";
	std::cin >> input;

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
}