/*
 * Consultador.cpp
 *
 *  Created on: 30/11/2011
 *      Author: esteban
 */
#include "../AnalizadorGramatico/AnalizadorGramatico.h"
#include "Consulta.h"


Consulta::Consulta() {
	// TODO Auto-generated constructor stub

}

void Consulta::obtenerConsulta( std::string& consulta){

	AnalizadorGramatico parser;

	parser.parsearConsulta( consulta );

}

Consulta::~Consulta() {
	// TODO Auto-generated destructor stub
}

