#include "studentas.h"
#include "skaiciavimai.h"
#include "util.h"

#include "stud_random.cpp"
#include "stud_rikiavimas.cpp"
#include "studentas_io.cpp"
#include "timer.cpp"

#include <chrono>

template <typename container>
void testas(std::string file_path, container &stud);

template<typename container>
void pasirinkti_rikiavima(container &stud, std::string file_path);

template <typename container>
void konsoles_dialogas(container& stud);

void testuoti_eiga();
void testuoti_generavima();

int main() {
	// generuoti_penkis();
	std::vector<Studentas> stud;
	konsoles_dialogas(stud);

	return 0;
}

void testuoti_generavima(){
	for(int i = 0; i < 5; i++){
		generuoti_penkis();
	}
}

void testuoti_eiga(){
	std::list<Studentas> stud;

	testas("studentai1000.txt", stud);
	testas("studentai10000.txt", stud);
	testas("studentai100000.txt", stud);
	testas("studentai1000000.txt", stud);
	testas("studentai10000000.txt", stud);
}

template <typename container>
void testas(std::string file_path, container& stud){
	container vargsai, galvos;

	Timer t;
	// Ivedimas
	t.start_timer();
	nuskaityti_faila(stud, file_path);
	std::cout << "Nuskaitymas failo " << file_path << " užtruko " << t.get_time() << " s\n";

	// Rikiavimas
	pasirinkti_rikiavima(stud, file_path);

	// Kategorizavimas
	t.restart_timer();
	kategorizuoti(stud, vargsai, galvos);
	std::cout << "Skirstymas " << file_path << " užtruko " << t.get_time() << " s\n";

	// Isvedimas
	t.restart_timer();
	isvesti_faila(vargsai, "vargsai.txt");
	isvesti_faila(galvos, "galvos.txt");
	std::cout << "Išvedimas " << file_path << " užtruko " << t.get_time() << " s\n";

	std::cout << std::endl;
}

template <typename container>
void konsoles_dialogas(container& stud){
	char input;

input_option:

	std::cout << "Kaip įvesti studentus? Terminale - (t), Faile - (f)\n";
	std::cin >> input;

	switch (input)
	{
	case 't':
		irasyti_studentus(stud);
		break;

	case 'f':
		std::cout << "Konteinerio adresas " << &(*stud.begin()) << std::endl;
	 	testas("studentai100000.txt", stud);
		std::cout << "Konteinerio adresas " << &(*stud.begin()) << std::endl;
		break;
	
	default:
	 	goto input_option;
	}
}

template <typename container>
void pasirinkti_rikiavima(container &stud, std::string file_path){
	char input;

 sort_option:
	std::cout << "Rikiuoti pagal: (v)ardus, (p)avardes ar (g)alutinį pažymį?\n";
	std::cin >> input;

	Timer t;

	switch (input)
	{
	case 'v':
		t.start_timer();
		rikiuoti_studentus(stud, [](Studentas const& s1, Studentas const& s2){
										return s1.vardas.compare(s2.vardas) > 0;});
		std::cout << "Rikiavimas užtruko: " << t.get_time();
		break;

	case 'p':
		t.start_timer();
		rikiuoti_studentus(stud, [](Studentas const& s1, Studentas const& s2){
										return s1.vardas.compare(s2.vardas) > 0;});
		std::cout << "Rikiavimas užtruko: " << t.get_time();
		break;
	
	case 'g':
		t.start_timer();
		rikiuoti_studentus(stud, [](Studentas const& s1, Studentas const& s2){
										return s1.galutinis > s2.galutinis; });
		std::cout << "Rikiavimas užtruko: " << t.get_time();
		break;

	default:
	 	goto sort_option;
	}
}