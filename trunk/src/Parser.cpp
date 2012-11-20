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

	while (!archivo.eof()) {
		archivo >> termino;
		terminoValidado = parsearPalabra(termino);

		if(terminoValidado.size()>0){
			terminoStemado = stemmer->stemPalabra(terminoValidado);
			if(terminoStemado.size()>0){
				contenedorLexico->insertarPalabra(terminoStemado);
			}
		}

	}

	/*termino = lector->obtenerToken(archivo);
=======
	termino = lector->obtenerToken(archivo);
>>>>>>> .r187
	while (!archivo.eof()) {
		if (termino.length() > 0 && validador->validarTermino(termino)) {
			std::string terminoStemado = stemmer->stemPalabra(termino);

			// Por si justo la palabra que entra es un stemm y luego de procesar queda vacia
			if (terminoStemado.size() > 0) {
				contenedorLexico->insertarPalabra(terminoStemado);
			}
		}

<<<<<<< .mine
		/*terminoSiguiente = lector->obtenerToken(archivo);

		if (termino.length() > 0 && validador->validarTermino(termino)) {
			if (validador->esPalabraCompuesta(termino, terminoSiguiente) &&
				std::count(termino.begin(), termino.end(), ' ') < MAX_PALABRAS) {
				if (terminoSiguiente.length() > 0) {
					termino += " " + terminoSiguiente;
				}
			}else {
				std::string terminoStemado = stemmer->stemPalabra(termino);

				// Por si justo la palabra que entra es un stemm y luego de procesar queda vacia
				if (terminoStemado.size() > 0) {
					contenedorLexico->insertarPalabra(terminoStemado);

				}

				/*terminosOraciones.push_back(termino);
				if (terminosOraciones.size() == PALABRAS_FRASE) {
					std::string bufferOracion;
					std::list<std::string>::iterator it;
					for (it = terminosOraciones.begin(); it != terminosOraciones.end(); ++it) {
						bufferOracion += (*it) + " ";
					}

					contenedorOraciones->insertarPalabra(bufferOracion); // TODO eliminar segundo parametro

					// TODO Mantener 3 terminos anteriores
					terminosOraciones.pop_front();
				}*/

			/*	termino = terminoSiguiente;
			}
		}else {
			termino = terminoSiguiente;
		}
	}*/

		/*termino = lector->obtenerToken(archivo);
	}*/

	archivo.close();
	return true;
}

Trie* Parser::obtenerContenedorLexico() {
	return contenedorLexico;
}

std::string Parser::parsearPalabra(std::string palabra){

	std::string palabraParseada="";

	for(unsigned int i=0; i<palabra.size();i++){

		if( (palabra.at(i)>=65 && palabra.at(i)<=90 ) || (palabra.at(i)>=97 && palabra.at(i)<=122) ){
			palabraParseada += palabra.at(i);
		}

	}

	return palabraParseada;
}

//Trie* Parser::obtenerContenedorOraciones() {
//	return contenedorOraciones;
//}

void Parser::persistirLexico(std::string pathDiccionario, std::string pathOffsetDiccionario) {

    std::ofstream lexico;
    std::ofstream offsetLexico;

    lexico.open(pathDiccionario.c_str());
    offsetLexico.open(pathOffsetDiccionario.c_str());

    contenedorLexico->persistirPalabras_INI(&lexico, &offsetLexico);

    lexico.close();
    offsetLexico.close();
}
