#ifndef __PERSISTER_H_
#define __PERSISTER_H_

#include <fstream>
#include <string>
#include <list>
#include "trie.h"

struct TregistroArchivo{
    int col;
    int fil;
    int freq;
};

class Persister {

	public:
        Persister(std::string);
        ~Persister();
        void recibirDatos(list<TnodoData*>*,unsigned int);

	private:

        void bajarDatosADisco();

        fstream salida;
        list<TregistroArchivo*>* contenedor;

};

#endif
