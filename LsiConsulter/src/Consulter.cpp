/*
 * Consulter.cpp
 *
 *  Created on: 16/11/2012
 *      Author: federico
 */

#include "Consulter.h"

Consulter::Consulter() {
	// TODO Auto-generated constructor stub

}

Consulter::~Consulter() {
	// TODO Auto-generated destructor stub
}

void Consulter::analizarConsulta(std::string consulta){

	//toma un conjuento de palabras representado por el string y devuelve un vector son sus respectivos ID's
	std::vector<unsigned int*>* idQuery = parserQuery->parsearConsulta(consulta);

	for(unsigned int i=0; i<idQuery->size(); i++){

		std::cout<<*idQuery->at(i)<<std::endl;
	}

}
