#include "Persister.h"

Persister::Persister(std::string path){

	this->path = path;
    salida.open(this->path.c_str(),std::fstream::out);
    contenedor = new std::list<TregistroArchivo*>;
    regAux=NULL;

    cout<<"PERSISTER CREADO"<<endl;
}



Persister::Persister(std::string pathMatriz,int col,int fil, int cantTerminos){

	salida.open(pathMatriz.c_str(),std::fstream::out);
	//inicializo cabecera del archivo
    salida<<"%%MatrixMarket matrix coordinate real general\n";
    salida<<col<<" "<<fil<<" "<<cantTerminos<<endl;
    }

Persister::~Persister(void){

   // salida.close();
    cout<<"PERSISTER DESTRUIDO"<<endl;
    //vaciar contenedor

}

void Persister::cerrar(){

	salida.close();
	cout<<"PERSISTER DESTRUIDO"<<endl;

}

void Persister::abrir(){

	salida.open(path.c_str(),std::fstream::in);

}
//POR EL MOMENTO SE VA A HACER SECUENCIAL, MAS ADELANTE, SI ES NECESERAIO
//AGREGARE FUNCIONALIDAD PARA PODER LEER DE A COLUMNA
list<TregistroArchivo*>* Persister::obtenerColumnaMatriz(){


	if(regAux==NULL){//solo en la primer lectura pasa esto
		TregistroArchivo* regAux = new TregistroArchivo;
		salida >> regAux->col;
		salida >> regAux->fil;
		salida >> regAux->freq;


	}else{
	}

	int columna = regAux->col;

	while(columna==regAux->col && !salida.eof()){

		this->contenedor->push_back(regAux);//

		if(!salida.eof() && columna==regAux->col){
			TregistroArchivo* regAux = new TregistroArchivo;
			salida >> regAux->col;
			salida >> regAux->fil;
			salida >> regAux->freq;
		}
	}

	return this->contenedor;
}


void Persister::persistirDatos(std::vector<TnodoData*>* data, unsigned int columna){

    std::cout<<"iniciando persistencia"<<std::endl;
    std::cout<<"tamanio: "<<data->size()<<std::endl;

	for(register int i=0; i< data->size() ; i++){
	    if(data->at(i)){
            salida<<columna<<" "<<(data->at(i)->id + 1)<<" "<<data->at(i)->ocurrenciasEnElDocActual<<std::endl;
	    }
    }
}

bool Persister::hayData(){

	return salida.eof();

}
