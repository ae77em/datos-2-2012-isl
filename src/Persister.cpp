#include "Persister.h"
#include <iostream>


Persister::Persister(std::string path){

	this->path = path;
    archivo.open(this->path.c_str(),std::fstream::out);
    contenedor = new std::list<TregistroArchivo*>;
    regAux=NULL;

}

void Persister::escribirEncabezado(int col,int fil, int cantTerminos){

	archivo<<"%%MatrixMarket matrix coordinate real general\n";
    archivo<<col<<" "<<fil<<" "<<cantTerminos<<endl;

}

Persister::~Persister(void){

   // archivo.close();
    delete contenedor;
    cout<<"PERSISTER DESTRUIDO"<<endl;
    //vaciar contenedor

}

void Persister::cerrar(){

    regAux=NULL;
	archivo.close();
	cout<<"PERSISTER CERRADO"<<endl;

}

void Persister::abrir(){
    archivo.open(this->path.c_str(),std::fstream::in);
}
//POR EL MOMENTO SE VA A HACER SECUENCIAL, MAS ADELANTE, SI ES NECESERAIO
//AGREGARE FUNCIONALIDAD PARA PODER LEER DE A COLUMNA
list<TregistroArchivo*>* Persister::obtenerColumnaMatriz(){

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
	    if(data->at(i)!=NULL){
            archivo<<columna<<" "<<(data->at(i)->id + 1)<<" "<<data->at(i)->ocurrenciasEnElDocActual<<std::endl;
	    }
    }
}

bool Persister::hayData(){
	return archivo.eof();
}

void Persister::vaciar(list<TregistroArchivo*>* l){
    //por algun motivo cuando libero lo que pedi altera los resultados, queda provisorio l->clear()
    /*while(l->empty()){
        TregistroArchivo* aux = l->back();
        delete aux;
        l->pop_back();
    }*/
    l->clear();
}
