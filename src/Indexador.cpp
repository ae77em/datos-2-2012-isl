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

    std::cout<<"COMIENZA PERSISTENCIA DICCIONARIOS"<<std::endl;

    parser->persistirLexico(this->obtenerPathDiccionarioLexico());
    parser->persistirOraciones(this->obtenerPathDiccionarioOraciones());

/*	std::cout<<"COMIENZA PONDERACION MATRIZ POR TERMINOS"<<std::endl;

	std::string pathMatrizTerminos = ponderador->ponderar(parser->obtenerContenedorLexico(), persistidor, persistidor->obtenerPath());

	std::cout<<"COMIENZA PONDERACION MATRIZ POR ORACIONES"<<std::endl;

	std::string pathMatrizOraciones = ponderador->ponderar(parser->obtenerContenedorOraciones(), persistidorOraciones, persistidorOraciones->obtenerPath());

	std::cout<<"COMIENZA PERSISTENCIA DICCIONARIOS"<<std::endl;

    parser->persistirLexico(this->obtenerPathDiccionarioLexico());
    parser->persistirOraciones(this->obtenerPathDiccionarioOraciones());

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
*/
	return true;

}

std::string Indexador::obtenerPathDiccionarioLexico(){

	return pathDiccionarioTerminos;

}

std::string Indexador::obtenerPathDiccionarioOraciones(){

	return pathDiccionarioOraciones;

}


unsigned int Indexador::obtenerCanTopicos(){

	return cantTopicos;

}

void Indexador::crearCarpetaRepo(){


	if(mkdir(this->pathCarpetaRepo.c_str(), S_IRWXG| S_IRWXO| S_IRWXU)!=0){ //devuelve cero si se pudo crear el dire
		std::cout<<"no se pudo crear carpeta de repo"<<std::endl;
	}
}

void Indexador::generarPaths(){

		pathCarpetaRepo = nombreIndice;

		pathMatrizTermXDoc= pathCarpetaRepo + "/termXDoc__";
		pathMatrizTermXDoc += nombreIndice;

		pathMatrizOracionesXDoc=pathCarpetaRepo + "/oracionesXDoc_";
		pathMatrizOracionesXDoc += nombreIndice;

		pathMatrizTermXDocPrePonderada=pathCarpetaRepo + "/termXDoc_PrePonderada_";
		pathMatrizTermXDocPrePonderada += nombreIndice;

		pathMatrizOracionesXDocPrePonderada=pathCarpetaRepo + "/oracionesXDoc_PrePonderada_";
		pathMatrizOracionesXDocPrePonderada += nombreIndice;

		pathMatrizTermXDocPonderada=pathCarpetaRepo + "/termXDoc_Ponderada_";
		pathMatrizTermXDocPonderada += nombreIndice;

		pathMatrizOracionesXDocPonderada=pathCarpetaRepo + "/oracionesXDoc_Ponderada_";
		pathMatrizOracionesXDocPonderada += nombreIndice;

		pathSVDTerminos=pathCarpetaRepo + "/indiceSVDTerminos_";
		pathSVDTerminos += nombreIndice;

		pathSVDOraciones=pathCarpetaRepo + "/indiceSVDOraciones_";
		pathSVDOraciones += nombreIndice;

		pathDiccionarioTerminos=pathCarpetaRepo + "/diccionarioTerminos";
		pathDiccionarioTerminos += nombreIndice;

		pathDiccionarioOraciones=pathCarpetaRepo + "/diccionarioOraciones";
		pathDiccionarioOraciones+= nombreIndice;

		/*std::cout<<pathMatrizTermXDoc<<std::endl;
		std::cout<<pathMatrizOracionesXDoc<<std::endl;
		 */
}
