#include "LectorArchivo.h"

std::string LectorArchivo::obtenerToken(std::ifstream &archivo) {
	char c;
	std::string palabra;

    // Iteramos sobre el contenido del archivo
    archivo.get(c);
	while (!archivo.eof() && isalnum(c)) {
        palabra += c;
		archivo.get(c);
	}
	return palabra;
}
