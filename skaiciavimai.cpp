#include <vector>
#include <algorithm>

float vidurkis(std::vector<int> pazymiai) {
	int sum = 0;
	for (int paz : pazymiai)
		sum += paz;

	return ((float)sum) / (pazymiai.size());
}

float mediana(std::vector<int> pazymiai) {
	int ilgis = pazymiai.size();
	if (ilgis == 0)
		return 0.0;

	std::sort(pazymiai.begin(), pazymiai.end());

	// Klasikine medianos formule
	// Jei vektoriaus ilgis nelyginis, paimamas floor(n/2) (arba paparastai: vidurinis)
	// Jei lyginis, paimamas viduriniu vidurkis
	if (ilgis % 2 == 1)
		return pazymiai.at(ilgis / 2);
	else
		return (pazymiai.at(ilgis / 2) + pazymiai.at(ilgis / 2 - 1)) / 2.0;
}

float galutinis(float paz_agg, int egz_paz) {
	return 0.4 * paz_agg + 0.6 * egz_paz;
}
