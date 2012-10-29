#include "Ponderer.h"
#include "Persister.h"
#include <math.h>
#include <fstream>
#include <iostream>


Ponderer::Ponderer() {

	this->matrizFreqLoc=NULL;
	this->trie=NULL;
	this->matrizPonderada=NULL;

}

Ponderer::~Ponderer() {
	// TODO Auto-generated destructor stub
}


void Ponderer::ponderar(Trie* unTrie,Persister* unP){

	trie = unTrie;
	matrizFreqLoc = unP;

	matrizFreqLoc->abrir();

    this->calcularEntropia();
    this->ponderarLocarPorGlobal(); //tambien persiste, despues hay que cambiarlo

}


void Ponderer::calcularEntropia(){

	this->contenedorParcialEntropia = trie->exportarDatosParaEntropia_INI();
	this->cantidadDocumentosEnLaColeccion = trie->obtenerCantidadDeDocumentosParseados();

	for(register unsigned int i=0; i<this->cantidadDocumentosEnLaColeccion; i++){

		list<TregistroArchivo*>* columna = matrizFreqLoc->obtenerColumnaMatriz();//el formato de la matriz arrance desde 1

		list<TregistroArchivo*>::iterator b = columna->begin();
		list<TregistroArchivo*>::iterator e = columna->end();

        while(b!=e){
			TregistroArchivo* auxReg = *b; //uso el id como indice del vector que contiene las entropias parciales

			TacumEntropia* auxEntropia = this->contenedorParcialEntropia->at(auxReg->fil -1);

			double localDivGlobal = ((double)auxReg->freq)/((double)auxEntropia->infoTerm->ocurrenciasEnLaColeccion);

			auxEntropia->acumEntropia = auxEntropia->acumEntropia + (localDivGlobal*(log10(localDivGlobal)/log10(2)));

			b++;
		}
		matrizFreqLoc->vaciar(columna);
    }

    this->dividirTodoPorLog();

    matrizFreqLoc->cerrar();

}

void Ponderer::dividirTodoPorLog(){
	for(register unsigned int i=0; i<this->contenedorParcialEntropia->size(); i++){
	   this->contenedorParcialEntropia->at(i)->acumEntropia = this->contenedorParcialEntropia->at(i)->acumEntropia / (log(cantidadDocumentosEnLaColeccion)/log(2));
	}
}

void Ponderer::ponderarLocarPorGlobal(){

	fstream matrizPonderada;
	matrizPonderada.open("matrizPonderada.mm",fstream::out);
	//inicializo cabecera de matriz MM
	matrizPonderada<<"%%MatrixMarket matrix coordinate real general"<<std::endl;
	matrizPonderada<<trie->obtenerCantidadDeDocumentosParseados()<<" "<<trie->obtenerContadorId()<<" "<<trie->obtenerCantidadDePalabrasIngresadas()<<endl;

    //abriendo matriz de ponderacion locales
	matrizFreqLoc->abrir();

	//recorro toda la matriz
	while(!matrizFreqLoc->hayData()){
        list<TregistroArchivo*>* dataCol = matrizFreqLoc->obtenerColumnaMatriz();

		list<TregistroArchivo*>::iterator b = dataCol->begin();
		list<TregistroArchivo*>::iterator e = dataCol->end();
		//recorriendo columnas de la matriz
		while(b!=e){
			TregistroArchivo* aux = *b;

			double entropia = this->contenedorParcialEntropia->at(aux->fil - 1)->acumEntropia;
			double pesoLocal = log10(aux->freq + 1);
			double localPorGlobal = (entropia*pesoLocal);
			//persistiendo
			matrizPonderada<<aux->col<<" "<<aux->fil<<" "<<localPorGlobal<<std::endl;

			b++;
		}
		matrizFreqLoc->vaciar(dataCol);
	}

	matrizPonderada.close();
}

