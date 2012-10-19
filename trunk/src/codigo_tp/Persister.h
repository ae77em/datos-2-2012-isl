#ifndef __PERSISTER_H_
#define __PERSISTER_H_

#include <fstream>
#include <string>
#include <list>
#include "Trie.h"

struct TregistroArchivo{
    int col;
    int fil;
    int freq;
};

class Persister {

	public:
		Persister();
        Persister(std::string);
        ~Persister();
        void recibirDatos(std::list<TnodoData*>*,unsigned int);

	private:

        void bajarDatosADisco();

        std::fstream salida;
        std::list<TregistroArchivo*>* contenedor;

};

#endif
