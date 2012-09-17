#ifndef _trie_H_
#define _trie_H_

#define FINAL_DE_PALABRA 0

#include <string>
#include <iostream>
#include <fstream>
#include <list>

using namespace std;

struct TnodoData{

    int ocurrenciasEnElDocActual;
    int id;
};

struct TnodoTrie {

    char letra;
    TnodoTrie* hermano;
    TnodoTrie* hijo;
    TnodoData* infoArchivo;
    char flagParser;
};

struct TnodoPrincipalTrie{
    int cantidadTotalDePalabrasEnLaColeccion;//lleva la cuenta de las palabras ingresadas
    int contadorDeId_s; //lleva la cuenta de palabras diferentes ingresadas
    int cantidadDeDocumentoParseados;
    TnodoTrie* hijo;
    fstream log;

};

class Trie {

private:

    TnodoPrincipalTrie* RAIZ ;

public:

    Trie ();
    void inicializarRaiz();
    void inicializarNodo(TnodoTrie*);

    void insertarPalabraEnRaiz(std::string,int*);
    TnodoTrie* insertarPalabra(std::string,TnodoTrie*,int*);
    TnodoTrie* buscarLugar(char,TnodoTrie*,short int*);

    void aumentarCantidadDePalabrasEnLaColeccion(void);

    bool buscarPalabra(string);
    bool buscarPalabra(string,TnodoTrie*);
    TnodoTrie* buscarLetra(char,TnodoTrie*);

    void destruirArbol(TnodoTrie*,int*);
    void destruirArbol_INI(void);

    list<TnodoData*>* buscarPalabrasDelDocParseado_INI(void);
    void buscarPalabrasDelDocParseado(TnodoTrie*,list<TnodoData*>*);

    void exportarPalabras_INI(fstream*);
    void exportarPalabras(TnodoTrie*,fstream*,string);

    int obternerCantidadDePalabrasIngresadas();
    int obtenerContadorId();
    void incrementarContadorId();

};
#endif
