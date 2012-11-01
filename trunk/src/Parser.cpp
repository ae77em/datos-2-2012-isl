#include "Parser.h"
#include "Stemmer.h"

Parser::Parser() {
	lector = new LectorArchivo();
	contenedorLexico = new Trie();
	stemmer = new Stemmer();
}

Parser::~Parser() {
	delete lector;
	contenedorLexico->destruirArbol_INI();
	delete contenedorLexico;
	delete stemmer;
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

			std::string terminoStemado = stemmer->stemPalabra(termino);
			int* despuesLoSaco = NULL;

			// Por si justo la palabra que entra es un stemm y luego de procesar queda vacia
			if (terminoStemado.size() > 0) {
				contenedorLexico->insertarPalabraEnRaiz(terminoStemado,despuesLoSaco);
			}
		}
	}

	archivo.close();
	return true;
}

Trie* Parser::obtenerContenedorLexico() {
	return contenedorLexico;
}

void Parser::persistirLexico() {
    std::ofstream lexico;
    std::ofstream offsetLexico;

    lexico.open("diccionario.txt");
    offsetLexico.open("offsetLexico.txt");

    contenedorLexico->persistirPalabras_INI(&lexico, &offsetLexico);

    lexico.close();
    offsetLexico.close();

}
