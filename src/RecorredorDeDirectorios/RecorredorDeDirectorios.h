/*
 * RecorredorDeDirectorios.h
 *
 *  Created on: 22/10/2011
 *      Author: user
 */

#ifndef RECORREDORDEDIRECTORIOS_H_
#define RECORREDORDEDIRECTORIOS_H_

#include <stdlib.h>
#include <sys/stat.h>
#include <iostream>
#include <sys/types.h>
#include <dirent.h>
#include <list>

using namespace std;

class RecorredorDeDirectorios {
private:
	list<std::string>* listaDeDirectorios;
public:
	RecorredorDeDirectorios();
	void contarDirectoriosArchivos(std::string &,int*,int*,int*);
	list<std::string>* obtenerListaDeDirectorios();
	virtual ~RecorredorDeDirectorios();
};

#endif /* RECORREDORDEDIRECTORIOS_H_ */
