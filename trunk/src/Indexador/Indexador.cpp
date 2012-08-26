/*
 * Indexador.cpp
 *
 *  Created on: 27/11/2011
 *      Author: esteban
 */

#include "Indexador.h"
#include "../AnalizadorGramatico/AnalizadorGramatico.h"


Indexador::Indexador() {
	//contenedorDePalabras = new PseudoTrie;
	parser = new AnalizadorGramatico(*contenedorDePalabras);
	listaDeDirectorios = new list<string>;

}

void  Indexador::indexarDirectorio(string path) {

	/*int* contDir = new int; *contDir = 0;
	int* contArchivo = new int; *contArchivo = 0;
	int* contOtroTipoDeArchivo = new int; *contOtroTipoDeArchivo = 0;
	unsigned colIni = 0;
	string unaRuta;
	RecorredorDeDirectorios recorredor;*/

	//recorredor.contarDirectoriosArchivos(path,contDir,contArchivo,contOtroTipoDeArchivo);

	//listaDeDirectorios = recorredor.obtenerListaDeDirectorios();

	// si la matriz ya existia entonces la ponderacion la hace desde
	// la primer columna no ponderada
	//if ( contenedorDePalabras->getIndice()  )
		//colIni = contenedorDePalabras->getIndice().cols();

	/*listaDeDirectorios->push_front(path);

	if ( listaDeDirectorios->tieneDatos() ){
		while ( listaDeDirectorios->tieneDatos() ){
			unaRuta = listaDeDirectorios->obtenerDato();
			parser->parsearArchivo(unaRuta);
			contenedorDePalabras->buscarPalabrasDeLaParseada_INI();
		}

		Eigen::MatrixXf* mat = contenedorDePalabras->getIndice(); //mat(3,3)

		util.ponderacionLocal(*mat);
		util.ponderacionGlobal(*mat,colIni);

		cout<<"INICIO LSI\n";
		LSI lsi(*mat);

		cout<<"INDEXACION FINALIZADA";
	}

	else cout<<"NO HA HABIDO INDEXACION";*/

}

Indexador::~Indexador() {
	delete contenedorDePalabras;
	delete parser;
	delete listaDeDirectorios;
}

