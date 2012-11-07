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

		/**
		 * Valida si los terminos forman un mismo concepto.
		 *
		 * Tecnicas:
		 * - Ver si las dos palabras empiezan con mayuscula. Ej. San Francisco
		 * - Si la primer palabra empieza con mayuscula y la segunda es un numero.
		 */
		bool esPalabraCompuesta(std::string termino, std::string terminoSiguiente);
};

#endif
