#ifndef UTIL_H
#define UTIL_H

#include "studentas.h"

Studentas generuoti_rand_stud();
void generuoti_atsitiktinius(std::string file, unsigned int n);
std::vector<Studentas> nuskaityti_faila(std::string failas);

void pasirinkti_rikiavima(std::vector<Studentas>& stud, std::string file_path);
bool palyginti_rikiavimui(Studentas pirmas, Studentas antras);
void rikiuoti_studentus(std::vector<Studentas>& stud);

void kategorizuoti(std::vector<Studentas> stud);

#endif
