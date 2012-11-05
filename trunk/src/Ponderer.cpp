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
	this->nombreMatrizFinal="";

}

Ponderer::~Ponderer() {
	// TODO Auto-generated destructor stub
}


void Ponderer::ponderar(Trie* unTrie,Persister* unP, std::string nombreIndice){

	trie = unTrie;
	matrizFreqLoc = unP;

	//parseo nombre indice
	this->nombreMatrizFinal = nombreIndice.substr(nombreIndice.find_last_of(47));

	matrizFreqLoc->abrir();

    this->calcularEntropia();
    this->ponderarLocarPorGlobal(); //tambien persiste, despues hay que cambiarlo

}


void Ponderer::calcularEntropia(){

	this->contenedorParcialEntropia = trie->exportarDatosParaEntropia_INI();

	this->cantidadDocumentosEnLaColeccion = trie->obtenerCantidadDeDocumentosParseados();

	for(register unsigned int i=0; i<this->cantidadDocumentosEnLaColeccion; i++){

		std::list<TregistroArchivo*>* columna = matrizFreqLoc->obtenerColumnaMatriz();//el formato de la matriz arrance desde 1

		std::list<TregistroArchivo*>::iterator b = columna->begin();
		std::list<TregistroArchivo*>::iterator e = columna->end();

        while(b!=e){
			TregistroArchivo* auxReg = *b; //uso el id como indice del vector que contiene las entropias parciales

			TacumEntropia* auxEntropia = this->contenedorParcialEntropia->at(auxReg->fil -1);

			double localDivGlobal = ((double)auxReg->freq)/((double)auxEntropia->infoTerm->ocurrenciasEnLaColeccion);

			auxEntropia->acumEntropia += (localDivGlobal*(log2(localDivGlobal)));

			b++;
		}
        //vacia la lista que contenai los datos de la comluna leida
		matrizFreqLoc->vaciar();

    }

    this->dividirTodoPorLog();

    matrizFreqLoc->cerrar();

}

void Ponderer::dividirTodoPorLog(){

    for(register unsigned int i=0; i<this->contenedorParcialEntropia->size(); i++){
	   this->contenedorParcialEntropia->at(i)->acumEntropia = this->contenedorParcialEntropia->at(i)->acumEntropia / (log2(cantidadDocumentosEnLaColeccion));
	}
}

void Ponderer::ponderarLocarPorGlobal(){

	std::cout<<"PERSISTIENDO MATRIZ CON LA ENTROPIA CALCULADA"<<std::endl;

	std::ofstream matrizPonderada;

	std::string nombreMatrizFinal("indices/");
	nombreMatrizFinal += this->nombreMatrizFinal;

	matrizPonderada.open(nombreMatrizFinal.c_str());
	//inicializo cabecera de matriz MM
	matrizPonderada<<"%%MatrixMarket matrix coordinate real general"<<std::endl;
	matrizPonderada<<trie->obtenerCantidadDeDocumentosParseados()<<" "<<trie->obtenerContadorId()<<" "<<trie->obtenerCantidadDePalabrasIngresadas()<<std::endl;

    //abriendo matriz de ponderacion locales
	matrizFreqLoc->abrir();

	//recorro toda la matriz
	while(!matrizFreqLoc->hayData()){
		std::list<TregistroArchivo*>* dataCol = matrizFreqLoc->obtenerColumnaMatriz();

		std::list<TregistroArchivo*>::iterator b = dataCol->begin();
		std::list<TregistroArchivo*>::iterator e = dataCol->end();
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
	matrizFreqLoc->cerrar();
//lo dejo listo para calcular la data de la matriz por oraciones
	inicializarPonderer();
}


void Ponderer::inicializarPonderer(){

	//lo hice asi no mas, despues veo donde hay que aplicar algun delete

	contenedorParcialEntropia = NULL;
	cantidadDocumentosEnLaColeccion = 0;
	this->matrizFreqLoc=NULL;
	this->trie=NULL;
	this->matrizPonderada=NULL;
	this->nombreMatrizFinal="";
}
