#include <cstdlib>
#include <iostream>
#include <string>

#include "Indexador.h"

int main (int argc, char *argv[]) {
	Indexador* indexador;
	std::string nombreRepositorio;
	std::string ruta;
	int cantTopicos;
	
	// Validacion de los argumentos
	if (argc < 4) {
		std::cerr << "Uso del programa: " << std::endl;
		std::cerr << "TPGrupoXXi <nombre repositorio> <cantidad topicos> <directorio> " << std::endl;
		
		return 1;
	}
	
	nombreRepositorio = argv[1];
	cantTopicos = atoi(argv[2]);
	ruta = argv[3];

	
	// Creo el indice
	indexador = new Indexador(nombreRepositorio,cantTopicos);
	if (!indexador->crearIndice(nombreRepositorio, cantTopicos, ruta)) {
		std::cerr << "El indice no pudo ser creado." << std::endl;

		return 1;
	}
	
	delete indexador;
	return 0;
}


