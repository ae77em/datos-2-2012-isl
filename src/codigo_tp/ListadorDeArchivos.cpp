#include "ListadorDeArchivos.h"


ListadorDeArchivos::ListadorDeArchivos(std::string ruta ) {
	this->ruta = ruta;
}

std::list<std::string>* ListadorDeArchivos::listarArchivos() {

	std::list<std::string>* lista = new std::list<std::string>;

	listarArchivos(this->ruta, lista);

	return lista;
}

void ListadorDeArchivos::listarArchivos(std::string ruta,std::list<std::string>* lista) {

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
}
