/*
 * Utilidades.cpp
 *
 *  Created on: 15/09/2011
 *      Author: esteban
 */

#include "Utilidades.h"
//#include <Eigen/Sparse>
//#include <Eigen/Dense>
#include <cmath>
#include <sys/time.h>

//using namespace Eigen;
/*
 * Transforma un entero en string
 *
 * @param numero El entero a transformar
 */
std::string Utilidades::intToString(uint32_t numero) {

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
void Utilidades::pasarAminusculas(std::string& str){
     std::transform(str.begin(), str.end(), str.begin(), ::tolower);
}
const float SVD_EPS = 0.0001f;

double Utilidades::getSec(){
  timeval tv;
  gettimeofday(&tv, NULL);
  return tv.tv_sec + (double)tv.tv_usec*1e-6;
}

/*
void Utilidades::sampleTwoGaussian(float& f1, float& f2){
  float v1 = (float)(rand() + 1.f) / ((float)RAND_MAX+2.f);
  float v2 = (float)(rand() + 1.f) / ((float)RAND_MAX+2.f);
  float len = sqrt(-2.f * log(v1));
  f1 = len * cos(2.f * M_PI * v2);
  f2 = len * sin(2.f * M_PI * v2);
}

void Utilidades::sampleGaussianMat(MatrixXf& mat){
  for (int i = 0; i < mat.rows(); ++i){
    int j = 0;
    for ( ; j+1 < mat.cols(); j += 2){
      float f1, f2;
      sampleTwoGaussian(f1, f2);
      mat(i,j  ) = f1;
      mat(i,j+1) = f2;
    }
    for (; j < mat.cols(); j ++){
      float f1, f2;
      sampleTwoGaussian(f1, f2);
      mat(i, j)  = f1;
    }
  }
}


void Utilidades::processGramSchmidt(MatrixXf& mat){
  for (int i = 0; i < mat.cols(); ++i){
    for (int j = 0; j < i; ++j){
      float r = mat.col(i).dot(mat.col(j));
      mat.col(i) -= r * mat.col(j);
    }
    float norm = mat.col(i).norm();
    if (norm < SVD_EPS){
      for (int k = i; k < mat.cols(); ++k){
	mat.col(k).setZero();
      }
      return;
    }
    mat.col(i) *= (1.f / norm);
  }
}

void Utilidades::convertFV2Mat(const std::vector<fv_t>& fvs, SMatrixXf& A){
  int maxID = 0;
  size_t nonZeroNum = 0;
  for (size_t i = 0; i < fvs.size(); ++i){
    const fv_t& fv(fvs[i]);
    for (size_t j = 0; j < fv.size(); ++j){
      maxID = std::max(fv[j].first+1, maxID);
    }
    nonZeroNum += fv.size();
  }
  A.resize(fvs.size(), maxID);
  A.reserve(nonZeroNum);
  for (size_t i = 0; i < fvs.size(); ++i){
    A.startVec(i);
    const fv_t& fv(fvs[i]);
    for (size_t j = 0; j < fv.size(); ++j){
      A.insertBack(i, fv[j].first) = fv[j].second;
    }
  }
  A.finalize();
}
*/
/*
 * Ortogonaliza la matriz pasada con el metodo de Gram-Schmidt
 *
 * @param mat : matriz a ortogonalizar.
 *
void Utilidades::ortogonalizacionGramSchmidt( MatrixXf& mat ){

	for (int i = 0; i < mat.cols(); ++i){
	    for (int j = 0; j < i; ++j){
			float r = mat.col(i).dot(mat.col(j));
			mat.col(i) -= r * mat.col(j);
	    }
	    float norm = mat.col(i).norm();
	    if (norm < SVD_EPS){
	    	for (int k = i; k < mat.cols(); ++k){
				mat.col(k).setZero();
	    	}
	    	return;
	    }
	    mat.col(i) *= (1.f / norm);
	}
}
*/
/*
 * Calcula la norma vectorial de *this. *this debe ser un vector
 * de tipo MatrizInversa...es malo el metodo pero bueno, es lo que hay
 *
float Utilidades::normaVectorialMatriz( MatrixXf & mat){

	//float norma = 0;
*/
	/*if ( mat.cols() != 1 && mat.rows() != 1 )
		return 0; // si no es un vector

	if ( mat.cols() == 1 && mat.rows() == 1 )
		return mat(0,0);

	if ( mat.cols() > 1 )
		for ( unsigned i = 0; i < mat.cols(); ++i )
			norma += pow(mat(0,i),2);

	else if ( mat.rows() > 1 )
		for ( unsigned i = 0; i < mat.rows(); ++i )
			norma += pow(mat(i,0),2);*

	float norma = mat.dot(mat,mat); // calculo el producto escalar

	return floor ( sqrt(norma) * 1000 ) / 1000;

}
*/
/*
 * Borra la fila de la matriz indicada
 *
 * @param mat: matriz a la cual se le borra la fila.
 * @param nroFila: numero de fila a borrar. Se numeran
 * 				   de 0 a cantidad de filas - 1.
 *
void Utilidades::borrarFila( MatrixXf & mat , unsigned nroFila ){

	for ( unsigned i = nroFila; i < mat.rows()-1; ++i)
		for ( unsigned j = 0; j < mat.cols(); ++j){
			mat(i,j) = mat(i+1,j);
	}
	redimensionarMatriz(mat,mat.rows()-1,mat.cols());
	mat.reSize(mat.size()+1);
}
*/
/*
 * Redimensiona una matriz. No borra lo que ya esta. Si
 * la nueva dimension es menor a la anterior, ya sea por
 * fila, columna, o ambas, corta por derecha y por abajo.
 * En caso contrario, agrega filas y/o columnas de ceros.
 *
 * @param mat: matriz a la cual se redimensiona.
 * @param fila y col: cantidades nuevas de filas y columnas.
 *
 *
void Utilidades::redimensionarMatriz( MatrixXf & mat, unsigned filas, unsigned columnas ){

	mat.setCols(columnas);
	mat.setRows(filas);
	if ( mat.capacity() <= mat.size() )
		mat.reSize( mat.size()+1 );

}

void Utilidades::cambiarColumnas( MatrixXf & mat, unsigned columnas ){

	mat.setCols(columnas);
	if ( mat.capacity() <= mat.size() )
		mat.reSize( mat.size()+1 );

}

void Utilidades::cambiarFilas( MatrixXf & mat, unsigned filas ){

	mat.setRows(filas);
	if ( mat.capacity() <= mat.size() )
		mat.reSize( mat.size()+1 );

}
*/
/*
 * Calcula la importancia local de un término en un doc.
 * @param : ft = frecuencia del termino en el documento.
 *
void Utilidades::ponderacionLocal( MatrixXf & mat ){

	for ( unsigned i = 0; i < mat.rows(); ++i )
		for ( unsigned j = 0; j < mat.cols(); ++j ){
			float ft = mat(i,j);
			float log = log10( ft + 1 );
			mat(i,j) = floor( log * 1000 ) / 1000;
		}
}
*/
/*
 * Calcula la importancia global de un término en un doc.
 * @param : ft = frecuencia del termino en el documento.
 * @param : fgt = frecuencia global del termino, esto es,
 * 			la cantidad de apariciones en la totalidad de
 * 			este.
 * @param : n = cantidad de columnas/documentos.
**
float Utilidades::cocientePonderacionGlobal( float ft, float fgt, unsigned n ){

	if ( ft == 0 || fgt == 0) return 0;
	float p = ft / fgt;
	float logn = log10(n); // supongo que siempre se trata de log en base 10...
	float logp = log10(p);

	float g = p * logp / logn; // <-- ponderacion global del termino
	return floor ( g * 1000 ) / 1000;
}
*/
/*
 * Calcula la ponderacion global de un término, usando el metodo de Entropia.
 * En este caso se le pasa la matriz con la ponderacion local en cada una de
 * sus componentes....
 *
void Utilidades::ponderacionGlobal( MatrixXf & mat, unsigned colIni ){

	unsigned nroTermino = 0;
	while ( nroTermino < mat.rows() ){
		MatrixXf aux(1,mat.rows());
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

float Utilidades::conTresDecimales(float numero){

	return floor(numero * 1000) / 1000;
}


float Utilidades::calculoDeSimilitud( float q[], float d[], int tamanio){

	float auxRaiz, auxRaiz2;
	float numerador;
	//float* d = new float[A.rows()]; // d corresponde a un fila de D, que es la matriz de docs

	Utilidades::dotVectores(d,q,numerador,tamanio);

	Utilidades::dotVectores(q,q,auxRaiz,tamanio); // calculo la norma de q
	Utilidades::dotVectores(d,d,auxRaiz2,tamanio); // y d

	auxRaiz = sqrt(auxRaiz);
	auxRaiz2 = sqrt(auxRaiz2);

	auxRaiz *= auxRaiz2;

	 //delete d;
	return conTresDecimales( numerador/ auxRaiz );
}

*/
/*
 * Producto vectorial
 */
void Utilidades::dotVectores( float mat1[], float mat2[], float& dot, int tamanio ){


	if (sizeof(mat1) != sizeof(mat2))
		return;

	float aux1,aux2;
	for (int i = 0; i < tamanio; ++i ){
		aux1 = mat1[i];
		aux2 = mat2[i];
		dot += (aux1 * aux2);
	}
}

