#ifndef CONSULTER_H_
#define CONSULTER_H_

#include <string>
#include <vector>
#include <fstream>
#include "ParserQuery.h"
#include "CalculosAlgebraicos.h"

class Consulter {
public:
	Consulter(unsigned int unK,std::string,std::string,std::string);
	virtual ~Consulter();

	void rankearConsulta(std::string);
	std::vector<double*>* proyectarQuery();

private:
    void cargarS();
    void evaluar();
    std::vector<double*>* multiplicarContraU();
    std::vector<double*>* multiplicarContraS(std::vector<double*>*);

    //atributos
	unsigned int K;
    ParserQuery* parserQuery;
    CalculosAlgebraicos* calculer;

    std::ifstream matrizU;
    std::ifstream matrizS;
    std::ifstream matrizV;

	std::vector<unsigned int*>* query;
	std::vector<double*>* queryProyectada;
	std::vector<double*>* vectorS;

	//HEAP heap;
};

#endif /* CONSULTER_H_ */
