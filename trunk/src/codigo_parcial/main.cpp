#include <iostream>
#include <string>

#include "Indexador.h"
#include "Ponderador.h"
#include <Eigen/Sparse>

using namespace Eigen;

void calculoPonderacion(){

	MatrixXf m(5,5);
	Ponderador pond;

	for (unsigned i = 0; i < 5; i++ )
		for (unsigned j = 0; j < 5; j++ ){

			/* genero un float random entre 0 y 1 */
			float r = (float)rand()/(float)RAND_MAX;

			m(i,j) = r;

		}


	std::cout << "Matriz antes de ponderacion" << std::endl;
	std::cout << m;
	pond.ponderacionLocal(m);
	std::cout << "Matriz despues de ponderacion local" << std::endl;
	std::cout << m;
	pond.ponderacionGlobal(m,0);
	std::cout << "Matriz antes de ponderacion global" << std::endl;
	std::cout << m;

}

int main (int argc, char *argv[]) {

	calculoPonderacion();

/*
	Indexador indexador;
	std::string nombreRepositorio;
	std::string directorio;
	int cantTopicos;
	
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
	
	std::cerr << "El indice fue creado satisfactoriamente.";*/
	return 0;
}


