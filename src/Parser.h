#ifndef __PARSER_H_
#define __PARSER_H_

#include <fstream>
#include <iostream>

#include "LectorArchivo.h"

class Parser {
	private:
		LectorArchivo* lector;
	public:
		Parser();
		~Parser();
		bool parsearArchivo(std::string nombreArchivo);
};

#endif
