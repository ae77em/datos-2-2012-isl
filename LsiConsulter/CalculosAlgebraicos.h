#ifndef CALCULOSALGEBRAICOS_H
#define CALCULOSALGEBRAICOS_H

#include <vector>
#include <fstream>
#include <math.h>
#include <iostream>

class CalculosAlgebraicos
{
    public:
        CalculosAlgebraicos();
        virtual ~CalculosAlgebraicos();

        double metodoCoseno(std::vector<double>*,std::vector<double>*);
        double productoInterno(std::vector<double>*,std::vector<double>*);
        double norma(std::vector<double>*);
        void normalizarVector(std::vector<double>*);

    protected:
    private:
};

#endif // CALCULOSALGEBRAICOS_H
