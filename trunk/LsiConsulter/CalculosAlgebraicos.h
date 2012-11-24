#ifndef CALCULOSALGEBRAICOS_H
#define CALCULOSALGEBRAICOS_H

#include <cmath>
#include <fstream>
#include <iostream>
#include <vector>

class CalculosAlgebraicos {
    public:
        CalculosAlgebraicos();
        virtual ~CalculosAlgebraicos();

        double productoInterno(std::vector<double>* v1, std::vector<double>* v2);
        double norma(std::vector<double>* v1);
        void normalizarVector(std::vector<double>* v1);
};

#endif
