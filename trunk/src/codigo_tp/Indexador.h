#ifndef __INDEXADOR_H_
#define __INDEXADOR_H_

#include <string>
#include <list>

#include "Lister.h"
#include "Parser.h"

class Indexador {
	private:
		Lister* listador;
		Parser* parser;

	public:
		Indexador();
		~Indexador();
		
		bool crearIndice(std::string nombrerepositorio, int cantTopicos, std::string directorio);
};

#endif
