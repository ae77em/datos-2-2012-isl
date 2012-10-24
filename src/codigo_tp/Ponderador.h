/*
 * Ponderador.h
 *
 *  Created on: 18/10/2012
 *      Author: esteban
 *     Comment: Clase con funciones comunes para el programa.
 */

#ifndef PONDERADOR_H_
#define PONDERADOR_H_

#include <sstream>
#include <string>
#include <cstdint>
#include <algorithm>


class Ponderador {
private:

	float conTresDecimales( float );

public:

	Ponderador();

	virtual ~Ponderador();

	static float normaVectorialMatriz( MatrizDispersa<float> &);

	static void ponderacionLocal( MatrizDispersa<float> & );

	static float cocientePonderacionGlobal( float, float, unsigned );

	static void ponderacionGlobal( MatrizDispersa<float> & , unsigned);

	static float calculoDeSimilitud( float q[], float d[], int );

	static void dotVectores( float mat1[], float mat2[], float& dot, int tamanio );

};




#endif /* PONDERADOR_H_ */
