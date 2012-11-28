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
	if (validarNumero(termino) && termino.length() > LONG_MAX_NUMERO) {
		return false;
	}

	return true;
}
