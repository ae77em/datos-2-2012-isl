#include "Persister.h"
#include <iostream>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>


Persister::Persister(std::string path){

	this->path = path;
    archivo.open(this->path.c_str(),std::fstream::out);
    contenedor = new std::list<TregistroArchivo*>;
    regAux=NULL;

}

void Persister::escribirEncabezado(int col,int fil, int cantTerminos){

	archivo<<"%%MatrixMarket matrix coordinate real general\n";
    archivo<<col<<" "<<fil<<" "<<cantTerminos<<std::endl;

}

Persister::~Persister(void){

   // archivo.close();
    delete contenedor;
    std::cout<<"PERSISTER DESTRUIDO"<<std::endl;
    //vaciar contenedor

	if (regAux != NULL) {
		delete regAux;
	}
}

void Persister::cerrar(){

    regAux=NULL;
	archivo.close();
	std::cout<<"PERSISTER CERRADO"<<std::endl;

}

void Persister::abrir(){
    archivo.open(this->path.c_str(),std::fstream::in);
}
//POR EL MOMENTO SE VA A HACER SECUENCIAL, MAS ADELANTE, SI ES NECESERAIO
//AGREGARE FUNCIONALIDAD PARA PODER LEER DE A COLUMNA
std::list<TregistroArchivo*>* Persister::obtenerColumnaMatriz(){

	if(regAux==NULL){//solo en la primer lectura pasa esto
		regAux = new TregistroArchivo;
		archivo >> regAux->col;
		archivo >> regAux->fil;
		archivo >> regAux->freq;

	}else{
       // cout<<endl<<"ENTRE con col: "<<regAux->col<<" fil "<<regAux->fil<<"freq "<<regAux->freq<<endl;
	}

    int columna=regAux->col;

	while( ( regAux->col==columna ) && (!archivo.eof() )){
        this->contenedor->push_back(regAux);//

		if(!archivo.eof() && columna==regAux->col){

            regAux = new TregistroArchivo;
			archivo >> regAux->col;
			archivo >> regAux->fil;
			archivo >> regAux->freq;
        }
	}

	return this->contenedor;
}


void Persister::persistirDatos(std::vector<TnodoData*>* data, unsigned int columna){

	for(register unsigned int i=0; i< data->size() ; i++){
	    if(data->at(i)){
            archivo<<columna<<" "<<(data->at(i)->id + 1)<<" "<<data->at(i)->ocurrenciasEnElDocActual<<std::endl;
	    }
    }
}

void Persister::persistirDatos(std::list<TregistroArchivoF*>* data){

	std::list<TregistroArchivoF*>::iterator iterador;

	for (iterador = data->begin(); iterador != data->end(); iterador++){
        archivo<<(*iterador)->col<<" "<<(*iterador)->fil<<" "<<(*iterador)->peso<<std::endl;
    }
}


bool Persister::hayData(){
	return archivo.eof();
}

void Persister::vaciar(std::list<TregistroArchivo*>* l){

    //por algun motivo cuando libero lo que pedi altera los resultados, queda provisorio l->clear()
    /*while(l->empty()){
        TregistroArchivo* aux = l->back();
        delete aux;
        l->pop_back();
    }*/
    l->clear();
}

void Persister::irAlComienzo(){

    archivo.seekp(std::ios_base::beg);

}

std::vector<std::vector<double>*>* generadorContenedorMatriz(int cantCol){

    std::vector<std::vector<double>*>* matriz = new std::vector<std::vector<double>*>;

    for(int i=0;i<cantCol;i++){
        matriz->push_back(new std::vector<double>);
    }

    return matriz;
}

void Persister::parserLSI(int cantidadDeDocumetos){

    int cantCol=cantidadDeDocumetos;

    std::vector<std::vector<double>*>* bufferMatriz = generadorContenedorMatriz(cantCol);

    std::ifstream matriz;
    matriz.open("salidaGensim.txt");

    char letra;
    int col=0;
    std:: string nro="";
    int cantidadDeDocumentos=3;

    double valor=0;

    while(!matriz.eof()){

        letra = matriz.get(); //si es un nro o un punto

        if((letra <= 57 && letra >= 48) || (letra == 46) || (letra==45)){
            while( (letra <= 57 && letra >= 48) || (letra == 46) || (letra==45)){
                nro += letra;
                letra = matriz.get(); //si es un nro o un punto
            }
            valor = atof(nro.c_str());
            bufferMatriz->at(col)->push_back(valor);

            col++;
            if(col == cantidadDeDocumentos){
                col=0;
            }
            nro="";
        }
    }

    /*cout<<"PROBANDO VALORES: "<<endl;
    for(int i=0;i<bufferMatriz->size();i++){
        for(int j=0; j<cantidadDeDocumentos;j++){
            cout<<"D"<<j<<": "<<bufferMatriz->at(i)->at(j)<<" ";
        }
        cout<<endl;
    }*/

    std::ofstream matrizSinComasNiCorchetes;
    matrizSinComasNiCorchetes.open("matrizFinal.txt");

    for(int unsigned i=0;i<bufferMatriz->size();i++){
        for(int j=0; j<cantidadDeDocumentos;j++){
            matrizSinComasNiCorchetes<<bufferMatriz->at(i)->at(j)<<" ";
        }
        matrizSinComasNiCorchetes<<std::endl;
    }

    matriz.close();
    matrizSinComasNiCorchetes.close();

}
std::vector<std::vector<double>*>* Persister::generadorContenedorMatriz(int cantCol){

    std::vector<std::vector<double>*>* matriz = new std::vector<std::vector<double>*>;

    for(int i=0;i<cantCol;i++){
        matriz->push_back(new std::vector<double>);
    }

    return matriz;
}
