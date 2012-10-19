#include "Parser.h"

Parser::Parser() {
	stemmer = new Stemmer();
	persistidor = new Persister();
}

Parser::~Parser() {
	delete stemmer;
	delete persistidor;
}

bool Parser::parsearArchivo(std::string nombreArchivo) {

	std::ifstream archivo(nombreArchivo.c_str(),std::ifstream::in);
	std::string termino;
	
	if (!archivo.good()) {
		return false;
	}
	
	/* el stemmer se encarga de validar, stemmizar y pasar a minúsculas
	 * la palabra.
	 * todo ver como hacer para meterlo en el trie...
	 */
	stemmer->stemfile((FILE*)&archivo);

	/*termino = lector->leerPalabra(archivo);
	while (termino.size() > 0) {
		// VALIDAR
		// STEM
		// MINUSCULA
		
		termino = lector->leerPalabra(archivo);
	}*/

	
	// BAJAR TRIE A DISCO
	
	return true;
}
