#include "Parser.h"

Parser::Parser() {
	lector = new LectorArchivo();
}

Parser::~Parser() {
	delete lector;
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
			// INSERTAR EN EL TRIE
		}
	}

	archivo.close();
	return true;
}
