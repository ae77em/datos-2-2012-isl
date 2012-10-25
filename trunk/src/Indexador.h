#ifndef __INDEXADOR_H_
#define __INDEXADOR_H_

#include <string>
#include <list>

#include "ListadorDeArchivos.h"
#include "Parser.h"

class Indexador {
	private:
		ListadorDeArchivos* listador;
		Parser* parser;
	public:
		Indexador();
		~Indexador();
		
		bool crearIndice(std::string nombreRepositorio, int cantTopicos, std::string directorio);
};

#endif
