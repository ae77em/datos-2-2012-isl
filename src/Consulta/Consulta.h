/*
 * Consultador.h
 *
 *  Created on: 30/11/2011
 *      Author: esteban
 */

#ifndef CONSULTA_H_
#define CONSULTA_H_

#include <iostream>

class Consulta {
public:
	Consulta();
	void obtenerConsulta( std::string& );
	virtual ~Consulta();
};

#endif /* CONSULTA_H_ */
