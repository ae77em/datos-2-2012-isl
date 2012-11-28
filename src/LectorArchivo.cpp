#include "LectorArchivo.h"

std::string LectorArchivo::obtenerToken(std::ifstream &archivo) {
	int c;
	std::string palabra;

	while (palabra.length() < MAX_LENGTH && (c = archivo.get()) != EOF && isalnum(c)) {
        palabra += c;
	}

	return palabra;
}
