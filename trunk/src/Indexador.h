#ifndef __INDEXADOR_H_
#define __INDEXADOR_H_

#include <string>
#include <list>

#include "ListadorDeArchivos.h"
#include "Parser.h"
#include "Ponderer.h"
#include "Persister.h"


class Indexador {
	private:
		ListadorDeArchivos* listador;
		Parser* parser;

		///agregado por FEDE
		Ponderer* ponderador;
		Persister* persistidor;
		///

	public:
		Indexador();
		~Indexador();
		
		bool crearIndice(std::string nombreRepositorio, int cantTopicos, std::string directorio);
};

#endif