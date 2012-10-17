#ifndef Heap_H
#define Heap_H

#include <iostream>
#include <vector>

template <class T>
class Heap
{
    public:

        Heap(){
            this->contenedor = new std::vector<T>;
        };

        virtual ~Heap(){

        };

        bool estaVacio(){

            return (contenedor->size() > 0) ? false:true;

        };

        void cargarElemento( T nro){

            contenedor->push_back(nro);

            controlarQueSeaUnHeapHaciaArriba(contenedor->size()-1);

        };

        T obtenerRaiz(){
            return contenedor->front();
        };

        T obtenerCantidadDeElementos(){
            return contenedor->size();
        };

        T obtenerElemento(int i){
            // TODO Auto-generated method stub
            return contenedor->at(i);
        };

        T quitarRaiz(){

            T minimo = this->obtenerRaiz();

            contenedor->at(0) = contenedor->at(contenedor->size()-1);

            contenedor->pop_back();

            controlarQueSeaUnHeapHaciaAbajo(0);

            return minimo;
        };

        void cargarElementoEnVector(T elemento){
            contenedor->push_back(elemento);
        };

        void mostrar(){
            for(int i=0;i<contenedor->size();i++){
            std::cout <<contenedor->at(i)<<" ";
            }
        };

    private:

        void controlarQueSeaUnHeapHaciaArriba(int pos){
        // 0 1 2 3 4 5 6  2n+1, 2n+2, n-1/2
            if(contenedor->at(pos) < contenedor->at((pos-1)/2)){
                intercambiar(pos,(pos-1)/2);
                controlarQueSeaUnHeapHaciaArriba((pos-1)/2);
            }
        };

        void intercambiar(int nivelBajo, int nivelAlto){

            T aux = contenedor->at(nivelBajo);
            contenedor->at(nivelBajo) = contenedor->at(nivelAlto);
            contenedor->at(nivelAlto)= aux;

        };

        void controlarQueSeaUnHeapHaciaAbajo(int pos){

            if( (contenedor->size() > pos*2 +1) && (contenedor->at((pos*2) + 1) < contenedor->at(pos)) ){
                intercambiar(pos,(pos*2) + 1);
                controlarQueSeaUnHeapHaciaAbajo((pos*2) + 1);
            }
            if( (contenedor->size() > pos*2 + 2) && (contenedor->at((pos*2) + 2) < contenedor->at(pos)) ){
                intercambiar(pos,(pos*2) + 2);
                controlarQueSeaUnHeapHaciaAbajo((pos*2) + 2);
            }

        };

        //variables
        std::vector<T>* contenedor;
};

#endif // HEAP_H
