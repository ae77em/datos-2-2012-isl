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

			// vuelco los datos obtenidos del documento parseado a disco
			persistidor->persistirDatos(parser->obtenerContenedorLexico()->buscarPalabrasDelDocParseado_INI(), parser->obtenerContenedorLexico()->obtenerCantidadDeDocumentosParseados());

			//preparo el trie para una nueva parseada
			parser->obtenerContenedorLexico()->inicializarFrecuenciasLocales();
			parser->obtenerContenedorLexico()->vaciarContenedorParcial();
			std::cout<<"libro: "<<parser->obtenerContenedorLexico()->obtenerCantidadDeDocumentosParseados()<<std::endl;
		}
	}

	nombreArchivos.close();
	persistidor->cerrar();

	std::cout<<"COMIENZA PONDERACION MATRIZ POR TERMINOS"<<std::endl;

	ponderador->ponderar(parser->obtenerContenedorLexico(), persistidor, this->pathMatrizTermXDocPonderada);

	parser->obtenerContenedorLexico()->recorrer();

	std::cout<<"COMIENZA PERSISTENCIA DICCIONARIOS"<<std::endl;

    parser->persistirLexico(pathDiccionarioTerminos,pathOffsetDiccionarioTerminos);

    //aca  deberian de ir los destructoures de los trie,

    std::cout<<"CALCULANDO SVD TERMINOS"<<std::endl;
    calculador->calcularLSI(this->obtenerCanTopicos(),this->pathMatrizTermXDocPonderada,this->pathCarpetaRepo);

    persistidor->cerrar();

    delete archivos;

    std::cout<<"FIN"<<std::endl;

	return true;

}

std::string Indexador::obtenerPathDiccionarioLexico() {
	return pathDiccionarioTerminos;
}

unsigned int Indexador::obtenerCanTopicos() {
	return cantTopicos;
}

void Indexador::crearCarpetaRepo() {
	// Devuelve cero si se pudo crear el dire
	if(mkdir(this->pathCarpetaRepo.c_str(), S_IRWXU | S_IRGRP | S_IXGRP | S_IROTH | S_IXOTH ) != 0) {
		std::cerr << "No se pudo crear la carpeta del repositorio: " << pathCarpetaRepo << std::endl;
	}
}

void Indexador::generarPaths(){
	std::string home = getenv("HOME");
	pathCarpetaRepo = home + "/" + nombreIndice;

	pathMatrizTermXDoc = pathCarpetaRepo + "/MatriztermXDoc";
	pathMatrizTermXDocPonderada = pathCarpetaRepo + "/MatriztermXDoc_Ponderada";
	pathSVDTerminos = pathCarpetaRepo + "/SVDTerminos";
	pathDiccionarioTerminos = pathCarpetaRepo + "/diccionarioTerminos";
	pathOffsetDiccionarioTerminos = pathCarpetaRepo + "/offsetDiccionarioTermino";
	pathNombreArchivosTerminos = pathCarpetaRepo + "/nombreArchivos";
}
