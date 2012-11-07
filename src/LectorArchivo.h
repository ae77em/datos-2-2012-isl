#ifndef __READER_H_
#define __READER_H_

#include <fstream>

class LectorArchivo {
	private:
	public:
		/**
		 * Obtiene un termino del archivo pasado como parametro.
		 * Solo toma caracteres alfanumericos.
		 */
		std::string obtenerToken(std::ifstream &archivo);
};

#endif
