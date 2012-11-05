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
		Ponderer* ponderadorOraciones;
		Persister* persistidor;
		Persister* persistidorOraciones;
		CalculadorLSI* calculador;

		std::string nombreIndice;
		unsigned int cantTopicos;

	public:
		Indexador(std::string nombreIndice, unsigned int cantTopicos);
		~Indexador();

		bool crearIndice(std::string nombreRepositorio, int cantTopicos, std::string directorio);

		std::string obtenerNombreIndice();
		unsigned int obtenerCanTopicos();


	private:
		void calcularLSI(int,std::string);
};

#endif
