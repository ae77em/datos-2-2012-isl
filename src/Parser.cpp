#include "Parser.h"
#include "Stemmer.h"

Parser::Parser() {
	lector = new LectorArchivo();
	contenedorLexico = new Trie();
	//stemedor = new Stemmer();

}

Parser::~Parser() {
	delete lector;

	contenedorLexico->destruirArbol_INI();
	delete contenedorLexico;
}

bool Parser::parsearArchivo(std::string nombreArchivo) {

	Stemmer stemedor;
	std::string termino;
	std::ifstream archivo(nombreArchivo.c_str());

	if (!archivo.good()) {
		return false;
	}
	std::cout<<"COMENCE PARSEAR ARCHIVO"<<std::endl;

	//int cont = 0;

	while (!archivo.eof()) {
		termino = lector->obtenerToken(archivo);

		if (termino.length() > 0) {
			// VALIDAR
			std::string terminoStemado = stemedor.stemPalabra(termino);
			int* despuesLoSaco=NULL;
			/* por si justo la palabra que entra es un stemm,
			 * y luego de procesar queda vacia
			 * ESTA VALIDACION SERIA MAS INDICADA DENTRO DEL TRIE.
			 * QUE QUEDE A JUICIO DE FEDE HACERLA O NO.
			 */
			if ( terminoStemado != "" )
				contenedorLexico->insertarPalabraEnRaiz(terminoStemado,despuesLoSaco);

		}
	}
	std::cout<<"TERMINE PARSEAR ARCHIVO"<<std::endl;

	archivo.close();
	return true;
}

Trie* Parser::obtenerContenedorLexico(){

	return contenedorLexico;

}

void Parser::persistirLexico(){

    fstream lexico;
    fstream offsetLexico;

    lexico.open("diccionario.txt",fstream::out);
    offsetLexico.open("offsetLexico.txt",fstream::out);

    contenedorLexico->persistirPalabras_INI(&lexico,&offsetLexico);

    lexico.close();
    offsetLexico.close();

}
