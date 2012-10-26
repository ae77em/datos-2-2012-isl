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
        Persister(std::string,int col,int fil, int cantTerminos);
        ~Persister(void);
        void persistirDatos(std::vector<TnodoData*>*,unsigned int);
        list<TregistroArchivo*>* obtenerColumnaMatriz();
        void abrir();
        void cerrar();

        bool hayData();

	private:

        void bajarDatosADisco();

        TregistroArchivo* regAux; //almacenara el registro que se le cunado se cambie de columna
        std::fstream salida;
        std::list<TregistroArchivo*>* contenedor;
        std::string path;

};

#endif
