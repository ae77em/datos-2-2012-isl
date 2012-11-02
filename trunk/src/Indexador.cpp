#include "Indexador.h"

#include <iostream>

Indexador::Indexador() {
	listador = new ListadorDeArchivos();
	parser = new Parser();
	persistidor = new Persister("matrizFreqLoc.mm");
	ponderador = new Ponderer();
	calculador = new CalculadorLSI();
}

Indexador::~Indexador() {
	delete listador;
	delete parser;
	delete persistidor;
	delete ponderador;
	delete calculador;
}


/**
 * Realiza los procesos necesarios para la creacion del indice
 */
bool Indexador::crearIndice(std::string nombreRepositorio, int cantTopicos, std::string directorio) {

	std::list<std::string>* archivos = listador->listarArchivos(directorio);

	std::list<std::string>::iterator iterador;

	for (iterador = archivos->begin(); iterador != archivos->end(); iterador++) {

		std::string nombreArchivo = (*iterador);

		if (!parser->parsearArchivo(nombreArchivo)) {
			std::cerr << "El archivo " << nombreArchivo << " no pudo ser parseado" << std::endl;
		}

		parser->obtenerContenedorLexico()->aumentarCantidadDeDocParseados();

		// vuelvo los datos obtenidos del documento parseado a disco
		persistidor->persistirDatos(parser->obtenerContenedorLexico()->buscarPalabrasDelDocParseado_INI(), parser->obtenerContenedorLexico()->obtenerCantidadDeDocumentosParseados());

		//preparo el trie para una nueva parseada
		parser->obtenerContenedorLexico()->inicializarFrecuenciasLocales();
		parser->obtenerContenedorLexico()->vaciarContenedorParcial();
	}

	persistidor->cerrar();
	//ponderador->ponderar(parser->obtenerContenedorLexico(), persistidor);
    parser->persistirLexico();

    calculador->calcularLSI(cantTopicos);

    delete archivos;
	return true;

}
