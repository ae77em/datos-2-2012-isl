/*
 * Utilities.h
 *
 *  Created on: 18/10/2012
 *      Author: esteban
 */

#ifndef UTILITIES_H_
#define UTILITIES_H_

class Utilities {
public:
	Utilities();
	/*
	 * Utilidades.h
	 *
	 *  Created on: 15/09/2011
	 *      Author: esteban
	 */
	#ifndef UTILIDADES_H_
	#define UTILIDADES_H_

	#include <sstream>
	#include <string>
	#include <stdint.h>
	#include <algorithm>
	#include "MatrizDispersa.h"
	/**
	 * Clase con funciones comunes para el programa.
	 */
	class Utilidades {

	public:

		static std::string intToString(uint32_t numero);

	 	static void pasarAminusculas(std::string& str);

	 	static float conTresDecimales( float );

		static float normaVectorialMatriz( MatrizDispersa<float> &);

		static void ponderacionLocal( MatrizDispersa<float> & );

		static float cocientePonderacionGlobal( float, float, unsigned );

		static void ponderacionGlobal( MatrizDispersa<float> & , unsigned);

		static float calculoDeSimilitud( float q[], float d[], int );

	};



	virtual ~Utilities();
};

#endif /* UTILITIES_H_ */
