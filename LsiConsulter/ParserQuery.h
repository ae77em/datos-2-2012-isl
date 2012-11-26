/*
 * ParserQuery.h
 *
 *  Created on: 16/11/2012
 *      Author: federico
 */

#ifndef PARSERQUERY_H_
#define PARSERQUERY_H_

#include <string>
#include <list>
#include <vector>
#include <fstream>
#include "Stemmer.h"

class ParserQuery {
public:

	ParserQuery(std::string,std::string);
	virtual ~ParserQuery();

	std::vector<unsigned int>* parsearConsulta(std::list<std::string>* terminosConsulta);

private:
    void cargarOffsetDiccionario();

	void splitQuery();
	void stemezarPalabras();
	void obtenerOffsetDiccionario();

	std::vector<unsigned int>* recuperarIds();
	unsigned int buscarIdTermino(std::string);
	unsigned int buscarIdTerminoRec(std::string,int ,int ,int);

	Stemmer* stemmer;

	std::ifstream diccionario;
	std::ifstream offsetDiccionario;

	std::string pathDiccionario;
	std::string pathOffsetDiccionario;
	std::string consulta;

	std::list<std::string>* palabras;
	std::list<std::string>* palabrasStemezadas;

	std::vector<unsigned int>* contenedorOffsetDiccionario;


};


#endif /* PARSERQUERY_H_ */
