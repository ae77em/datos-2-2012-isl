#ifndef CONSULTER_H_
#define CONSULTER_H_

#include <string>
#include <vector>
#include <fstream>
#include "ParserQuery.h"

class Consulter {
public:
	Consulter(unsigned int unK,std::string,std::string,std::string);
	virtual ~Consulter();

	void analizarConsulta(std::string);
	std::vector<double*>* proyectarQuery();

private:
    void cargarS();
    std::vector<double*>* multiplicarContraU();
    std::vector<double*>* multiplicarContraS(std::vector<double*>*);

    //atributos
    std::ifstream matrizU;
    std::ifstream matrizS;
    std::ifstream matrizV;

	ParserQuery* parserQuery;
	unsigned int K;

	std::vector<unsigned int*>* query;
	std::vector<double*>* queryProyectada;
	std::vector<double*>* vectorS;
};

#endif /* CONSULTER_H_ */
