#include "Parser.h"
#include "Stemmer.h"

#include <algorithm>

Parser::Parser() {
	contenedorLexico = new Trie();
	lector = new LectorArchivo();
	stemmer = new Stemmer();
	validador = new Validador();
}

Parser::~Parser() {
	contenedorLexico->destruirArbol_INI();
	delete contenedorLexico;
	delete lector;
	delete stemmer;
	delete validador;
}

bool Parser::parsearArchivo(std::string nombreArchivo) {
	std::string termino, terminoSiguiente;
	std::ifstream archivo(nombreArchivo.c_str());

	if (!archivo.good()) {
		return false;
	}

	std::string terminoValidado;
	std::string terminoStemado;

	termino = lector->obtenerToken(archivo);
	while (!archivo.eof()) {
		if (termino.length() > 0 && validador->validarTermino(termino)) {
			std::string terminoStemado = stemmer->stemPalabra(termino);

			// Por si justo la palabra que entra es un stemm y luego de procesar queda vacia
			if (terminoStemado.size() > 0) {
				contenedorLexico->insertarPalabra(terminoStemado);
			}
		}

		termino = lector->obtenerToken(archivo);
	}

	archivo.close();
	return true;
}

Trie* Parser::obtenerContenedorLexico() {
	return contenedorLexico;
}

void Parser::persistirLexico(std::string pathDiccionario, std::string pathOffsetDiccionario) {
    std::ofstream lexico;
    std::ofstream offsetLexico;

    lexico.open(pathDiccionario.c_str());
    offsetLexico.open(pathOffsetDiccionario.c_str());

    contenedorLexico->persistirPalabras_INI(&lexico, &offsetLexico);

    lexico.close();
    offsetLexico.close();
}
