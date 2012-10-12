#ifndef __LISTER_H_
#define __LISTER_H_

#include <iostream>
#include <list>

class Lister {
	private:
		std::string ruta;
	public:
		Lister(std::string ruta);
		~Lister();
		std::list<std::string>* listarArchivos ();
};

#endif