#ifndef __PARSER_H_
#define __PARSER_H_

#include <fstream>
#include <iostream>

#include "LectorArchivo.h"
#include "Stemmer.h"
#include "Trie.h"
#include "Validador.h"

#define PALABRAS_FRASE 4

class Parser {
	private:
		LectorArchivo* lector;
		Stemmer* stemmer;
		Trie* contenedorLexico;
		Validador* validador;
	public:
		Parser();
		~Parser();
		
		bool parsearArchivo(std::string nombreArchivo);
		void persistirLexico();
		Trie* obtenerContenedorLexico();
};

#endif
