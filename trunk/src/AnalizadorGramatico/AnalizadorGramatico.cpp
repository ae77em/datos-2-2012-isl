/*
 * AnalizadorGramatico.cpp
 *
 *  Created on: 03/09/2011
 *      Author: esteban
 */

#include "AnalizadorGramatico.h"
#include "../ArchivoTexto/ArchivoTexto.h"
#include <iostream>
#include <fstream>
#include <cstring>

#ifndef CANTIDAD_DE_SEPARADORES
#define CANTIDAD_DE_SEPARADORES 48
#endif

AnalizadorGramatico::AnalizadorGramatico(){}

AnalizadorGramatico::AnalizadorGramatico(Trie& unTrie){
	trie = unTrie;
}

AnalizadorGramatico::~AnalizadorGramatico() {
	// TODO indicar como seria la destruccion del trie
	// trie->destruirArbol(args...)
}

/*
 * Dado un documento de texto, lo parsea (extrae los terminos relevantes)
 * y los almacena en la estructura dada.
 *
 * @param archivoAparsear: es el puntero al archivo a parsear.
 * @param arbol: es la estructura para guardar las palabras.
 *
 * @return true si termino bien, false caso contrario
 */
bool AnalizadorGramatico::parsearArchivo(std::string& archivoAparsear){

	int* direccion = new int;
	std::string palabra;
	const char* invalidos[CANTIDAD_DE_SEPARADORES] = {"¡!#$%&'( )*+,-.0123456789:;<=>¿?@[]^_`{|}~/\\\"\n"};
	ArchivoTexto archivo;

	archivo.abrirParaLectura(archivoAparsear);
	std::string auxLinea;

	while ( archivo.leerLinea(auxLinea)){
		char *linea = new char[MAX_LENGTH];
		strcpy(linea,auxLinea.c_str());
		char* auxPalabra = strtok(linea,*invalidos);

		while ( auxPalabra != NULL ){
			palabra = auxPalabra;
			Utilidades::pasarAminusculas(palabra);
			trie.insertarPalabra(palabra,direccion);
			auxPalabra = strtok (NULL, *invalidos);
		}
		delete []linea;
		delete auxPalabra;
	}

	//delete archivo; // cierra el archivo, no lo borra
	delete direccion;
	return true;
 }

void AnalizadorGramatico::parsearConsulta( std::string & consulta ){

	std::string palabra;
	const char* invalidos[CANTIDAD_DE_SEPARADORES] = {"¡!#$%&'( )*+,-.0123456789:;<=>¿?@[]^_`{|}~/\\\"\n"};

	char *linea = new char[sizeof(consulta)];
	strcpy(linea,consulta.c_str());
	char* auxPalabra = strtok(linea,*invalidos);

	while ( auxPalabra != NULL ){
		unsigned nroFila = 0;
		palabra = auxPalabra; // esto es porque auxPalabra no es un string
		Utilidades::pasarAminusculas(palabra);
		if ( trie.buscarPalabra(palabra,nroFila) ){
			/*if ( matriz.cols() < nroFila )
				//Utilidades::cambiarFilas(matriz,nroFila);
			matriz(nroFila,0) = 1; // voy formando el vector consulta*/
		}
		auxPalabra = strtok (NULL, *invalidos);
	}

	delete []linea;
	delete auxPalabra;
}









