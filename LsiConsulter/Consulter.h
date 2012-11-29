#ifndef CONSULTER_H_
#define CONSULTER_H_

#include <cstdlib>
#include <fstream>
#include <string>
#include <vector>

#include "CalculosAlgebraicos.h"
#include "Heap.h"
#include "ParserQuery.h"

class Consulter {
public:
	Consulter(std::string repositorio);
	virtual ~Consulter();

	int rankearConsulta(std::list<std::string>* terminosConsulta);
	std::vector<double>* proyectarQuery();
private:

    void cargarS();
    void cargarV();
    void cargarNombreArchivos(std::string);
    void evaluar();
    void mostrarRankings();
    void generarContenedorMatrizV();
    void cargarMatrizV();

    std::vector<double>* multiplicarContraU();
    std::vector<double>* multiplicarContraS(std::vector<double>*);

    std::string obtenerNombreArchivo(unsigned int);

    //atributos
	unsigned int cantAutovalores;
    ParserQuery* parserQuery;
    CalculosAlgebraicos* calculer;

    std::ifstream matrizU;
    std::ifstream matrizS;
    std::ifstream matrizV;

	std::vector<int>* query;
	std::vector<double>* queryProyectada;
	std::vector<double>* vectorS;
	std::vector<std::vector<double>*>* contenedorMatrizV;

	std::vector<std::string> contenedorNombreArchivos;

    double* registroV;

	Heap* heap;
};

#endif /* CONSULTER_H_ */
