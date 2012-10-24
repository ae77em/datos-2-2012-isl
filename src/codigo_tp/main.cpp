#include <iostream>
#include <string>

#include "Indexador.h"

int main (int argc, char *argv[]) {
	Indexador indexador;
	std::string nombreRepositorio;
	std::string cantTopicos;
	std::string directorio;
	
	if (argc < 4) {
		std::cerr << "Uso del programa: " << std::endl;
		std::cerr << "TPGrupoXXi <repositorio> <topicos> <dir> " << std::endl;
		
		return 1;
	}
	
	nombreRepositorio = argv[1];
	cantTopicos = argv[2];
	directorio = argv[3];
	
	if (indexador.crearIndice(nombreRepositorio, cantTopicos, directorio)) {
		std::cerr << "El indice no pudo ser creado.";
		return 1;
	}
	
	std::cerr << "El indice fue creado satisfactoriamente.";
	return 0;
}


