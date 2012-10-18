/*
 * Utilities.cpp
 *
 *  Created on: 18/10/2012
 *      Author: esteban
 */

#include "Utilities.h"

Utilities::Utilities() {
	// TODO Auto-generated constructor stub

}

float Utilities::conTresDecimales(float numero){

	return floor(numero * 1000) / 1000;
}


/*
 * Transforma un entero en string
 *
 * @param numero El entero a transformar
 */
std::string Utilities::intToString(uint32_t numero) {

  std::string snumero;
  std::stringstream cvz;
  cvz.width();
  cvz << numero;
  snumero= cvz.str();

  return snumero;
}

/*
 * Transforma un string a minusculas.
 *
 * @param str El string a transformar.
 */
void Utilities::pasarAminusculas(std::string& str){
     std::transform(str.begin(), str.end(), str.begin(), ::tolower);
}

/*
 * Calcula la norma vectorial de *this. *this debe ser un vector
 * de tipo MatrizInversa...es malo el metodo pero bueno, es lo que hay
 */
float Utilities::normaVectorialMatriz( MatrizDispersa<float> & mat){

	//float norma = 0;

	/*if ( mat.cols() != 1 && mat.rows() != 1 )
		return 0; // si no es un vector

	if ( mat.cols() == 1 && mat.rows() == 1 )
		return mat(0,0);

	if ( mat.cols() > 1 )
		for ( unsigned i = 0; i < mat.cols(); ++i )
			norma += pow(mat(0,i),2);

	else if ( mat.rows() > 1 )
		for ( unsigned i = 0; i < mat.rows(); ++i )
			norma += pow(mat(i,0),2);*/

	float norma = mat.dot(mat,mat); // calculo el producto escalar

	return floor ( sqrt(norma) * 1000 ) / 1000;

}

/*
 * Calcula la importancia local de un término en un doc.
 * @param : ft = frecuencia del termino en el documento.
 */
void Utilities::ponderacionLocal( MatrizDispersa<float> & mat ){

	for ( unsigned i = 0; i < mat.rows(); ++i )
		for ( unsigned j = 0; j < mat.cols(); ++j ){
			float ft = mat(i,j);
			float log = log10( ft + 1 );
			mat(i,j) = floor( log * 1000 ) / 1000;
		}
}

/*
 * Calcula la importancia global de un término en un doc.
 * @param : ft = frecuencia del termino en el documento.
 * @param : fgt = frecuencia global del termino, esto es,
 * 			la cantidad de apariciones en la totalidad de
 * 			este.
 * @param : n = cantidad de columnas/documentos.
**/
float Utilities::cocientePonderacionGlobal( float ft, float fgt, unsigned n ){

	if ( ft == 0 || fgt == 0) return 0;
	float p = ft / fgt;
	float logn = log10(n); // supongo que siempre se trata de log en base 10...
	float logp = log10(p);

	float g = p * logp / logn; // <-- ponderacion global del termino
	return floor ( g * 1000 ) / 1000;
}

/*
 * Calcula la ponderacion global de un término, usando el metodo de Entropia.
 * En este caso se le pasa la matriz con la ponderacion local en cada una de
 * sus componentes....
 */
void Utilities::ponderacionGlobal( MatrizDispersa<float> & mat, unsigned colIni ){

	unsigned nroTermino = 0;
	while ( nroTermino < mat.rows() ){
		MatrizDispersa<float> aux(1,mat.rows());
		float sumatoria = 0;
		float fgt = 0;
		for ( unsigned k = colIni; k < mat.cols(); ++k )
			if ( mat(nroTermino,k) != 0 )
				fgt += pow(10,mat(nroTermino,k))-1;

		for ( unsigned j = colIni; j < mat.cols(); ++j ){
			float ft = mat(nroTermino,j);
			sumatoria += cocientePonderacionGlobal( ft, fgt, mat.cols());
			aux(0,j) = sumatoria;
		}
		sumatoria++; // le sumo uno

		// multiplico a la fila correspondiente con el termino
			// por su ponderacion global
		for ( unsigned j = colIni; j < mat.cols(); ++j ){
			float g = mat(nroTermino,j)*sumatoria;
			mat(nroTermino,j) = floor ( g * 1000) / 1000;
		}

		nroTermino++;
	}

}

float Utilities::calculoDeSimilitud( float q[], float d[], int tamanio){

	float auxRaiz, auxRaiz2;
	float numerador;
	//float* d = new float[A.rows()]; // d corresponde a un fila de D, que es la matriz de docs

	Utilities::dotVectores(d,q,numerador,tamanio);

	Utilities::dotVectores(q,q,auxRaiz,tamanio); // calculo la norma de q
	Utilities::dotVectores(d,d,auxRaiz2,tamanio); // y d

	auxRaiz = sqrt(auxRaiz);
	auxRaiz2 = sqrt(auxRaiz2);

	auxRaiz *= auxRaiz2;

	 //delete d;
	return conTresDecimales( numerador/ auxRaiz );
}


/*
 * Producto vectorial
 */
void Utilities::dotVectores( float mat1[], float mat2[], float& dot, int tamanio ){


	if (sizeof(mat1) != sizeof(mat2))
		return;

	float aux1,aux2;
	for (int i = 0; i < tamanio; ++i ){
		aux1 = mat1[i];
		aux2 = mat2[i];
		dot += (aux1 * aux2);
	}
}




Utilities::~Utilities() {
	// TODO Auto-generated destructor stub
}

