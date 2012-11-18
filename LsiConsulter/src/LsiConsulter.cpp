#include <iostream>
#include <string>

#include "Consulter.h"

std::string obtenerTerminosQuery(int argc, char* argv[]) {
	std::string query;

	for (int i = 4; i < argc; i++) {
		query += argv[i] + " ";
	}

	return query;
}

int main(int argc, char* argv[]) {
	Consulter* consultador;
	std::string nombreRepositorio;
	std::string query;

	// Validacion de los argumentos
	if (argc < 5) {
		std::cerr << "Uso del programa: " << std::endl;
		std::cerr << "TPGrupoXXq -r <nombre repositorio> -q <t1 t2 ...>" << std::endl;

		return 1;
	}

	nombreRepositorio = argv[2];
	query = obtenerTerminosQuery(argc, argv);

	Consulter* consulter = new Consulter(0, nombreRepositorio);
	consulter->analizarConsulta(query);

	delete consulter;
	return 0;
}