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
	std::string termino, terminoSiguiente;
	std::ifstream archivo(nombreArchivo.c_str());

	if (!archivo.good()) {
		return false;
	}
	
	termino = lector->obtenerToken(archivo);
	while (!archivo.eof()) {
		terminoSiguiente = lector->obtenerToken(archivo);

		if (termino.length() > 0 && validador->validarTermino(termino)) {
			if (validador->esPalabraCompuesta(termino, terminoSiguiente)) {
				if (terminoSiguiente.length() > 0) {
					termino += " " + terminoSiguiente;
				}
			}else {
				std::string terminoStemado = stemmer->stemPalabra(termino);

				// Por si justo la palabra que entra es un stemm y luego de procesar queda vacia
				if (terminoStemado.size() > 0) {
					contenedorLexico->insertarPalabra(terminoStemado);
				}

				terminosOraciones.push_back(termino);
				if (terminosOraciones.size() == PALABRAS_FRASE) {
					std::string bufferOracion;
					std::list<std::string>::iterator it;
					for (it = terminosOraciones.begin(); it != terminosOraciones.end(); ++it) {
						bufferOracion += (*it) + " ";
					}

					//contenedorOraciones->insertarPalabra(bufferOracion); // TODO eliminar segundo parametro

					// TODO Mantener 3 terminos anteriores
					terminosOraciones.pop_front();
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

void Parser::persistirLexico(std::string path) {

    std::ofstream lexico;
    std::ofstream offsetLexico;

    std::string pathOffsetLexico = path;
    pathOffsetLexico += "_offset";

    lexico.open(path.c_str());
    offsetLexico.open(pathOffsetLexico.c_str());

    contenedorLexico->persistirPalabras_INI(&lexico, &offsetLexico);

    lexico.close();
    offsetLexico.close();
}

void Parser::persistirOraciones(std::string path) {

    std::ofstream oraciones;
    std::ofstream offsetOraciones;

    std::string pathOffsetOracion = path;
    pathOffsetOracion += "_offset";

    oraciones.open(path.c_str());
    offsetOraciones.open(pathOffsetOracion.c_str());

    contenedorOraciones->persistirPalabras_INI(&oraciones, &offsetOraciones);

    oraciones.close();
    offsetOraciones.close();
}
