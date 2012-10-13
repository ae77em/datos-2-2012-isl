#include "Indexer.h"

#include <list>

Indexer::Indexer() {
	listador = new Lister();
	parser = new Parser();
	ponderador = new Ponderer();
}

Indexer::Indexer() {
	delete listador;
	delete parser;
	delete ponderador;
}

std::bool Indexer::crearIndice(std::string nombrerepositorio, int cantTopicos, 
							  std::string directorio) {
	// Listo los archivos
	std::list<std::string>* archivosAParsear = listador->listarArchivos();
	
	// Parseo los archivos
	for (std::list<std::string>::iterator iterador = archivosAParsear->begin(); 
		 iterador != archivosAParsear->end(); iterador++) {
		if (!parser->parsearArchivo(*iterador)) {
			std::cerr << "El archivo " << *iterador << " no pudo ser parseado" << std::endl;
		}
	}
	
	// Aca hay que realizar la ponderacion
}
