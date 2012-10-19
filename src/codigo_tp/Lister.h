#ifndef __LISTER_H_
#define __LISTER_H_

#include <iostream>
#include <list>
#include <cstring>
#include <dirent.h>
#include <sys/stat.h>
#include <sys/types.h>

class Lister {

private:
		std::string ruta;
		std::list<std::string>* lista;

public:
		Lister();
		Lister(std::string);
		~Lister();
		std::list<std::string>* listarArchivos();

private:
		void listarArchivos(std::string,std::list<std::string>*);
};

#endif
