#include "Validador.h"

Validador::Validador() {

}

Validador::~Validador() {

}

bool Validador::validarTermino(std::string termino) {


	return true;
}

/**
 * Valida que todos los caracteres del numero sean numericos.
 */
bool Validador::validarNumero(std::string numero) {
	for (unsigned int i = 0; i < numero.length(); i++) {
		if (!isdigit(numero[i])) {
			return false;
		}
	}

	return true;
}

/**
 * Valida si los terminos forman un mismo concepto.
 *
 * Tecnicas:
 * - Ver si las dos palabras empiezan con mayuscula. Ej. San Francisco
 * - Si la primer palabra empieza con mayuscula y la segunda es un numero.
 */
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
