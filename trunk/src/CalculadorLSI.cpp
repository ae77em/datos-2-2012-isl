/*
 * CalculadorLSI.cpp
 *
 *  Created on: 01/11/2012
 *      Author: esteban
 */

#define CANT_COLUMNAS_A_LEVANTAR 10

#include <cstdlib>
#include <cstdio>
#include <iostream>

#include "CalculadorLSI.h"

CalculadorLSI::CalculadorLSI() {
	// TODO Auto-generated constructor stub

}

void CalculadorLSI::calcularLSI(int cantTopicos, std::string pathMatriz){

	char strTop[5];
	char strCol[10];
	//std::string comandoScript= "./CalcularLSI.py matrizPonderada.mm ";

	//le agrego el path a la matriz
	std::string comandoScript= "./CalcularLSI.py ";

	std::string pathMatrizAux = "indices";
	pathMatriz  =pathMatrizAux + pathMatriz;

	comandoScript += pathMatriz;
	comandoScript += " ";

	sprintf(strTop, "%d", cantTopicos);
	sprintf(strCol, "%d", CANT_COLUMNAS_A_LEVANTAR);

	comandoScript += strTop;
	comandoScript += " ";
	comandoScript += strCol;

	std::cout << "INICIO CALCULO ISL" << std::endl;
	system(comandoScript.c_str());
	std::cout << "FIN CALCULO ISL" << std::endl;
}

CalculadorLSI::~CalculadorLSI() {
	// TODO Auto-generated destructor stub
}

