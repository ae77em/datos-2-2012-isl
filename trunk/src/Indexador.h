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
		Persister* persistidorOraciones;
		CalculadorLSI* calculador;

		std::string nombreIndice;
		unsigned int cantTopicos;

	public:
		Indexador(std::string nombreIndice, unsigned int cantTopicos);
		~Indexador();

		bool crearIndice(std::string nombreRepositorio, int cantTopicos, std::string directorio);

		std::string obtenerPathDiccionarioLexico();
		std::string obtenerPathDiccionarioOraciones();

		unsigned int obtenerCanTopicos();

	private:
		void calcularLSI(int,std::string);
		void generarPaths();
		void crearCarpetaRepo();

		std::string pathCarpetaRepo;

		std::string pathMatrizTermXDoc;
		std::string pathMatrizOracionesXDoc;

		std::string pathMatrizTermXDocPrePonderada;
		std::string pathMatrizOracionesXDocPrePonderada;

		std::string pathMatrizTermXDocPonderada;
		std::string pathMatrizOracionesXDocPonderada;

		std::string pathSVDTerminos;
		std::string pathSVDOraciones;

		std::string pathDiccionarioTerminos;
		std::string pathDiccionarioOraciones;

};

#endif
