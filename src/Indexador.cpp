#include "Indexador.h"

#include <iostream>

Indexador::Indexador() {
	listador = new ListadorDeArchivos();
	parser = new Parser();
	persistidor = new Persister("matrizFreqLoc.mm");
	ponderador = new Ponderer();
}

Indexador::~Indexador() {
	delete listador;
	delete parser;
	delete persistidor;
	delete ponderador;
}

bool Indexador::crearIndice(std::string nombreRepositorio, int cantTopicos, std::string directorio) {
	// Listo los archivos
	std::list<std::string>* archivos = listador->listarArchivos(directorio);

	// Parseo los archivos y vuelco su data al disco
	std::list<std::string>::iterator iterador;

	for (iterador = archivos->begin(); iterador != archivos->end(); iterador++) {
		std::string nombreArchivo = (*iterador);

		if (!parser->parsearArchivo(nombreArchivo)) {
			std::cerr << "El archivo " << nombreArchivo << " no pudo ser parseado" << std::endl;
		}

		parser->obtenerContenedorLexico()->aumentarCantidadDeDocParseados();

		std::cout<<"DOC: "<<parser->obtenerContenedorLexico()->obtenerCantidadDeDocumentosParseados()<<std::endl;

		// vuelvo los datos obtenidos del documento parseado a disco
		persistidor->persistirDatos(parser->obtenerContenedorLexico()->buscarPalabrasDelDocParseado_INI(),parser->obtenerContenedorLexico()->obtenerCantidadDeDocumentosParseados());
		//preparo el trie para una nueva parseada
		parser->obtenerContenedorLexico()->inicializarFrecuenciasLocales();

		parser->obtenerContenedorLexico()->vaciarContenedorParcial();

		//finaliza ciclo de parseo
	}

	std::cout<<"PONDERANDO"<<std::endl;

	persistidor->cerrar(); //DESPUES HAY QUE REFACTORIZAR ESTE METODO

	ponderador->ponderar(parser->obtenerContenedorLexico(),persistidor);

    parser->persistirLexico();

	return true;
}
