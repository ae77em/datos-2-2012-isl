#include "Persister.h"

Persister::Persister(std::string path){

    salida.open(path.c_str(),std::fstream::out);
    //inicializo cabecera del archivo
    salida<<"%%MatrixMarket matrix coordinate real general\n";
    //se debe dejar un espacio en blanco para luego insertar la cantidad de col, fil e indices
    //ese debe ser el formato respetado para que la libreria pueda andar
    salida<<"                         \n";

    //contenedor = new std::list<TregistroArchivo*>;
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


void Persister::persistirDatos(std::vector<TnodoData*>* data, unsigned int columna){

	for(register int i=0; i< data->size() ; i++){
									//sumo uno porque los id arrancar desde 0, y las filas desde 1
         salida<<columna<<" "<<(data->at(i)->id + 1)<<" "<<data->at(i)->ocurrenciasEnElDocActual<<std::endl;
    }
}
