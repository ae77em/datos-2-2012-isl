#include <stdlib.h>
#include <time.h>
#include "redsvd/src/eigen/Eigen/Dense.h"

using namespace std;
using namespace Eigen;

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

void crearMatrizFormatoMM(){

		srand(time(NULL));

	    int fila=100000,columna=750000,contador=0,indice=0,
	    		indicesDistintosDeCero=1000;

	    float valorIndice=0;

	    vector<float>* contenedor = new vector<float>;
	    contenedor->resize(fila,0);

	    fstream archivo;
	    archivo.open("/home/federico/pruebasPython/mm1x5term75x4docIndices75x7.mm",fstream::out);

	    archivo<<"%%MatrixMarket matrix coordinate real general"<<endl;
	    //inserto cabecera del archivo
	    //doc - terminos - indices distintos de cero

	    archivo<<columna<<" "<<fila<<" "<<(indicesDistintosDeCero*columna)<<endl;

	    register int valoresIngresados=0;

	    for(register int i=1;i<=columna;i++){

	        for(register int j=1;j<=indicesDistintosDeCero;j++){
	        	//en este bucle cargo el vector de longitud Filas con indicesDistintosDeCero valores diferentes
	        	indice =  rand()%fila;
	        	valorIndice = 1 + log10 (1 + rand()%20000);

	        	if(contenedor->at(indice)!=0){
	        		//busco lugar vacion dentro del vector
	        		while(contenedor->at(indice)!=0){

	        			//si llego al final del vector
	        			if(indice==(fila-1)){
	        				indice=-1;
	        			}

	        			++indice;
	        		}
	        	}
	        	if(indice<0){
	        	cout<<indice<<endl;
	        	}
	        	contenedor->at(indice) = valorIndice;
	        }

	        for(register unsigned int k=0; k<contenedor->size(); k++){

	        	if(contenedor->at(k)!=0){
	        		archivo<<i<<" "<<k+1<<" "<<contenedor->at(k)<<endl;
	        		contador++;
	        		contenedor->at(k)=0;
	        		++valoresIngresados;
	        	}

	        	if(valoresIngresados==indicesDistintosDeCero){
	        		valoresIngresados=0;
	        		break;
	        	}

	        }

	    }

	    cout<<endl<<"ingrese:  "<<contador<<endl;

	    archivo.close();


}

/*
 * Principal.
 */
int main(int argc, char **argv) {

	cout << "AHORA ENTRA A NUESTRO MAIN, Y RESPONDE SEGUN LOS PARAMETROS INGRESADOS\n"<< endl;

	if ( argv[1] ){

		if(argv[1]==string("-c")){
			if(argc<3){
				std::cout << "\n>> Se debe especificar una direccion para la incorporacion de archivos" << std::endl;
			} else {
				incorporacion(argv[2]);
			}
		} else if(argv[1]==string("-x")){
			if(argc<3){
				std::cout << "\n>> Se debe especificar al menos una palabra clave para la busqueda" << std::endl;
			} else {
				busqueda(argc, argv);
			}
		} else if(argv[1]==string("-h")){
			ayuda();
		}
		else {
			std::cout << "\n>> Comando '" << argv[1] << "' no valido." << std::endl;
		}

	}
	else {
		std::cout << ">> No se han ingresado parametros." << std::endl;
	}


	return 0;
}



