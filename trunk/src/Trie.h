#ifndef _TRIE_H_
#define _TRIE_H_

#define FINAL_DE_PALABRA 0

#include <string>
#include <iostream>
#include <fstream>
#include <list>
#include <vector>

struct TnodoTerminoId {
    std::string palabra;
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
    char flagParser;
};

struct TnodoPrincipalTrie {
    int cantidadTotalDePalabrasEnLaColeccion;//lleva la cuenta de las palabras ingresadas
    int contadorDeId_s; //lleva la cuenta de palabras diferentes ingresadas
    int cantidadDeDocumentoParseados;
    TnodoTrie* padreSupremo;
    std::vector<TnodoTerminoId*>* contenedor; // se usa en la persistencia del lexico
    std::vector<TnodoData*>* contenedorParcial;
    std::vector<TacumEntropia*>* contenedorEntropia;
};

class Trie {
	private:
		TnodoPrincipalTrie* RAIZ ;
		char buffer [33];

		void inicializarRaiz();
		void inicializarNodo(TnodoTrie*);
		void insertarPalabra(std::string,TnodoTrie*);
		void recorrer(TnodoTrie*,std::string,std::ofstream*);
		bool buscarPalabra(std::string,TnodoTrie*);
		TnodoTrie* buscarLetra(char,TnodoTrie*);
		void exportarPalabrasContenedor(TnodoTrie*, std::vector<TnodoTerminoId*>*, std::string);
        void eliminarPalabra(std::string,TnodoTrie);
        void exportarDatosParaEntropia(std::vector<TacumEntropia*>*,TnodoTrie*);
        void destruirArbol(TnodoTrie*,int*);
        void persistirPalabras(TnodoTrie*, std::ofstream*, std::ofstream*, int*, std::string);
        void buscarPalabrasDelDocParseado(TnodoTrie*, std::vector<TnodoData*>*);

	public:
		Trie ();
		~Trie ();

		void insertarPalabra(std::string);
		void recorrer();

		void aumentarCantidadDePalabrasEnLaColeccion(void);
		void aumentarCantidadDeDocParseados(void);

		bool buscarPalabra(std::string);
		std::vector<TnodoData*>* buscarPalabrasDelDocParseado_INI(void);

		int obtenerCantidadDePalabrasIngresadas();
		int obtenerCantidadDeDocumentosParseados();
		int obtenerContadorId();
		void incrementarContadorId();

		std::vector<TnodoTerminoId*>* exportarPalabrasContenedor_INI();

		void persistirPalabras_INI(std::ofstream*, std::ofstream*);
		void persistirPalabrasContenedor(std::ofstream*);

		void destruirArbol_INI(void);
		//////NUEVOS al 25/10
		std::vector<TacumEntropia*>* exportarDatosParaEntropia_INI();
		void vaciarContenedorParcial(); //no se hacen delete, solo se limpia el contenedor
		void inicializarFrecuenciasLocales();
        void vaciarContenedores();

        //////NUEVOS al 14/11 eliminacion de palabras en el trie
        void eliminarPalabra_INI(std::string);
        void actualizarIdsLuegoDeFiltradoDeTerminos();

};
#endif
