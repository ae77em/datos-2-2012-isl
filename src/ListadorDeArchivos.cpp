#include "ListadorDeArchivos.h"

#include <cstring>
#include <dirent.h>
#include <sys/stat.h>
#include <sys/types.h>

ListadorDeArchivos::ListadorDeArchivos() {

}

ListadorDeArchivos::~ListadorDeArchivos() {

}

std::list<std::string>* ListadorDeArchivos::listarArchivos(std::string ruta) {
	std::list<std::string>* archivos = new std::list<std::string>();
	listarArchivos(ruta, archivos);

	return archivos;
}

void ListadorDeArchivos::listarArchivos(std::string ruta, std::list<std::string>* archivos) {
	struct dirent* archivo;
	DIR* directorio;

	directorio = opendir (ruta.c_str());
	if (directorio == NULL){
		return;
	}

	while  ((archivo = readdir(directorio)) != NULL) {
		std::string nomArchivo = ruta + "/" + archivo->d_name;

		if (archivo->d_type == DT_DIR) {
			if (strcmp(archivo->d_name, ".") != 0 && strcmp(archivo->d_name, "..") != 0) {
				listarArchivos(nomArchivo, archivos);
			}
		}else {
			archivos->push_back(nomArchivo);
		}
	}

	closedir(directorio);
}
