#include "Validador.h"

Validador::Validador() {

}

Validador::~Validador() {

}

bool Validador::validarNumero(std::string numero) {
	for (unsigned int i = 0; i < numero.length(); i++) {
		if (!isdigit(numero[i])) {
			return false;
		}
	}

	return true;
}

bool Validador::validarTermino(std::string termino) {
	if (validarNumero(termino) && termino.length() > 4) {
		return false;
	}

	return true;
}

bool Validador::esPalabraCompuesta(std::string termino, std::string terminoSiguiente) {
	if (islower(termino[0])) {
		return false;
	}

	if (isdigit(terminoSiguiente[0])) {
		return validarNumero(terminoSiguiente);
	}else if (islower(terminoSiguiente[0])) {
		return false;
	}

	return true;
}
