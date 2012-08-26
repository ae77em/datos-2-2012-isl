#ifndef _trie_H_
#define _trie_H_

#include <string>
#include <iostream>
#include "../Utilidades/Utilidades.h"
using namespace std;

struct TnodoData{

	unsigned ocurrenciasEnElDocActual;
	unsigned ocurrenciasEnLaColeccion;
	unsigned ocurrenciasEnDocDistintos;
    unsigned nroDeFila; //corresponde a cada palabra

};
struct TnodoTrie {

    char letra;
    TnodoTrie* hermano;
    TnodoTrie* hijo;
    TnodoData* infoArchivo;
    char flagParser;
    long int contadorDeFila;
};



class Trie {

private:

    TnodoTrie* RAIZ ;
    unsigned cantidadDeDocumentos; // son la cantidad de columnas de la matriz
    Utilidades utilidades;

public:

    Trie();
    ~Trie();
    void inicializarNodo(TnodoTrie*);
    void insertarPalabra(std::string,int*);
    bool buscarPalabra(string,unsigned&);
    bool buscarPalabra(string);
    TnodoTrie* insertarPalabra(std::string,TnodoTrie*,int*);
    TnodoTrie* buscarLugar(char,TnodoTrie*,short int*);
    TnodoTrie* getNodo();
    bool buscarPalabra(string,TnodoTrie*,unsigned&);
  //  bool buscarPalabra(string,TnodoTrie*);
    TnodoTrie* buscarLetra(char,TnodoTrie*);
    void destruirArbol(TnodoTrie*,int*);
    void buscarPalabrasDeLaParseada_INI(void);
    void buscarPalabrasParaGuardar_INI(string &);
    void buscarPalabrasParaGuardar(TnodoTrie*,string,string,string&);
    void buscarPalabrasDeLaParseada(TnodoTrie*,string,string,bool);
    void destruirArbol_INI(void);
    void incrementarCantidadDeDocumentos(){ cantidadDeDocumentos++; };
    void setCantidadDeDocumentos(){ cantidadDeDocumentos = 0; }; //deja esta variable en estado valido


};
#endif
