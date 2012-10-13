#ifndef __INDEXER_H_
#define __INDEXER_H_

#include <string>

#include "Lister.h"
#include "Parser.h"
#include "Ponderer.h"

class Indexer {
	private:
		Lister* listador;
		Parser* parser;
		Ponderer* ponderador;
	public:
		Indexer();
		~Indexer();
		
		std::bool crearIndice(std::string nombrerepositorio, int cantTopicos, 
							  std::string directorio);
};

#endif
