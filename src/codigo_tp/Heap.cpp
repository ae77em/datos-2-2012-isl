#include "Heap.h"

Heap::Heap(){
	this->contenedor = new vector<int*>;
}

Heap::~Heap()
{
    //dtor
}



bool Heap::estaVacio(){

		if(contenedor->size()>0){
			return false;
		}else{
			return true;
		}
}

void Heap::cargarElemento(int* nro) {

    contenedor->push_back(nro);

    controlarQueSeaUnHeapHaciaArriba(contenedor->size()-1);

}

	//se usa cuando un nuevo elemento es insertando en el heap, el mismo es insertando en el ultimo elemento y va siendo
	//subido hasta que el contenedor alcanza la propiedad de heap
void Heap::controlarQueSeaUnHeapHaciaArriba(int pos) {

		// 0 1 2 3 4 5 6  2n+1, 2n+2, n-1/2
		if(*contenedor->at(pos) < *contenedor->at((pos-1)/2)){
			intercambiar(pos,(pos-1)/2);
			controlarQueSeaUnHeapHaciaArriba((pos-1)/2);
		}

}

void Heap::intercambiar(int nivelBajo, int nivelAlto) {

		int* aux = contenedor->at(nivelBajo);
		contenedor->at(nivelBajo) = contenedor->at(nivelAlto);
		contenedor->at(nivelAlto)= aux;

}

int* Heap::obtenerRaiz() {
    return contenedor->at(0);
}


int Heap::obtenerCantidadDeElementos() {
		return contenedor->size();
}

	//simplemente accede directamenta a los elemento del heap, se usa en la etapa de pruebas
int* Heap::obtenerElemento(int i) {
		// TODO Auto-generated method stub
		return contenedor->at(i);
}

	//devuelve la raiz quitandola del arbol
int* Heap::quitarRaiz() {

		int* minimo = this->obtenerRaiz();

		contenedor->at(0) = contenedor->at(contenedor->size()-1);

		contenedor->pop_back();

		controlarQueSeaUnHeapHaciaAbajo(0);

		return minimo;
}

	//se usa cuando se insertar un elemento en la raiz y es el mismo debe ser hundido hasta que el arbol sea un heap
void Heap::controlarQueSeaUnHeapHaciaAbajo(int pos) {

		if( (contenedor->size() > pos*2 +1) && (*contenedor->at((pos*2) + 1) < *contenedor->at(pos)) ){
			intercambiar(pos,(pos*2) + 1);
			controlarQueSeaUnHeapHaciaAbajo((pos*2) + 1);
		}
		if( (contenedor->size() > pos*2 + 2) && (*contenedor->at((pos*2) + 2) < *contenedor->at(pos)) ){
			intercambiar(pos,(pos*2) + 2);
			controlarQueSeaUnHeapHaciaAbajo((pos*2) + 2);
		}

}

	//solamente se usa en la etapa de pruebas
void Heap::cargarElementoEnVector(int* nro) {
		contenedor->push_back(nro);
}

void Heap::mostrar(){

    for(int i=0;i<contenedor->size();i++){
        cout <<*contenedor->at(i)<<" ";
    }

}

