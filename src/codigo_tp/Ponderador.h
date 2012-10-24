/*
 * Ponderador.h
 *
 *  Created on: 18/10/2012
 *      Author: esteban
 *     Comment: Clase con funciones comunes para el programa.
 */


#include <Eigen/Sparse>

#ifndef PONDERADOR_H_
#define PONDERADOR_H_

using namespace Eigen;

class Ponderador {
private:

	float conTresDecimales( float );

public:

	Ponderador();

	virtual ~Ponderador();

	static float normaVectorialMatriz( MatrixXf&);

	static void ponderacionLocal( MatrixXf& );

	static float cocientePonderacionGlobal( float, float, unsigned );

	static void ponderacionGlobal( MatrixXf& , unsigned);

	static float calculoDeSimilitud( float q[], float d[], int );

	static void dotVectores( float mat1[], float mat2[], float& dot, int tamanio );

};

#endif /* PONDERADOR_H_ */
