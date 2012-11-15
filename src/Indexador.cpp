#include "Indexador.h"

#include <iostream>

Indexador::Indexador(std::string nombreIndice, unsigned int cantTopicos) {

	this->nombreIndice = nombreIndice;
	this->cantTopicos = cantTopicos;

	listador = new ListadorDeArchivos();
	parser = new Parser();

	std::string nombreIndiceTerminos("termXdoc_terminos_");

	nombreIndiceTerminos += nombreIndice;

	persistidor = new Persister(nombreIndiceTerminos);

	std::string nombreIndiceOraciones("termXdoc_oraciones_");

	nombreIndiceOraciones += nombreIndice;

	persistidorOraciones = new Persister(nombreIndiceOraciones);

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

	std::cout<<"COMIENZA INDEXACION"<<std::endl;

	std::list<std::string>* archivos = listador->listarArchivos(directorio);

	std::list<std::string>::iterator iterador;
	for (iterador = archivos->begin(); iterador != archivos->end(); iterador++) {
		std::string nombreArchivo = (*iterador);

		if (!parser->parsearArchivo(nombreArchivo)) {
			std::cerr << "El archivo " << nombreArchivo << " no pudo ser parseado" << std::endl;
		}else{
			parser->obtenerContenedorLexico()->aumentarCantidadDeDocParseados();
			parser->obtenerContenedorOraciones()->aumentarCantidadDeDocParseados();

			// vuelco los datos obtenidos del documento parseado a disco
			persistidor->persistirDatos(parser->obtenerContenedorLexico()->buscarPalabrasDelDocParseado_INI(), parser->obtenerContenedorLexico()->obtenerCantidadDeDocumentosParseados());
			persistidorOraciones->persistirDatos(parser->obtenerContenedorOraciones()->buscarPalabrasDelDocParseado_INI(), parser->obtenerContenedorOraciones()->obtenerCantidadDeDocumentosParseados());

			std::cout<<"SE PARSEO DOC: "<<parser->obtenerContenedorOraciones()->obtenerCantidadDeDocumentosParseados()<<std::endl;

			//preparo el trie para una nueva parseada
			parser->obtenerContenedorLexico()->inicializarFrecuenciasLocales();
			parser->obtenerContenedorLexico()->vaciarContenedorParcial();

			parser->obtenerContenedorOraciones()->inicializarFrecuenciasLocales();
			parser->obtenerContenedorOraciones()->vaciarContenedorParcial();
		}
	}

	persistidor->cerrar();
    persistidorOraciones->cerrar();

	std::cout<<"COMIENZA PONDERACION MATRIZ POR TERMINOS"<<std::endl;

	std::string pathMatrizTerminos = ponderador->ponderar(parser->obtenerContenedorLexico(), persistidor, persistidor->obtenerPath());

	std::cout<<"COMIENZA PONDERACION MATRIZ POR ORACIONES"<<std::endl;

	std::string pathMatrizOraciones = ponderador->ponderar(parser->obtenerContenedorOraciones(), persistidorOraciones, persistidorOraciones->obtenerPath());

	std::cout<<"COMIENZA PERSISTENCIA DICCIONARIOS"<<std::endl;

    parser->persistirLexico(this->obtenerNombreIndice());
    parser->persistirOraciones(this->obtenerNombreIndice());

    //aca  deberian de ir los destructoures de los trie,

    std::cout<<"CALCULANDO SVD TERMINOS"<<std::endl;
    calculador->calcularLSI(this->obtenerCanTopicos(),pathMatrizTerminos);
    //persistidor->parserLSI(this->obtenerCantTopicos());

    // TODO para las oraciones, no se como se hace
    std::cout<<"CALCULANDO SVD ORACIONES"<<std::endl;

    calculador->calcularLSI(cantTopicos,pathMatrizOraciones);

    //persistidor->parserLSI(cantTopicos);

    persistidor->cerrar();
    persistidorOraciones->cerrar();



    delete archivos;

    std::cout<<"FIN"<<std::endl;

	return true;

}

std::string Indexador::obtenerNombreIndice(){

	return nombreIndice;

}


unsigned int Indexador::obtenerCanTopicos(){

	return cantTopicos;

}

void Indexador::generarPaths(){

		pathMatrizTermXDoc("matricesTermDoc/termXDoc__");
		pathMatrizTermXDoc += nombreIndice;

		pathMatrizOracionesXDoc("matricesTermDoc/oracionesXDoc_");
		pathMatrizOracionesXDoc += nombreIndice;

		pathMatrizTermXDocPrePonderada("matricesPrePonderadas/termXDoc_PrePonderada_");
		pathMatrizTermXDocPrePonderada += nombreIndice;

		pathMatrizOracionesXDocPrePonderada("matricesPrePonderadas/oracionesXDoc_PrePonderada_");
		pathMatrizOracionesXDocPrePonderada += nombreIndice;

		pathMatrizTermXDocPonderada("matricesPonderadas/termXDoc_Ponderada_");
		pathMatrizTermXDocPonderada += nombreIndice;

		pathMatrizOracionesXDocPonderada("matricesPonderadas/oracionesXDoc_Ponderada_");
		pathMatrizOracionesXDocPonderada += nombreIndice;

		pathSVDTerminos("indices/indiceSVDTerminos_");
		pathSVDTerminos += nombreIndice;

		pathSVDOraciones("indices/indiceSVDOraciones_");
		pathSVDOraciones += nombreIndice;

		pathDiccionarioTerminos("diccionarios/diccionarioTerminos");
		pathDiccionarioTerminos += nombreIndice;

		pathDiccionarioOraciones("diccionarios/diccionarioOraciones");
		pathDiccionarioOraciones+= nombreIndice;

}
