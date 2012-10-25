#ifndef __READER_H_
#define __READER_H_

#include <fstream>

class LectorArchivo {
	private:
	public:
		std::string obtenerToken(std::ifstream &archivo);
};

#endif
