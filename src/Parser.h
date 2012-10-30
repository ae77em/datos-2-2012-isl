#ifndef __PARSER_H_
#define __PARSER_H_

#include <fstream>
#include <iostream>

#include "LectorArchivo.h"
#include "Trie.h"
#include "Stemmer.h"

class Parser {
	private:
		LectorArchivo* lector;

		//agregados por FEDE
		Trie* contenedorLexico;
		Stemmer* stemedor;
		//
	public:
		Parser();
		~Parser();
		bool parsearArchivo(std::string nombreArchivo);

		//agregados por FEDE
		Trie* obtenerContenedorLexico();
};

#endif
