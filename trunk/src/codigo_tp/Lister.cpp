#include "Lister.h"

#include <cstring>
#include <dirent.h>
#include <sys/stat.h>
#include <sys/types.h>

Lister::Lister(std::string ruta) {
	this->ruta = ruta;
}

std::list<std::string>* Lister::listarArchivos() {
	std::list<std::string>* lista;

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
				listarArchivos(nomArchivo, lista);
			}
		}else {
			lista->push_back(nomArchivo);
		}
	}

	closedir(directorio);
	return lista;
}
