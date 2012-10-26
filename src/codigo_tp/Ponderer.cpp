#include "Ponderer.h"
#include "Persister.h"
#include <math.h>


Ponderer::Ponderer(Trie* unTrie,Persister* unP) {

	this->contenedorParcialEntropia = unTrie->exportarDatosParaEntropia_INI();
	this->cantidadDocumentosEnLaColeccion = unTrie->obtenerCantidadDeDocumentosParseados();
	this->persister=unP;

}

Ponderer::~Ponderer() {
	// TODO Auto-generated destructor stub
}

void Ponderer::calcularEntropia(){

	for(register unsigned int i=0; i<this->cantidadDocumentosEnLaColeccion; i++){

		list<TregistroArchivo*>* columna = persister->obtenerColumnaMatriz(i+1);//el formato de la matriz arrance desde 1

		list<TregistroArchivo*>::iterator b = columna->begin();
		list<TregistroArchivo*>::iterator e = columna->end();

		while(b!=e){
			TregistroArchivo* auxReg = *b; //uso el id como indice del vector que contiene las entropias parciales

			TacumEntropia* auxEntropia = this->contenedorParcialEntropia->at(auxReg->fil -1);

			double localDivGlobal = ((double)auxReg->freq)/((double)auxEntropia->infoTerm->ocurrenciasEnLaColeccion);

			auxEntropia->acumEntropia = auxEntropia->acumEntropia + (localDivGlobal*(log(localDivGlobal)/log(2)));

			b++;
		}

		this->dividirTodoPorLog();

		persister->destruir();
	}

}

void Ponderer::dividirTodoPorLog(){
	for(register unsigned int i=0; i<this->contenedorParcialEntropia->size(); i++){
		this->contenedorParcialEntropia->at(i)->acumEntropia = this->contenedorParcialEntropia->at(i)->acumEntropia / (log(cantidadDocumentosEnLaColeccion)/log(2));
	}
}

void Ponderer::ponderarLocarPorGlobal(){

	Persister matrizPonderada("matrizPonderada.mm");

}

