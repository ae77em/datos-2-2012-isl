#ifndef CONSULTER_H_
#define CONSULTER_H_

#include <string>
#include <vector>
#include <fstream>
#include "ParserQuery.h"
#include "CalculosAlgebraicos.h"

class Consulter {
public:
	Consulter(std::string repositorio);
	virtual ~Consulter();

	void rankearConsulta(std::string);
	std::vector<double>* proyectarQuery();
	 void mostrarMatrices(); //solo para imprimir las matrices


private:

    void cargarS();
    void cargarV();
    void cargarNombreArchivos(std::string);

    void evaluar();


    std::vector<double>* multiplicarContraU();
    std::vector<double>* multiplicarContraS(std::vector<double>*);
    void generarContenedorMatrizV();
    void cargarMatrizV();

    //atributos
	unsigned int cantAutovalores;
    ParserQuery* parserQuery;
    CalculosAlgebraicos* calculer;

    std::ifstream matrizU;
    std::ifstream matrizS;
    std::ifstream matrizV;

	std::vector<unsigned int>* query;
	std::vector<double>* queryProyectada;
	std::vector<double>* vectorS;
	std::vector<std::vector<double>*>* contenedorMatrizV;

	std::vector<std::string>* contenedorNombreArchivos;

    double* registroV;

    void mostrarU();
    void mostrarV();
    void mostrarS();



	//HEAP heap;
};

#endif /* CONSULTER_H_ */
