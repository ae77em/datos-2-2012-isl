#include "Indexador.h"
#include <sys/stat.h>
#include <sys/types.h>

#include <iostream>

Indexador::Indexador(std::string nombreIndice, unsigned int cantTopicos) {
	this->nombreIndice = nombreIndice;
	this->cantTopicos = cantTopicos;

	this->generarPaths();
	this->crearCarpetaRepo();

	listador = new ListadorDeArchivos();
	parser = new Parser();

	persistidor = new Persister(pathMatrizTermXDoc);
	persistidorOraciones = new Persister(pathMatrizOracionesXDoc);

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

	std::ofstream nombreArchivos;
	nombreArchivos.open(this->pathNombreArchivosTerminos.c_str());

	std::cout<<"COMIENZA INDEXACION"<<std::endl;

	std::list<std::string>* archivos = listador->listarArchivos(directorio);

	std::list<std::string>::iterator iterador;
	int i = 0;
	for (iterador = archivos->begin(); iterador != archivos->end(); iterador++, i++) {
		std::string nombreArchivo = (*iterador);

		if (!parser->parsearArchivo(nombreArchivo)) {
			std::cerr << "El archivo " << nombreArchivo << " no pudo ser parseado" << std::endl;
		}else {
			std::cout << "El archivo " << nombreArchivo << " fue parseado (" << i << ")" << std::endl;

			//extrayendo y persistiendo nombre archivo
			nombreArchivos<<nombreArchivo.substr((nombreArchivo.find_last_of("/\\")+1))<<std::endl;
			parser->obtenerContenedorLexico()->aumentarCantidadDeDocParseados();

			//parser->obtenerContenedorOraciones()->aumentarCantidadDeDocParseados();

			// vuelco los datos obtenidos del documento parseado a disco
			persistidor->persistirDatos(parser->obtenerContenedorLexico()->buscarPalabrasDelDocParseado_INI(), parser->obtenerContenedorLexico()->obtenerCantidadDeDocumentosParseados());
			//persistidorOraciones->persistirDatos(parser->obtenerContenedorOraciones()->buscarPalabrasDelDocParseado_INI(), parser->obtenerContenedorOraciones()->obtenerCantidadDeDocumentosParseados());

			//preparo el trie para una nueva parseada
			parser->obtenerContenedorLexico()->inicializarFrecuenciasLocales();
			parser->obtenerContenedorLexico()->vaciarContenedorParcial();
			std::cout<<"libro: "<<parser->obtenerContenedorLexico()->obtenerCantidadDeDocumentosParseados()<<std::endl;
			//parser->obtenerContenedorOraciones()->inicializarFrecuenciasLocales();
			//parser->obtenerContenedorOraciones()->vaciarContenedorParcial();
		}
	}

	nombreArchivos.close();
	persistidor->cerrar();
	//persistidorOraciones->cerrar();

	std::cout<<"COMIENZA PONDERACION MATRIZ POR TERMINOS"<<std::endl;

	ponderador->ponderar(parser->obtenerContenedorLexico(), persistidor, this->pathMatrizTermXDocPonderada);

	//ponderador->ponderar(parser->obtenerContenedorOraciones(), persistidorOraciones,this->pathMatrizOracionesXDocPonderada);

	parser->obtenerContenedorLexico()->recorrer();

	std::cout<<"COMIENZA PERSISTENCIA DICCIONARIOS"<<std::endl;

    parser->persistirLexico(pathDiccionarioTerminos,pathOffsetDiccionarioTerminos);
    //parser->persistirOraciones(this->obtenerPathDiccionarioOraciones());

    //aca  deberian de ir los destructoures de los trie,

    std::cout<<"CALCULANDO SVD TERMINOS"<<std::endl;
    calculador->calcularLSI(this->obtenerCanTopicos(),this->pathMatrizTermXDocPonderada,this->nombreIndice);

    // TODO para las oraciones, no se como se hace
    //std::cout<<"CALCULANDO SVD ORACIONES"<<std::endl;

    //calculador->calcularLSI(cantTopicos,this->pathMatrizOracionesXDocPonderada);

    //persistidor->parserLSI(cantTopicos);

    persistidor->cerrar();
//  persistidorOraciones->cerrar();

    delete archivos;

    std::cout<<"FIN"<<std::endl;

	return true;

}

std::string Indexador::obtenerPathDiccionarioLexico() {
	return pathDiccionarioTerminos;
}

std::string Indexador::obtenerPathDiccionarioOraciones() {
	return pathDiccionarioOraciones;
}

unsigned int Indexador::obtenerCanTopicos() {
	return cantTopicos;
}

void Indexador::crearCarpetaRepo(){

	if(mkdir(this->pathCarpetaRepo.c_str(), S_IRWXU | S_IRGRP | S_IXGRP | S_IROTH | S_IXOTH )!=0){ //devuelve cero si se pudo crear el dire
		std::cout<<"no se pudo crear carpeta de repo: "<<pathCarpetaRepo<<std::endl;
	}
}

void Indexador::generarPaths(){
		pathCarpetaRepo =  nombreIndice;

		pathMatrizTermXDoc= pathCarpetaRepo + "/MatriztermXDoc__";
		pathMatrizTermXDoc += nombreIndice;

		pathMatrizOracionesXDoc=pathCarpetaRepo + "/MatrizoracionesXDoc_";
		pathMatrizOracionesXDoc += nombreIndice;

		pathMatrizTermXDocPonderada=pathCarpetaRepo + "/MatriztermXDoc_Ponderada_";
		pathMatrizTermXDocPonderada += nombreIndice;

		pathMatrizOracionesXDocPonderada=pathCarpetaRepo + "/MatrizoracionesXDoc_Ponderada_";
		pathMatrizOracionesXDocPonderada += nombreIndice;

		pathSVDTerminos=pathCarpetaRepo + "/SVDTerminos_";
		pathSVDTerminos += nombreIndice;

		pathSVDOraciones=pathCarpetaRepo + "/SVDOraciones_";
		pathSVDOraciones += nombreIndice;

		pathDiccionarioTerminos=pathCarpetaRepo + "/diccionarioTerminos";
		pathDiccionarioTerminos += nombreIndice;

		pathDiccionarioOraciones=pathCarpetaRepo + "/diccionarioOraciones";
		pathDiccionarioOraciones+= nombreIndice;

		pathOffsetDiccionarioTerminos = pathCarpetaRepo + "/offsetDiccionarioTermino";
		pathOffsetDiccionarioTerminos += nombreIndice;


		pathNombreArchivosTerminos=pathCarpetaRepo + "/nombreArchivos";
		pathNombreArchivosTerminos += pathCarpetaRepo;
}
