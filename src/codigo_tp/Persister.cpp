#include "Persister.h"

Persister::Persister(std::string path){

    salida.open(path.c_str(),fstream::out);
    //inicializo cabecera del archivo
    salida<<"%%MatrixMarket matrix coordinate real general"<<endl;
    //se debe dejar un espacio en blanco para luego insertar la cantidad de col, fil e indices
    //ese debe ser el formato respetado para que la libreria pueda andar
    salida<<"                         "<<endl;

    contenedor = new list<TregistroArchivo*>;

}

Persister::~Persister(){

    salida.close();
    //vaciar contenedor

}

void Persister::recibirDatos(list<TnodoData*>* data, unsigned int columna){

    list<TnodoData*>::iterator b = data->begin();
    list<TnodoData*>::iterator e = data->end();
    while(b!=e){
        TnodoData* aux = *b;
        salida<<columna<<" "<<aux->id<<" "<<aux->ocurrenciasEnElDocActual<<endl;
        b++;
    }
}
