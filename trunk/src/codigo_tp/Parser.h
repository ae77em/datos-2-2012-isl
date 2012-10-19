#ifndef __PARSER_H_
#define __PARSER_H_

#include "Stemmer.h"
#include "Persister.h"

class Parser {
	private:
		Stemmer* stemmer;
		Persister* persistidor;

	public:
		Parser();
		~Parser();
		bool parsearArchivo(std::string nombreArchivo);
};

#endif
