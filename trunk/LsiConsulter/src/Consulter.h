/*
 * Consulter.h
 *
 *  Created on: 16/11/2012
 *      Author: federico
 */

#ifndef CONSULTER_H_
#define CONSULTER_H_

#include <string>
#include <vector>
#include <fstream>
#include "ParserQuery.h"

class Consulter {
public:
	Consulter();
	virtual ~Consulter();

	void analizarConsulta(std::string);

private:

	ParserQuery* parserQuery;
};

#endif /* CONSULTER_H_ */
