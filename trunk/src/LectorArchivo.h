#ifndef __READER_H_
#define __READER_H_

#include <fstream>

#define MAX_LENGTH 20

class LectorArchivo {
	private:
	public:
		/**
		 * Obtiene un termino del archivo pasado como parametro.
		 * Solo toma caracteres alfanumericos. Hasta 20 caracteres.
		 */
		std::string obtenerToken(std::ifstream &archivo);
};

#endif
