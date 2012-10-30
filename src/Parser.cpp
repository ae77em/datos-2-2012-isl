#include "Parser.h"

Parser::Parser() {
	lector = new LectorArchivo();
	contenedorLexico = new Trie();
	stemedor = new Stemmer();

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
	std::cout<<"COMENCE PARSEAR ARCHIVO"<<std::endl;

	while (!archivo.eof()) {
		termino = lector->obtenerToken(archivo);

		if (termino.length() > 0) {
			// VALIDAR
			//string terminoStemado = stemedor->stemPalabra(termino);
			int* despuesLoSaco=NULL;
			contenedorLexico->insertarPalabraEnRaiz(termino,despuesLoSaco);
		}
	}
	std::cout<<"TERMINE PARSEAR ARCHIVO"<<std::endl;

	archivo.close();
	return true;
}

Trie* Parser::obtenerContenedorLexico(){

	return contenedorLexico;

}
