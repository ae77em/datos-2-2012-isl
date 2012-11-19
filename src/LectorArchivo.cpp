#include "LectorArchivo.h"

std::string LectorArchivo::obtenerToken(std::ifstream &archivo) {
	char c;
	std::string palabra;

    c = archivo.get();
	while (!archivo.eof() && isalnum(c) && palabra.length() < (MAX_LENGTH -1)) {
        palabra += c;
		c = archivo.get();
	}

	palabra += c;
	return palabra;
}
