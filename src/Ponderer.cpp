#include "Ponderer.h"
#include "Persister.h"
#include <math.h>
#include <fstream>
#include <iostream>


Ponderer::Ponderer() {
	contenedorParcialEntropia = NULL;
	cantidadDocumentosEnLaColeccion = 0;
	this->matrizFreqLoc=NULL;
	this->trie=NULL;
	this->matrizPonderada=NULL;

}

Ponderer::~Ponderer() {
	// TODO Auto-generated destructor stub
}


void Ponderer::ponderar(Trie* unTrie,Persister* unP,std::string pathMatrizPonderada){

	trie = unTrie;
	matrizFreqLoc = unP;

	//guardo path de la matriz donde se va a escribir ponderada con la entropia
	this->pathMatrizPonderada = pathMatrizPonderada;

    this->calcularEntropia();
    this->ponderarLocarPorGlobal(); //tambien persiste, despues hay que cambiarlo

}


void Ponderer::calcularEntropia(){

	this->matrizFreqLoc->abrir(); //abre la matriz en modo lextura

	this->contenedorParcialEntropia = trie->exportarDatosParaEntropia_INI();

	this->cantidadDocumentosEnLaColeccion = trie->obtenerCantidadDeDocumentosParseados();

	for(register unsigned int i=0; i<this->cantidadDocumentosEnLaColeccion; i++){

		std::list<TregistroArchivo*>* columna = matrizFreqLoc->obtenerColumnaMatriz();//el formato de la matriz arranca desde 1

		std::list<TregistroArchivo*>::iterator b = columna->begin();
		std::list<TregistroArchivo*>::iterator e = columna->end();

        while(b!=e){
			TregistroArchivo* auxReg = *b; //uso el id como indice del vector que contiene las entropias parciales

			TacumEntropia* auxEntropia = this->contenedorParcialEntropia->at(auxReg->fil -1);

			double freqLocalDivFreqGlobal = ((double)auxReg->freq)/((double)auxEntropia->infoTerm->ocurrenciasEnLaColeccion);

			auxEntropia->acumEntropia += (freqLocalDivFreqGlobal*(log2(freqLocalDivFreqGlobal)));

			b++;
		}
        //vacia la lista que contenai los datos de la comluna leida
		matrizFreqLoc->vaciar();

    }

    this->dividirTodoPorLog();

    matrizFreqLoc->cerrar();

}

void Ponderer::dividirTodoPorLog(){
    //ademas de dividir todo por log, tambien suma el 1

    for(register unsigned int i=0; i<this->contenedorParcialEntropia->size(); i++){
	   this->contenedorParcialEntropia->at(i)->acumEntropia = (this->contenedorParcialEntropia->at(i)->acumEntropia / (log2(cantidadDocumentosEnLaColeccion))) + 1;
	}


}

void Ponderer::ponderarLocarPorGlobal(){

	std::cout<<"PERSISTIENDO MATRIZ CON LA ENTROPIA CALCULADA"<<std::endl;

	//abriendo matriz de ponderacion locales
	matrizFreqLoc->abrir();

	matrizPonderada = new Persister(pathMatrizPonderada);
	matrizPonderada->escribirEncabezado(trie->obtenerCantidadDeDocumentosParseados(),trie->obtenerContadorId(),trie->obtenerCantidadDePalabrasIngresadas());

	std::list<TregistroArchivoF*>* registrosPonderados = new std::list<TregistroArchivoF*>;

	//recorro toda la matriz
	while(!matrizFreqLoc->hayData()){
		std::list<TregistroArchivo*>* dataCol = matrizFreqLoc->obtenerColumnaMatriz();

		std::list<TregistroArchivo*>::iterator b = dataCol->begin();
		std::list<TregistroArchivo*>::iterator e = dataCol->end();
		//recorriendo columnas de la matriz
		while(b!=e){
			TregistroArchivo* aux = *b;
			TregistroArchivoF* auxF = new TregistroArchivoF;

			double entropia = this->contenedorParcialEntropia->at(aux->fil - 1)->acumEntropia;
			double pesoLocal = log10(aux->freq + 1);
			double localPorGlobal = (pesoLocal*entropia);

			auxF->col = aux->col;
			auxF->fil = aux->fil;
			auxF->peso = localPorGlobal; //este seria el registro ya ponderado con la entropia

			registrosPonderados->push_back(auxF);
			b++;
		}
		matrizPonderada->persistirDatos(registrosPonderados);
		matrizFreqLoc->vaciar(); //vacio los registros de la columna leida

		//preparo la lista para poder ponderar una nueva columna
		while(registrosPonderados->empty()){
		        TregistroArchivoF* aux = registrosPonderados->back();
		        delete aux;
		        registrosPonderados->pop_back();
		}
		registrosPonderados->clear();
	}

	matrizFreqLoc->cerrar();
	matrizPonderada->cerrar();


}


