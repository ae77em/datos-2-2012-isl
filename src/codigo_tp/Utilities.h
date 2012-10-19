/*
 * Utilities.h
 *
 *  Created on: 18/10/2012
 *      Author: esteban
 *     Comment: Clase con funciones comunes para el programa.
 */

#ifndef UTILITIES_H_
#define UTILITIES_H_

#include <sstream>
#include <string>
#include <cstdint>
#include <algorithm>


class Utilities {
public:
	Utilities();

	virtual ~Utilities();

	static std::string intToString(uint32_t numero);

	static void pasarAminusculas(std::string& str);

	static float conTresDecimales( float );

	static float normaVectorialMatriz( MatrizDispersa<float> &);

	static void ponderacionLocal( MatrizDispersa<float> & );

	static float cocientePonderacionGlobal( float, float, unsigned );

	static void ponderacionGlobal( MatrizDispersa<float> & , unsigned);

	static float calculoDeSimilitud( float q[], float d[], int );

	static void dotVectores( float mat1[], float mat2[], float& dot, int tamanio );

};




#endif /* UTILITIES_H_ */
