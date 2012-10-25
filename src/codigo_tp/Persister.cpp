#include "Persister.h"

Persister::Persister(std::string path){

    salida.open(path.c_str(),std::fstream::out);
    //inicializo cabecera del archivo
    salida<<"%%MatrixMarket matrix coordinate real general\n";
    //se debe dejar un espacio en blanco para luego insertar la cantidad de col, fil e indices
    //ese debe ser el formato respetado para que la libreria pueda andar
    salida<<"                         \n";

    contenedor = new std::list<TregistroArchivo*>;
    regAux=NULL;

    cout<<"PERSISTER CREADO"<<endl;
}

Persister::~Persister(void){

   // salida.close();
    cout<<"PERSISTER DESTRUIDO"<<endl;
    //vaciar contenedor

}

void Persister::destruir(){

	salida.close();
	cout<<"PERSISTER DESTRUIDO"<<endl;

}

void Persister::abrir(std::string path){

	salida.open(path.c_str(),std::fstream::in);

}
//POR EL MOMENTO SE VA A HACER SECUENCIAL, MAS ADELANTE, SI ES NECESERAIO
//AGREGARE FUNCIONALIDAD PARA PODER LEER DE A COLUMNA
list<TregistroArchivo*>* Persister::obtenerColumnaMatriz(unsigned int columna){


	if(regAux==NULL){//solo en la primer lectura pasa esto
		TregistroArchivo* regAux = new TregistroArchivo;

		salida >> regAux->col;
		salida >> regAux->fil;
		salida >> regAux->freq;
		this->contenedor->push_back(regAux);//

	}else{
		this->contenedor->push_back(this->regAux);//guardo el que me quedo almacenado de la ultima vez

	}


	while(columna==regAux->col){
		TregistroArchivo* reg = new TregistroArchivo;

		salida >> reg->col;
		salida >> reg->fil;
		salida >> reg->freq;
		this->contenedor->push_back(reg);

	}

	return this->contenedor;
}


void Persister::persistirDatos(std::vector<TnodoData*>* data, unsigned int columna){

	for(register int i=0; i< data->size() ; i++){
									//sumo uno porque los id arrancar desde 0, y las filas desde 1
         salida<<columna<<" "<<(data->at(i)->id + 1)<<" "<<data->at(i)->ocurrenciasEnElDocActual<<std::endl;
    }
}
