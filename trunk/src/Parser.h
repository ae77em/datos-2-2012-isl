#ifndef __PARSER_H_
#define __PARSER_H_

#include <fstream>
#include <iostream>

#include "LectorArchivo.h"
#include "Trie.h"

class Parser {
	private:
		LectorArchivo* lector;

		//agregados por FEDE
		Trie* contenedorLexico;

		//
	public:
		Parser();
		~Parser();
		bool parsearArchivo(std::string nombreArchivo);

		void persistirLexico();

		//agregados por FEDE
		Trie* obtenerContenedorLexico();
};

#endif
