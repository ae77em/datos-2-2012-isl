#include "Ponderer.h"
#include "Persister.h"


Ponderer::Ponderer(Trie* unTrie) {

	this->contenedorParcialEntropia = unTrie->exportarDatosParaEntropia_INI();
	this->cantidadDocumentosEnLaColeccion = unTrie->obtenerCantidadDeDocumentosParseados();

}

Ponderer::~Ponderer() {
	// TODO Auto-generated destructor stub
}

void Ponderer::calcularEntropia(Persister* unPersister){

	for(register int i=0; i<this->cantidadDocumentosEnLaColeccion; i++){

		list<TregistroArchivo*>* columna = unPersister->obtenerColumnaMatriz(i+1);//el formato de la matriz arrance desde 1

	}

}
