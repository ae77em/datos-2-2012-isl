#include "LectorArchivo.h"

std::string LectorArchivo::obtenerToken(std::ifstream &archivo) {

	char c;
	std::string palabra;

    c = archivo.get();

    /* mientras sea alfanumerico o no EOF */
	while (!archivo.eof() && isalnum(c)) {
        palabra += c;
		c = archivo.get();
	}
	return palabra;
}
