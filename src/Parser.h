#ifndef __PARSER_H_
#define __PARSER_H_

#include <fstream>
#include <iostream>
#include <list>
#include <string>

#include "LectorArchivo.h"
#include "Stemmer.h"
#include "Trie.h"
#include "Validador.h"

class Parser {
	private:
		std::list<std::string> terminosOraciones;

		LectorArchivo* lector;
		Stemmer* stemmer;
		Trie* contenedorLexico;
		Validador* validador;
	public:
		Parser();
		~Parser();
		
		bool parsearArchivo(std::string nombreArchivo);
		void persistirLexico(std::string,std::string);
		Trie* obtenerContenedorLexico();
		std::string parsearPalabra(std::string);
};

#endif
