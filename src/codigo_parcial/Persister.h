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
        ~Persister(void);

        void escribirEncabezado(int col,int fil, int cantTerminos);

        void persistirDatos(std::vector<TnodoData*>*,unsigned int);
        list<TregistroArchivo*>* obtenerColumnaMatriz();

        void abrir();
        void cerrar();

        bool hayData();
        void vaciar(list<TregistroArchivo*>*);



	private:

        TregistroArchivo* regAux; //almacenara el registro que se lee del archivo

        std::fstream archivo;

        std::list<TregistroArchivo*>* contenedor;

        std::string path;


};

#endif
