#include "studentas.h"
#include "util.h"
#include "skaiciavimai.cpp"

#include <vector>
#include <fstream>

void kategorizuoti(std::vector<Studentas> stud){
    std::vector<Studentas> vargsai;
    std::vector<Studentas> galvos;

    for(auto& s: stud){
        float med = mediana(s.nd_pazymiai);

        if(galutinis(med, s.egz_pazymys) >= 5.0)
            vargsai.push_back(s);
        else
            galvos.push_back(s);
    }

    stud.clear();
}