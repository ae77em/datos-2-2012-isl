#include "Parser.h"

Parser::Parser() {
	lector = new LectorArchivo();
	contenedorLexico = new Trie();

}

Parser::~Parser() {
	delete lector;

	contenedorLexico->destruirArbol_INI();
	delete contenedorLexico;
}

bool Parser::parsearArchivo(std::string nombreArchivo) {
	std::string termino;
	std::ifstream archivo(nombreArchivo.c_str());
	
	if (!archivo.good()) {
		return false;
	}

	while (!archivo.eof()) {
		termino = lector->obtenerToken(archivo);

		if (termino.length() > 0) {
			// VALIDAR
			// HACER EL STEM
			int* despuesLoSaco=NULL;
			contenedorLexico->insertarPalabraEnRaiz(termino,despuesLoSaco);
		}
	}

	archivo.close();
	return true;
}

Trie* Parser::obtenerContenedorLexico(){

	return contenedorLexico;

}
