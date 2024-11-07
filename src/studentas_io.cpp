#include <iostream>
#include <fstream>
#include <regex>
#include <iomanip>
#include <list>

#include "studentas.h"
#include "skaiciavimai.cpp"
#include "timer.h"

Studentas irasyti_studenta() {
	// Vieno studento irasymas
	Studentas stud;

	std::cout << "Įrašyti varda ir pavarde(ivedus vardą paspausti Enter):\n";
	std::cin >> stud.vardas >> stud.pavarde;

	std::string ivestis;
	int paz;

	std::cout << "Įvesti pažymius(norėdami užbaigti, įveskite 0):\n";
	while (true) {
		std::cin >> ivestis;
		try
		{
			paz = std::stoi(ivestis);
		}
		catch (const std::exception&)
		{
			std::cout << "Prasau, iveskite normalu skaiciu, jei norite baigti, iveskite 0\n";
			continue;
		}

		if (paz == 0) // Irasoma, kol nepaspaudzia 0
			break;

		stud.nd_pazymiai.push_back(paz);
	}

	std::cout << "Įveskite egzamino pažymį:\n";

ivesti:;
	std::cin >> ivestis;

	try
	{
		stud.egz_pazymys = std::stoi(ivestis);
	}
	catch (const std::exception&)
	{
		std::cout << "Prasau, iveskite normalu skaiciu, jei norite baigti, iveskite 0\n";
		goto ivesti;
	}

	return stud;
}

template <typename container>
void irasyti_studentus(container &sarasas) {
	// Visu studentu irasimas komandineje eiluteje
	char testi{ 't' };

	while (true) {
		std::cout << "Įrašyti studentą? ";
		std::cin >> testi;

		switch (testi)
		{
		// Jei nuspaudzia 't', ivyksta irsaymas
		case 't':
			sarasas.push_back(irasyti_studenta());
			break;
		// Jei nuspaudzia 'n', grazinama, nevyksta irasymas
		case 'n':
			return;
		// Jei nuspaudzia kazka kito, kartojamas klausimas
		default:
			break;
		}
	}
}

template <typename container>
void nuskaityti_faila(container &stud, std::string failas) {
	// Studentu suvedimas is failo
	std::ifstream fr(failas);

	if(fr.fail()){
		std::cout << "Nėra failo\n";
		return;
	}

	// Nuskaityti failo antraste(stulpelius)
	// Parasyta su prielaida, kad pirmi du stulpeliai: Vardas, Pavarde, o paskutinis: Egz.
	std::string header_str;
	std::getline(fr, header_str, '\n');
	
	int nd_skaicius = 0;

	// Nuskaitomas namu darbu kiekis su regex
	// Daroma prielaida, kad namu darbu stulpeliai zymimi ND(skaicius)

	// Sudarome regex expression ir jį paleidžiame per header_str.
	const std::regex reg_expr("ND\\d+");

	auto iterator = std::sregex_iterator(header_str.begin(), header_str.end(), reg_expr);
	auto empty = std::sregex_iterator();

	// Apskaičiuojame, kiek žodžių atitinka regex expression
	nd_skaicius = std::distance(iterator, empty);

	// Skaitomos eilutes, kol neprieis failo galo
	std::stringstream buffer;
	buffer << fr.rdbuf();
	fr.close();

	int tmp_paz;
	std::string line_buf;
	while (!buffer.eof()) {
		Studentas s;
		buffer >> s.vardas >> s.pavarde;

		for (int i = 0; i < nd_skaicius; i++) {
			buffer >> tmp_paz;
			s.nd_pazymiai.push_back(tmp_paz);
		}
		buffer >> s.egz_pazymys;

		s.galutinis = galutinis(vidurkis(s.nd_pazymiai), s.egz_pazymys);
		stud.push_back(s);
	}
}

template <typename container>
void isvesti_faila(const container &stud, std::string file_path) {
	Timer t;
	std::stringstream buffer;
	// Spausdinti visu studentu duomenis
	buffer << std::left << std::setw(20) << "Vardas" 
						   << std::setw(25) << "Pavardė" 
						   << "Galutinis (vid.)\n";
	buffer << "---------------------------------------------------------------\n";
	// Nustatomas tikslumas ir tik tada spausdinama
	buffer << std::fixed << std::setprecision(2);

	t.start_timer();
	for (auto& s : stud){
		
		float vid = vidurkis(s.nd_pazymiai);
		float med = mediana(s.nd_pazymiai);

	// Spausdinama, nustatant plocio minimuma(kuris retai virsijamas, tai beveik visada toks ir yra)
		buffer << std::setw(20) << s.vardas
			   << std::setw(25) << s.pavarde;
		buffer << std::left
			   << std::setw(17) << s.galutinis << "\n";
	}

	std::ofstream fr(file_path);
	fr << buffer.rdbuf();
	fr.close();
}