#include "Parser.h"

Parser::Parser() {
	lector = new Reader();
	stemmer = new Stemmer();
	persistidor = new Persister();
}

~Parser::Parser() {
	delete lector;
	delete stemmer;
	delete persistidor;
}

std::bool Parser::parsearArchivo(std::string nombreArchivo) {
	std::ifstream* archivo;
	std::string termino;
	
	archivo = new std::ifstream(nombreArchivo);
	if (!archivo->good()) {
		return false;
	}
	
	termino = lector->leerPalabra(archivo);
	while (termino.size() > 0) {
		// VALIDAR
		// STEM
		// MINUSCULA
		
		termino = lector->leerPalabra(archivo);
	}
	
	// BAJAR TRIE A DISCO
	
	return true;
}
