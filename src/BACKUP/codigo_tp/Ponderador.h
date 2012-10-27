/*
 * Ponderador.h
 *
 *  Created on: 18/10/2012
 *      Author: esteban
 *     Comment: Clase con funciones comunes para el programa.
 */

#ifndef PONDERADOR_H_
#define PONDERADOR_H_

#include <Eigen/src/Sparse>

using namespace Eigen;

class Ponderador {
private:

	float conTresDecimales( float );

	static float normaVectorialMatriz( Eigen::MatrixXf&);

	static float cocientePonderacionGlobal( float, float, unsigned );

	static float calculoDeSimilitud( float q[], float d[], int );

	static void dotVectores( float mat1[], float mat2[], float& dot, int tamanio );

public:

	Ponderador();

	virtual ~Ponderador();

	static void ponderacionLocal( Eigen::MatrixXf& );

	static void ponderacionGlobal( Eigen::MatrixXf& , unsigned);
};

#endif /* PONDERADOR_H_ */
