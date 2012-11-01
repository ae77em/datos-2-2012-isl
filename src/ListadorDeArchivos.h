#ifndef __LISTADOR_DE_ARCHIVOS_H_
#define __LISTADOR_DE_ARCHIVOS_H_

#include <list>
#include <string>

class ListadorDeArchivos {
	private:
		void listarArchivos(std::string directorio, std::list<std::string>* archivos);
	public:
		ListadorDeArchivos();
		~ListadorDeArchivos();

		std::list<std::string>* listarArchivos(std::string directorio);
};

#endif
