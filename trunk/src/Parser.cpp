#include "Parser.h"
#include "Stemmer.h"

Parser::Parser() {
	contenedorLexico = new Trie();
	contenedorOraciones = new Trie();
	lector = new LectorArchivo();
	stemmer = new Stemmer();
	validador = new Validador();
}

Parser::~Parser() {
	contenedorLexico->destruirArbol_INI();
	delete contenedorLexico;

	contenedorOraciones->destruirArbol_INI();
	delete contenedorOraciones;

	delete lector;
	delete stemmer;
	delete validador;
}

bool Parser::parsearArchivo(std::string nombreArchivo) {
	std::string termino, terminoSiguiente, bufferOracion;
	std::ifstream archivo(nombreArchivo.c_str());

	int contadorBuffer = 0;

	if (!archivo.good()) {
		return false;
	}
	
	termino = lector->obtenerToken(archivo);
	while (!archivo.eof()) {
		terminoSiguiente = lector->obtenerToken(archivo);

		if (termino.length() > 0) {
			if (validador->esPalabraCompuesta(termino, terminoSiguiente)) {
				if (terminoSiguiente.length() > 0) {
					termino += terminoSiguiente + " ";
				}
			}else {
				std::string terminoStemado = stemmer->stemPalabra(termino);

				// Por si justo la palabra que entra es un stemm y luego de procesar queda vacia
				if (terminoStemado.size() > 0) {
					contenedorLexico->insertarPalabraEnRaiz(terminoStemado, NULL); // TODO eliminar segundo parametro
				}

				bufferOracion += termino + " ";
				contadorBuffer++;

				if (contadorBuffer == PALABRAS_FRASE) {
					std::string oracionStemada = stemmer->stemPalabra(bufferOracion);
					contenedorLexico->insertarPalabraEnRaiz(oracionStemada, NULL); // TODO eliminar segundo parametro

					// TODO Mantener 3 terminos anteriores
					bufferOracion.clear();
					contadorBuffer = 0;
				}

				termino = terminoSiguiente;
			}
		}else {
			termino = terminoSiguiente;
		}
	}

	archivo.close();
	return true;
}

Trie* Parser::obtenerContenedorLexico() {
	return contenedorLexico;
}

Trie* Parser::obtenerContenedorOraciones() {
	return contenedorOraciones;
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

void Parser::persistirOraciones() {
    std::ofstream oraciones;
    std::ofstream offsetOraciones;

    oraciones.open("diccionario.txt");
    offsetOraciones.open("offsetLexico.txt");

    contenedorLexico->persistirPalabras_INI(&oraciones, &offsetOraciones);

    oraciones.close();
    offsetOraciones.close();
}
