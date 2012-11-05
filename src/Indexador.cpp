#include "Indexador.h"

#include <iostream>

Indexador::Indexador(std::string nombreIndice, unsigned int cantTopicos) {
	listador = new ListadorDeArchivos();
	parser = new Parser();

	std::string nombreIndiceTerminos("termXdoc_terminos_");

	nombreIndiceTerminos += nombreIndice;

	persistidor = new Persister(nombreIndice);

	std::string nombreIndiceOraciones("termXdoc_oraciones_");

	nombreIndiceOraciones += nombreIndice;

	persistidorOraciones = new Persister(nombreIndiceOraciones);
	ponderador = new Ponderer();
	calculador = new CalculadorLSI();

	this->nombreIndice = nombreIndice;
	this->cantTopicos = cantTopicos;
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

	ponderador->ponderar(parser->obtenerContenedorLexico(), persistidor, this->obtenerNombreIndice());

	std::cout<<"COMIENZA PONDERACION MATRIZ POR ORACIONES"<<std::endl;

	//despues ver como aprolijar esta parte
	std::string nombreMatrizOraciones(this->obtenerNombreIndice());
	nombreMatrizOraciones += "oraciones";

	ponderador->ponderar(parser->obtenerContenedorOraciones(), persistidorOraciones, nombreMatrizOraciones);

	std::cout<<"COMIENZA PERSISTENCIA DICCIONARIOS"<<std::endl;

    parser->persistirLexico(this->obtenerNombreIndice());
    parser->persistirOraciones(this->obtenerNombreIndice());

   /*
    * std::cout<<"CALCULANDO SVD"<<std::endl;
    * calculador->calcularLSI(this->obtenerCantTopicos());
    persistidor->parserLSI(this->obtenerCantTopicos());*/

    persistidor->cerrar();
    persistidorOraciones->cerrar();


    // TODO para las oraciones, no se como se hace
    /*
    calculador->calcularLSI(cantTopicos);
	persistidor->parserLSI(cantTopicos);
	persistidor->cerrar();
    */
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
