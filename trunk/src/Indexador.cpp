#include "Indexador.h"

#include <iostream>

Indexador::Indexador() {
	listador = new ListadorDeArchivos();
	parser = new Parser();
}

Indexador::~Indexador() {
	delete listador;
	delete parser;
}

bool Indexador::crearIndice(std::string nombreRepositorio, int cantTopicos, std::string directorio) {
	// Listo los archivos
	std::list<std::string>* archivos = listador->listarArchivos(directorio);
	
	// Parseo los archivos
	std::list<std::string>::iterator iterador;
	for (iterador = archivos->begin(); iterador != archivos->end(); iterador++) {
		std::string nombreArchivo = (*iterador);

		if (!parser->parsearArchivo(nombreArchivo)) {
			std::cerr << "El archivo " << nombreArchivo << " no pudo ser parseado" << std::endl;
		}
	}

	return true;
}
