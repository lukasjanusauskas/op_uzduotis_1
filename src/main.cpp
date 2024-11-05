#include "studentas.h"
#include "skaiciavimai.h"
#include "util.h"

#include "stud_random.cpp"
#include "studentas_io.cpp"
#include "stud_rikiavimas.cpp"
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

template <typename container>
void testas(std::string file_path, container& stud){
	container vargsai, galvos;

	Timer t;
	// Ivedimas
	nuskaityti_faila(stud, file_path);

	// Rikiavimas
	pasirinkti_rikiavima(stud, file_path);

	// Kategorizavimas
	t.restart_timer();
	kategorizuoti3(stud, vargsai, galvos);
	std::cout << "Skirstymas " << file_path << " užtruko " << t.get_time() << " s\n";

	// Isvedimas
	isvesti_faila(vargsai, "vargsai.txt");
	isvesti_faila(galvos, "galvos.txt");
}

template <typename container>
void konsoles_dialogas(container& stud){
	char input;

input_option:
	std::string path = "studentai1000000.txt";

	std::cout << "Kaip įvesti studentus? Terminale - (t), Faile - (f)\n";
	std::cin >> input;

	switch (input)
	{
	case 't':
		irasyti_studentus(stud);
		break;

	case 'f':
		for(int i = 0; i < 5; i++)
	 		testas(path, stud);
		break;
	
	default:
	 	goto input_option;
	}
}

bool pagal_galutini(Studentas pirmas, Studentas antras) {
	return pirmas.galutinis > antras.galutinis;
}

template <typename container>
void pasirinkti_rikiavima(container& stud, std::string file_path){
	char input;
	std::chrono::time_point<std::chrono::system_clock> start, end;
	std::chrono::duration<double> elapsed;

 sort_option:
	std::cout << "Rikiuoti pagal: (v)ardus, (p)avardes ar (g)alutinį pažymį?\n";
	std::cin >> input;

	switch (input)
	{
	case 'v':
		start = std::chrono::system_clock::now();

		std::sort(stud.begin(), stud.end(), [](Studentas &s1, Studentas &s2){
			return s1.vardas.compare(s2.vardas) > 0;
		});

		end = std::chrono::system_clock::now();
		elapsed = end - start;
		break;

	case 'p':
		start = std::chrono::system_clock::now();

		std::sort(stud.begin(), stud.end(), [](Studentas &s1, Studentas &s2){
			return s1.pavarde.compare(s2.pavarde) > 0;
		});

		end = std::chrono::system_clock::now();
		elapsed = end - start;
		break;

	case 'g':
		start = std::chrono::system_clock::now();

		std::sort(stud.begin(), stud.end(), [](Studentas &s1, Studentas &s2){
			return s1.galutinis > s2.galutinis;
		});

		end = std::chrono::system_clock::now();
		elapsed = end - start;
		break;
	
	default:
	 	goto sort_option;
	}

	std::cout << "Rikiavimas studentų iš failo " << file_path << " užtruko " << elapsed.count() << "s\n";
}