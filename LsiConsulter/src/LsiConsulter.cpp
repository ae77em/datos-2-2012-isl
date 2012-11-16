//============================================================================
// Name        : LsiConsulter.cpp
// Author      : fede
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include <string>
#include "Consulter.h"

int main() {

	std::string consulta= "";

	Consulter* consulter = new Consulter();
	consulter->analizarConsulta(consulta); //representa la serie de la palabras que conformen la consulta

	return 0;
}
