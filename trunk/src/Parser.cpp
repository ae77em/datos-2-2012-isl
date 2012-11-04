#include "Parser.h"
#include "Stemmer.h"

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
	std::string termino, terminoSiguiente, bufferOracion;
	std::ifstream archivo(nombreArchivo.c_str());

	int contadorBuffer = 0;

	if (!archivo.good()) {
		return false;
	}
	int cantTerm=0;
	int cantTermIngresados=0;
	termino = lector->obtenerToken(archivo);
	while (!archivo.eof()) {
		terminoSiguiente = lector->obtenerToken(archivo);

		if (termino.length() > 0) {
			cantTerm++;

			if (validador->esPalabraCompuesta(termino, terminoSiguiente)) {
				if (terminoSiguiente.length() > 0) {
					termino += " " + terminoSiguiente;
				}
			}else {
				std::string terminoStemado = stemmer->stemPalabra(termino);

				// Por si justo la palabra que entra es un stemm y luego de procesar queda vacia
				if (terminoStemado.size() > 0) {
					contenedorLexico->insertarPalabraEnRaiz(terminoStemado, NULL); // TODO eliminar segundo parametro
					cantTermIngresados++;
				}

				bufferOracion += termino + " ";
				contadorBuffer++;

				if (contadorBuffer == PALABRAS_FRASE) {
					bufferOracion = "";
					contadorBuffer--;
				}

				termino = terminoSiguiente;
			}
		}else {
			termino = terminoSiguiente;
		}
	}

	std::cout<<"Palabras en archivo "<<cantTerm<<"  Palabraque ingresaron  "<<cantTermIngresados<<std::endl;

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
