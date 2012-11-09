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

struct TregistroArchivoF {
    unsigned int col;
    unsigned int fil;
    double peso;
};

class Persister {

	public:

		Persister();
        Persister(std::string);
        ~Persister(void);

        void escribirEncabezado(int col,int fil, int cantTerminos);
//se usa en la matriz con ponderacion parciales, son locales
        void persistirDatos(std::vector<TnodoData*>*,unsigned int);

//se usa en la matriz final
        void persistirDatos(std::list<TregistroArchivoF*>*);

        std::list<TregistroArchivo*>* obtenerColumnaMatriz();

        void abrir();
        void cerrar();

        bool hayData();
        void vaciar(std::list<TregistroArchivo*>*);
        void vaciar();


        void irAlComienzo();

        void parserLSI(int);

        std::string obtenerPath();


	private:

        std::vector<std::vector<double>*>* generadorContenedorMatriz(int);

        TregistroArchivo* regAux; //almacenara el registro que se lee del archivo
        std::fstream archivo;
        std::list<TregistroArchivo*>* contenedor;
        std::string path;

};

#endif
