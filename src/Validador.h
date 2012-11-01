#ifndef __VALIDADOR_H_
#define __VALIDADOR_H_

#include <string>

class Validador {
	private:
		bool validarNumero(std::string numero);
	public:
		Validador();
		~Validador();

		bool validarTermino(std::string termino);


		bool esPalabraCompuesta(std::string termino, std::string terminoSiguiente);
};

#endif
