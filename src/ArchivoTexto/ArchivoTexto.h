/*
 * ArchivoTexto.h
 *
 *  Created on: 23/09/2011
 *      Author: esteban, mariano simone
 */

#ifndef ARCHIVOTEXTO_H_
#define ARCHIVOTEXTO_H_

#ifndef MAX_LENGTH
#define MAX_LENGTH 256
#endif

//Inclusiones necesarias
#include <fstream>
#include <iostream>

class ArchivoTexto {
private:
   std::fstream  archivo;  // referencia al archivo


public:

  ArchivoTexto();

  ~ArchivoTexto();

  void abrirParaLectura(const std::string& path);

  void abrirParaEscritura(const std::string& path);

  void escribir(char c);

  void escribir(const std::string& cadena);

  void terminarLinea();

  void tabular();

  bool leerLinea(std::string &cadena );

  void irAlPrincipio();

  void irAlFinal();
};

#endif
