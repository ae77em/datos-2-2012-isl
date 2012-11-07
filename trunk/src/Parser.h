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

#define PALABRAS_FRASE 4

class Parser {
	private:
		std::list<std::string> terminosOraciones;

		LectorArchivo* lector;
		Stemmer* stemmer;
		Trie* contenedorLexico;
		Trie* contenedorOraciones;
		Validador* validador;
	public:
		Parser();
		~Parser();
		
		bool parsearArchivo(std::string nombreArchivo);

		void persistirLexico(std::string nombreIndice);
		void persistirOraciones(std::string nombreIndice);

		Trie* obtenerContenedorLexico();
		Trie* obtenerContenedorOraciones();
};

#endif
