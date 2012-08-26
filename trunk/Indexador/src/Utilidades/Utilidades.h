/*
 * Utilidades.h
 *
 *  Created on: 15/09/2011
 *      Author: esteban
 */
#ifndef UTILIDADES_H_
#define UTILIDADES_H_

#define EIGEN_YES_I_KNOW_SPARSE_MODULE_IS_NOT_STABLE_YET

#include <sstream>
#include <string>
#include <stdint.h>
#include <algorithm>
#include <vector>
//#include <../Eigen/Eigen/Sparse>

/**
 * Clase con funciones comunes para el programa.
 */
/*
typedef Eigen::SparseMatrix<float, Eigen::RowMajor> SMatrixXf;
typedef std::vector<std::pair<int, float> > fv_t;
*/
class Utilidades {

private:

	static void sampleTwoGaussian(float& f1, float& f2);

public:

	static std::string intToString(uint32_t numero);

 	static void pasarAminusculas(std::string& str);

 	/*static void ortogonalizacionGramSchmidt( MatrizDispersa<float>& );

	static float normaVectorialMatriz( MatrizDispersa<float> &);

	static void borrarFila( MatrizDispersa<float> & mat , unsigned nroFila );

	static void redimensionarMatriz( MatrizDispersa<float> & , unsigned , unsigned );

	static void cambiarFilas( MatrizDispersa<float> & , unsigned );

	static void cambiarColumnas( MatrizDispersa<float> & , unsigned );

	static void ponderacionLocal( MatrizDispersa<float> & );*/

	static float cocientePonderacionGlobal( float, float, unsigned );

	/*static void ponderacionGlobal( MatrizDispersa<float> & , unsigned);*/

	static void dotVectores( float i[], float j[], float&, int);

	static float conTresDecimales( float );

	static float calculoDeSimilitud( float q[], float d[], int );

	/*static void convertFV2Mat(const std::vector<fv_t>& fvs, SMatrixXf& A);

	static void sampleGaussianMat(Eigen::MatrixXf& x);

	static void processGramSchmidt(Eigen::MatrixXf& mat);*/

	static double getSec();

};

#endif /* UTILIDADES_H_ */
