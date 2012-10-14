#ifndef Heap_H
#define Heap_H

#include <iostream>
#include <vector>

using namespace std;

class Heap
{
    public:
        Heap();
        virtual ~Heap();
        bool estaVacio();
        void cargarElemento(int*);
        int* obtenerRaiz();
        int obtenerCantidadDeElementos();
        int* obtenerElemento(int);
        int* quitarRaiz();
        void cargarElementoEnVector(int*);
        void mostrar();



    private:
        void controlarQueSeaUnHeapHaciaArriba(int);
        void intercambiar(int, int);
        void controlarQueSeaUnHeapHaciaAbajo(int);

        vector<int*>* contenedor;
};

#endif // HEAP_H
