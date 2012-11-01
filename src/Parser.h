#ifndef __PARSER_H_
#define __PARSER_H_

#include <fstream>
#include <iostream>

#include "LectorArchivo.h"
#include "Stemmer.h"
#include "Trie.h"

class Parser {
	private:
		LectorArchivo* lector;
		Trie* contenedorLexico;
		Stemmer* stemmer;
	public:
		Parser();
		~Parser();
		
		bool parsearArchivo(std::string nombreArchivo);
		void persistirLexico();
		Trie* obtenerContenedorLexico();
};

#endif
