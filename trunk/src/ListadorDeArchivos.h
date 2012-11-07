#ifndef __LISTADOR_DE_ARCHIVOS_H_
#define __LISTADOR_DE_ARCHIVOS_H_

#include <list>
#include <string>

class ListadorDeArchivos {
	private:
		/**
		 * Metodo privado que permite recorrer los subdirectorios recursivamente.
		 */
		void listarArchivos(std::string directorio, std::list<std::string>* archivos);
	public:
		ListadorDeArchivos();
		~ListadorDeArchivos();

		/**
		 * Metodo publico para obtener la lista de archivos existentes
		 * en el directorio pasado como parametro y en todos sus
		 * subdirectorios.
		 */
		std::list<std::string>* listarArchivos(std::string directorio);
};

#endif
