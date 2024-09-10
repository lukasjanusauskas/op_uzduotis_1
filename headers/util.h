#ifndef UTIL_H
#define UTIL_H

#include "studentas.h"

Studentas generuoti_rand_stud();
std::vector<Studentas> generuoti_atsitiktinius(unsigned int n);
std::vector<Studentas> nuskaityti_faila(std::string failas);

bool palyginti_rikiavimui(Studentas pirmas, Studentas antras);
void rikiuoti_studentus(std::vector<Studentas>& stud);

#endif
