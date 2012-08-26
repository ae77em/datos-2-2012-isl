/*
 * AnalizadorGramatico.h
 *
 *  Created on: 03/09/2011
 *      Author: esteban
 */

#include "../Utilidades/Utilidades.h"
#include "../ArchivoTexto/ArchivoTexto.h"
#include "../Trie/Trie.h"
#include <fstream>
#include <iostream>

#ifndef PARSER_H_
#define PARSER_H_

#ifndef MAX_LENGTH
#define MAX_LENGTH 256
#endif


class AnalizadorGramatico {
private:
	Trie trie;

public:
	AnalizadorGramatico();
	AnalizadorGramatico(Trie& unTrie);
	bool parsearArchivo(std::string& archivoAparsear );
	void parsearConsulta( std::string & consulta);
	virtual ~AnalizadorGramatico();
};

#endif /* PARSER_H_ */
