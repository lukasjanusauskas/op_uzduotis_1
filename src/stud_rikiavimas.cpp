#include <algorithm>
#include "studentas.h"

bool palyginti_rikiavimui(Studentas pirmas, Studentas antras) {
	// Eilutems lyginti naudojame compare metoda
	int cmp = pirmas.vardas.compare(antras.vardas);

	// Jei lygios eilutes, lyginam pavardes
	if (cmp == 0)
		return pirmas.pavarde.compare(antras.pavarde) < 0;

	// Jei nelygios, grazinam rezultata
	else
		return cmp < 0;
}

void rikiuoti_studentus(std::vector<Studentas>& stud) {
	// Rikiavimas su custom metodu
	std::sort(stud.begin(), stud.end(), &palyginti_rikiavimui);
}
