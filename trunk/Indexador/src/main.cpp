#include "AnalizadorGramatico/AnalizadorGramatico.h"
#include "Trie/Trie.h"
#include "Utilidades/Utilidades.h"
#include "Indexador/Indexador.h"
#include "RecorredorDeDirectorios/RecorredorDeDirectorios.h"
#include "Consulta/Consulta.h"

/*#include <Eigen/Dense>
#include <Eigen/Sparse>*/

#include <iostream>
#include <list>

//using namespace Eigen;
using namespace std;

#define EIGEN_YES_I_KNOW_SPARSE_MODULE_IS_NOT_STABLE_YET
/*
 * Pos: incorpora archivos al índice.
 */
void incorporacion(std::string directorio)
{
	//Indexador index;

	//index.indexarDirectorio(directorio);
	std::cout << ">> Se han incorporado archivos" << std::endl;

}

/*
 * Pos: busca los archivos que mejor coinciden con las palabras claves, los ordena
 * 		por relevancia y los muestra por pantalla.
 */
void busqueda(int argc, char **argv)
{
	std::cout << ">> Busqueda terminda" << std::endl;
}

/*
 * Pos: muestra por pantalla una mensaje de ayuda indicando comandos válidos.
 */
void ayuda()
{
	std::cout << "\n>> Comandos validos:\n"
			"\n\t'-i' -> incorporacion de archivos"
			"\n\t'-q' -> busqueda de archivos"
			"\n\nIncorporacion: el siguiente argumento a este comando debe ser un directorio."
			"\nBusqueda: los siguientes argumentos deben ser palabras de busqueda, indicando el principio y el final de éstas con comillas"<< std::endl;
}

/*
 * Principal.
 */
int main(int argc, char **argv) {


	if ( argv[1] ){

		if(argv[1]==string("-c")){
			if(argc<3){
				std::cout << ">> Se debe especificar una direccion para la incorporacion de archivos" << std::endl;
			} else {
				incorporacion(argv[2]);
			}
		} else if(argv[1]==string("-x")){
			if(argc<3){
				std::cout << ">> Se debe especificar al menos una palabra clave para la busqueda" << std::endl;
			} else {
				busqueda(argc, argv);
			}
		} else if(argv[1]==string("-h")){
			ayuda();
		}
		else {
			std::cout << ">> Comando '" << argv[1] << "' no valido." << std::endl;
		}

	}
	else {
		std::cout << ">> No se han ingresado parametros." << std::endl;
	}


	return 0;
}




