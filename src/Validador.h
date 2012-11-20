#ifndef __VALIDADOR_H_
#define __VALIDADOR_H_

#include <string>

class Validador {
	private:
		/**
		 * Valida que todos los caracteres del numero sean numericos.
		 */
		bool validarNumero(std::string numero);
	public:
		Validador();
		~Validador();

		/**
		 * Realiza las validaciones necesarias para ver si es un termino valido o no
		 * Tecnicas:
		 * - Si es un numero, limitar su longitud a 4 digitos
		 */
		bool validarTermino(std::string termino);
};

#endif
