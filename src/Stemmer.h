#ifndef __STEMMER_H_
#define __STEMMER_H_

#include <cstdio>
#include <string>
#include <iostream>

class Stemmer {
private:
	std::string b;       /* buffer para la palabra a procesar */
	int k,k0,j;     /* offset del string */
	std::string s;  /* almacena la palabra a procesar al inicio, y almacena la
	 	 	 	 	   misma procesada. Es la variable de retorno*/
	int i_max;		/* tamanio maximo del offset. Aumenta su capacidad de ser necesario. */

public:
	Stemmer();
	~Stemmer();
	std::string stemPalabra( std::string w );

private:
	void increase_s();
	int stem(std::string p, int i, int j);
	void paso5();
	void paso4();
	void paso3();
	void paso2();
	void paso1ab();
	void paso1c();
	void r(int length,std::string s);
	void setto(int length,std::string s);
	int ends(int length,std::string s);
	int cvc(int i);
	int dobleConsonante(int j);
	int vocalEnStem();
	int m();
	int esConsonante(int i);
};

#endif

