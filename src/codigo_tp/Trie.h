#ifndef _TRIE_H_
#define _TRIE_H_

#define FINAL_DE_PALABRA 0

#include <string>
#include <iostream>
#include <fstream>
#include <list>
#include <vector>

using namespace std;

struct TnodoTerminoId {
    string palabra;
    int* id;
};

struct TnodoData {
    unsigned int ocurrenciasEnElDocActual;
    unsigned int ocurrenciasEnLaColeccion;
    int id;
};

struct TacumEntropia{
	TnodoData* infoTerm;
	double acumEntropia;
};

struct TnodoTrie {
    char letra;
    TnodoTrie* hermano;
    TnodoTrie* hijo;
    TnodoData* infoArchivo;
    int flagParser;
};

struct TnodoPrincipalTrie {
    int cantidadTotalDePalabrasEnLaColeccion;//lleva la cuenta de las palabras ingresadas
    int contadorDeId_s; //lleva la cuenta de palabras diferentes ingresadas
    int cantidadDeDocumentoParseados;
    TnodoTrie* hijo;
    fstream log;
    vector<TnodoTerminoId*>* contenedor; // se usa en la persistencia del lexico
    vector<TnodoData*>* contenedorParcial;
    vector<TacumEntropia*>* contenedorEntropia;
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
		void aumentarCantidadDeDocParseados(void);

		bool buscarPalabra(string);
		bool buscarPalabra(string,TnodoTrie*);
		TnodoTrie* buscarLetra(char,TnodoTrie*);

		vector<TnodoData*>* buscarPalabrasDelDocParseado_INI(void);
		void buscarPalabrasDelDocParseado(TnodoTrie*,vector<TnodoData*>*);

		int obtenerCantidadDePalabrasIngresadas();
		int obtenerCantidadDeDocumentosParseados();
		int obtenerContadorId();
		void incrementarContadorId();

		vector<TnodoTerminoId*>* exportarPalabrasContenedor_INI();
		void exportarPalabrasContenedor(TnodoTrie*,vector<TnodoTerminoId*>*,string);

		void persistirPalabras_INI(fstream*);
		void persistirPalabras(TnodoTrie*,fstream*,string);
		void persistirPalabrasContenedor(fstream*);

		void eliminarStopWord_INI(string);
		void eliminarStoprWord(TnodoTrie*,string);

		void quitarTermindoDelContenedor(int);
		void actualizarIds(int);

		void vaciarContenedorParcial();
		void inicializarFrecuenciasLocales();

		void destruirArbol(TnodoTrie*,int*);
		void destruirArbol_INI(void);
		//////NUEVOS al 25/10
		vector<TacumEntropia*>* exportarDatosParaEntropia_INI();
		void exportarDatosParaEntropia(vector<TacumEntropia*>*,TnodoTrie*);
};
#endif
