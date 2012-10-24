#include "Indexador.h"

Indexador::Indexador() {
	listador = new ListadorDeArchivos();
	parser = new Parser();

}

Indexador::~Indexador() {
	delete listador;
	delete parser;

}

bool Indexador::crearIndice(std::string nombrerepositorio, int cantTopicos,std::string directorio) {
	// Listo los archivos
	std::list<std::string>* archivosAParsear = listador->listarArchivos();
	std::list<std::string>::iterator iterador = archivosAParsear->begin();
	
	// Parseo los archivos
	for ( ; iterador != archivosAParsear->end(); iterador++) {
		if (!parser->parsearArchivo(*iterador)) {
			std::cerr << "El archivo " << *iterador << " no pudo ser parseado" << std::endl;
		}
	}
	
	// Aca hay que realizar la ponderacion

	return true;

}
