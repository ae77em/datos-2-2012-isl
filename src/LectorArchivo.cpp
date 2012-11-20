#include "LectorArchivo.h"

std::string LectorArchivo::obtenerToken(std::ifstream &archivo) {
	int c;
	std::string palabra;

	while ((c = archivo.get()) != EOF && isalpha(c) && palabra.length() < (MAX_LENGTH -1)) {
        palabra += c;
	}

	return palabra;
}
