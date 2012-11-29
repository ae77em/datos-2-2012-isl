#include "CalculadorLSI.h"

#include <cstdlib>
#include <cstdio>
#include <iostream>

#define CANT_COLUMNAS_A_LEVANTAR 5000

CalculadorLSI::CalculadorLSI() {

}

CalculadorLSI::~CalculadorLSI() {

}

void CalculadorLSI::calcularLSI(int cantTopicos, std::string pathMatriz, std::string pathSVD) {
	char strTop[4];
	char strCol[5];

	//le agrego el path a la matriz
	std::string comandoScript= "./CalcularLSI.py ";

	comandoScript += pathMatriz;
	comandoScript += " ";

	sprintf(strTop, "%d", cantTopicos);
	sprintf(strCol, "%d", CANT_COLUMNAS_A_LEVANTAR);

	comandoScript += strTop;
	comandoScript += " ";
	comandoScript += strCol;
	comandoScript += " ";
	comandoScript += pathSVD;

	std::cout << "INICIO CALCULO ISL" << std::endl;
	int res = system(comandoScript.c_str());
	res++;
	std::cout << "FIN CALCULO ISL" << std::endl;
}
