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
		}else{
			parser->obtenerContenedorLexico()->aumentarCantidadDeDocParseados();
			parser->obtenerContenedorOraciones()->aumentarCantidadDeDocParseados();

			// vuelvo los datos obtenidos del documento parseado a disco
			persistidor->persistirDatos(parser->obtenerContenedorLexico()->buscarPalabrasDelDocParseado_INI(), parser->obtenerContenedorLexico()->obtenerCantidadDeDocumentosParseados());
			persistidor->persistirDatos(parser->obtenerContenedorOraciones()->buscarPalabrasDelDocParseado_INI(), parser->obtenerContenedorOraciones()->obtenerCantidadDeDocumentosParseados());

			//preparo el trie para una nueva parseada
			parser->obtenerContenedorLexico()->inicializarFrecuenciasLocales();
			parser->obtenerContenedorLexico()->vaciarContenedorParcial();

			parser->obtenerContenedorOraciones()->inicializarFrecuenciasLocales();
			parser->obtenerContenedorOraciones()->vaciarContenedorParcial();
		}
	}

//	ponderador->ponderar(parser->obtenerContenedorLexico(), persistidor);
    parser->persistirLexico();
    parser->persistirOraciones();

    calculador->calcularLSI(cantTopicos);
    persistidor->parserLSI(cantTopicos);
    persistidor->cerrar();

    // TODO para las oraciones, no se como se hace
    /*
    calculador->calcularLSI(cantTopicos);
	persistidor->parserLSI(3);
	persistidor->cerrar();
    */
    delete archivos;
	return true;

}
