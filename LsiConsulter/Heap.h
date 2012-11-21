#ifndef Heap_H
#define Heap_H

#include <iostream>
#include <vector>
#include "Consulter.h"

struct TnodoHeapDocPuntaje{
	double puntaje;
	unsigned int doc;
};

class Heap
{
    public:

        Heap(){
        	this->contenedor = new std::vector<TnodoHeapDocPuntaje>;

        };

        virtual ~Heap(){

        };

        bool estaVacio(){

            return (contenedor->size() > 0) ? false:true;

        };

        void cargarElemento( TnodoHeapDocPuntaje docPuntuado){
        	contenedor->push_back(docPuntuado);

            controlarQueSeaUnHeapHaciaArriba(contenedor->size()-1);

        };

        TnodoHeapDocPuntaje obtenerRaiz(){
            return contenedor->front();
        };

        unsigned int obtenerCantidadDeElementos(){
            return contenedor->size();
        };

        TnodoHeapDocPuntaje obtenerElemento(int i){
            // TODO Auto-generated method stub
            return contenedor->at(i);
        };

        TnodoHeapDocPuntaje obtenerMaximo(){

        	TnodoHeapDocPuntaje minimo = this->obtenerRaiz();

            contenedor->at(0) = contenedor->at(contenedor->size()-1);

            contenedor->pop_back();

            controlarQueSeaUnHeapHaciaAbajo(0);

            return minimo;
        };

        void cargarElementoEnVector(TnodoHeapDocPuntaje elemento){
            contenedor->push_back(elemento);
        };

        void mostrar(){
            for(unsigned int i=0;i<contenedor->size();i++){
            	std::cout <<contenedor->at(i).puntaje<<" ";
            }
            std::cout<<std::endl<<std::endl;
        };

    private:

        void controlarQueSeaUnHeapHaciaArriba(int pos){
        // 0 1 2 3 4 5 6  2n+1, 2n+2, n-1/2
        	if(contenedor->size()>1){
				if(contenedor->at(pos).puntaje > contenedor->at((pos-1)/2).puntaje){
					intercambiar(pos,(pos-1)/2);
					controlarQueSeaUnHeapHaciaArriba((pos-1)/2);
				}
        	}
        };

        void intercambiar(int nivelBajo, int nivelAlto){
        	TnodoHeapDocPuntaje aux = contenedor->at(nivelBajo);
            contenedor->at(nivelBajo) = contenedor->at(nivelAlto);
            contenedor->at(nivelAlto)= aux;
        };

        void controlarQueSeaUnHeapHaciaAbajo(unsigned int pos){

            if( (contenedor->size() > (pos*2 +1) ) && (contenedor->at((pos*2) + 1).puntaje > contenedor->at(pos).puntaje) ){
                intercambiar(pos,(pos*2) + 1);
                controlarQueSeaUnHeapHaciaAbajo((pos*2) + 1);
            }
            if( (contenedor->size() > pos*2 + 2) && (contenedor->at((pos*2) + 2).puntaje > contenedor->at(pos).puntaje) ){
                intercambiar(pos,(pos*2) + 2);
                controlarQueSeaUnHeapHaciaAbajo((pos*2) + 2);
            }

        };

        //variables
        std::vector<TnodoHeapDocPuntaje>* contenedor;
};

#endif // HEAP_H
