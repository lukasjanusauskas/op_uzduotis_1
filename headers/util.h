#ifndef UTIL_H
#define UTIL_H

#include "studentas.h"

Studentas generuoti_rand_stud();
void generuoti_atsitiktinius(std::string file, unsigned int n);
std::vector<Studentas> nuskaityti_faila(std::string failas);

bool palyginti_rikiavimui(Studentas pirmas, Studentas antras);

template <typename container>
void rikiuoti_studentus(container &stud);

template <typename container>
void kategorizuoti(container &stud, container &vargsai, container &galvos);

#endif
