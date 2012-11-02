#ifndef CONSULTER_H
#define CONSULTER_H

#include <vector>
#include <fstream>
#include <math.h>

class Consulter
{
    public:
        Consulter();
        virtual ~Consulter();

        double metodoCoseno(std::vector<double>*,std::vector<double>*);
        int buscarIdTermino(std::string,std::vector<int>*,std::fstream*);
        std::vector<int>* obtenerOffsetLexico(std::string);


    protected:
    private:

        double productoInterno(std::vector<double>*,std::vector<double>*);
        double norma(std::vector<double>*);

        int buscarIdTerminoRec(std::string,std::vector<int>*,int,int,int,std::fstream*);


};

#endif // CONSULTER_H
