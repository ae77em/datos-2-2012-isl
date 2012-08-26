/*
 * Indexador.h
 *
 *  Created on: 27/11/2011
 *      Author: esteban
 */
#include "../RecorredorDeDirectorios/RecorredorDeDirectorios.h"
#include "../AnalizadorGramatico/AnalizadorGramatico.h"
#include "../Trie/Trie.h"
#include "../Utilidades/Utilidades.h"

#include <list>

using namespace std;

#ifndef INDEXADOR_H_
#define INDEXADOR_H_

class Indexador {
private:
	Trie* contenedorDePalabras;
	std::string directorio;
	list<string>* listaDeDirectorios;
	AnalizadorGramatico* parser;
	Utilidades util;

public:
	Indexador();
	void indexarDirectorio(std::string path);
	virtual ~Indexador();
};

#endif /* INDEXADOR_H_ */
