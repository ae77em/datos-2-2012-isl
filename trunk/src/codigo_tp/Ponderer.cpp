#include "Ponderer.h"
#include "Persister.h"
#include <math.h>
#include <fstream>
#include <iostream>


Ponderer::Ponderer(Trie* unTrie,Persister* unP) {

	this->matrizFreqLoc=unP;
	this->trie=unTrie;
	this->matrizPonderada=NULL;

	unP->abrir();

}

Ponderer::~Ponderer() {
	// TODO Auto-generated destructor stub
}


void Ponderer::ponderar(){

    this->calcularEntropia();
    cout<<"APLICANDO FUNCION LOCAL X GLOBAL"<<endl;
    this->ponderarLocarPorGlobal();

}

void Ponderer::calcularEntropia(){

	this->contenedorParcialEntropia = trie->exportarDatosParaEntropia_INI();
	this->cantidadDocumentosEnLaColeccion = trie->obtenerCantidadDeDocumentosParseados();

	for(register unsigned int i=0; i<this->cantidadDocumentosEnLaColeccion; i++){

		list<TregistroArchivo*>* columna = matrizFreqLoc->obtenerColumnaMatriz();//el formato de la matriz arrance desde 1
        cout<<"LEIDA: "<<i+1<<endl;

		list<TregistroArchivo*>::iterator b = columna->begin();
		list<TregistroArchivo*>::iterator e = columna->end();

        while(b!=e){
			TregistroArchivo* auxReg = *b; //uso el id como indice del vector que contiene las entropias parciales

			TacumEntropia* auxEntropia = this->contenedorParcialEntropia->at(auxReg->fil -1);

			double localDivGlobal = ((double)auxReg->freq)/((double)auxEntropia->infoTerm->ocurrenciasEnLaColeccion);

			auxEntropia->acumEntropia = auxEntropia->acumEntropia + (localDivGlobal*(log(localDivGlobal)/log(2)));

			b++;
		}
		matrizFreqLoc->vaciar(columna);
    }

    this->dividirTodoPorLog();
    matrizFreqLoc->cerrar();

   cout<<"mostrando eotroiapo"<<endl<<endl;
    for(register int i=0;i<this->contenedorParcialEntropia->size();i++){
        cout<<this->contenedorParcialEntropia->at(i)->acumEntropia<<endl;
    }
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
        cout<<"PASE"<<endl;

		list<TregistroArchivo*>::iterator b = dataCol->begin();
		list<TregistroArchivo*>::iterator e = dataCol->end();
		//recorriendo columnas de la matriz
		while(b!=e){
			TregistroArchivo* aux = *b;

			double entropia = this->contenedorParcialEntropia->at(aux->fil - 1)->acumEntropia;
			double pesoLocal = log(aux->freq + 1);
            cout<<"MULTIPLICANDO: "<<entropia<<" * "<<pesoLocal<<endl;

			double localPorGlobal = (entropia*pesoLocal);
			matrizPonderada<<aux->col<<" "<<aux->fil<<" "<<localPorGlobal<<std::endl;

			b++;
		}
		matrizFreqLoc->vaciar(dataCol);
	}

	matrizPonderada.close();
}

