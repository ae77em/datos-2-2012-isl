#include <cstring>
#include <iostream>
#include <string>

#include "Consulter.h"
#include "Heap.h"

void procesarArgumento(std::list<std::string>* terminosConsulta, std::string termino) {
	std::string buffer;
	for (unsigned int i = 0; i < termino.length(); i++) {
		if (isalnum(termino[i])) {
			buffer += termino[i];
		}else {
			if (buffer.length() > 0) {
				terminosConsulta->push_back(buffer);
				buffer.clear();
			}
		}
	}
	
	if (buffer.length() > 0) {
		terminosConsulta->push_back(buffer);
		buffer.clear();
	}
}

int main(int argc, char* argv[]) {
	Consulter* consultador;
	std::string nombreRepositorio;

	std::list<std::string>* terminosConsulta = new std::list<std::string>();

	// Validacion de los argumentos
	if (argc < 5) {
		std::cerr << "Uso del programa: " << std::endl;
		std::cerr << "TPGrupoXXq -r <nombre repositorio> -q <t1 t2 ...>" << std::endl;

		delete terminosConsulta;
		return 1;
	}

	nombreRepositorio = argv[2];

	// Almaceno los terminos del query en una lista
	for (int i = 4; i < argc; i++) {
		procesarArgumento(terminosConsulta, argv[i]);
	}

	consultador = new Consulter(nombreRepositorio);
	if (consultador->rankearConsulta(terminosConsulta) == 0) {
		std::cout << "No se han encontrado resultados para la consulta realizada" << std::endl;
	}

	delete terminosConsulta;
	delete consultador;
	
	return 0;
}
