#include <fstream>
#include <iostream>

int main(int argc, char* argv[]) {
	std::ifstream archivoBinarioPython;

	int cantFilas = 0, cantColumnas = 0;
	double valor;

	archivoBinarioPython.open("/home/lautaro/Escritorio/Datos/codigo/V.bin", std::ios_base::in); // TODO PARA LAS PRUEBAS, SETEAR LA RUTA CORRECTA

	// Leo el tamaño de la matriz
	archivoBinarioPython.read(reinterpret_cast<char*>(&cantFilas), sizeof(int));
	archivoBinarioPython.read(reinterpret_cast<char*>(&cantColumnas), sizeof(int));

	std::cout << cantFilas << std::endl;
	std::cout << cantColumnas << std::endl;

	// Leo la matriz
	archivoBinarioPython.read(reinterpret_cast<char*>(&valor), sizeof(double));

	while (archivoBinarioPython.good()) {
		std::cout << valor << std::endl;
		archivoBinarioPython.read(reinterpret_cast<char*>(&valor), sizeof(double));
	}

	return 0;
}
