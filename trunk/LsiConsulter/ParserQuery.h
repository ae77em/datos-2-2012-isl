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

	std::vector<int>* parsearConsulta(std::list<std::string>* terminosConsulta);
private:
    void cargarOffsetDiccionario();

	void splitQuery();
	void stemezarPalabras();
	void obtenerOffsetDiccionario();

	std::vector<int>* recuperarIds();
	int buscarIdTermino(std::string);
	int buscarIdTerminoRec(std::string, int, int ,int);

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


#endif
