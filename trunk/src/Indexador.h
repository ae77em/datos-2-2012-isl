#ifndef __INDEXADOR_H_
#define __INDEXADOR_H_

#include <string>
#include <list>

#include "ListadorDeArchivos.h"
#include "Parser.h"
#include "Ponderer.h"
#include "Persister.h"
#include "CalculadorLSI.h"

class Indexador {
	private:
		ListadorDeArchivos* listador;
		Parser* parser;
		Ponderer* ponderador;
		Persister* persistidor;
		CalculadorLSI* calculador;

	public:
		Indexador();
		~Indexador();
		
		bool crearIndice(std::string nombreRepositorio, int cantTopicos, std::string directorio);

	private:
		void calcularLSI(int);
};

#endif
