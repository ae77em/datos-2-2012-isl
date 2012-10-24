#ifndef __LISTADOR_DE_ARCHIVOS_H_
#define __LISTADOR_DE_ARCHIVOS_H_

#include <iostream>
#include <list>
#include <cstring>
#include <dirent.h>
#include <sys/stat.h>
#include <sys/types.h>

class ListadorDeArchivos {

private:
		std::string ruta;

public:
		ListadorDeArchivos();

		ListadorDeArchivos(std::string);

		std::list<std::string>* listarArchivos();

		~ListadorDeArchivos();


private:
		void listarArchivos(std::string,std::list<std::string>*);
};

#endif
