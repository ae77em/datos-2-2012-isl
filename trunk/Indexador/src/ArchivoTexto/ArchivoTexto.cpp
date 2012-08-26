/*
 * ArchivoTexto.cpp
 *
 *  Created on: 23/09/2011
 *      Author: esteban, mariano simone
 */

#include "ArchivoTexto.h"
#include <iostream>

using namespace std;

ArchivoTexto::ArchivoTexto(){};

/**
  * Cierra el archivo (no lo destruye físicamente)
  */
ArchivoTexto::~ArchivoTexto() {
  archivo.close();
}

/* Abre el archivo ubicado en el path pasado
 * (debe incluir nombre completo) en modo lectura.
 * Si no puede realizar la operacion, arroja una excepcion.
 */
void ArchivoTexto::abrirParaLectura(const std::string& path) {
  //intenta abrir el archivo en modo lectura
  archivo.open(path.c_str(), std::fstream::in);

  if (!archivo.is_open())
	  // si no se pudo crear el archivo arroja una excepción/
	  throw std::ios_base::failure("El archivo no pudo ser abierto\n");

}


/**
 * Posiciona el cursor en una nueva linea debajo de la actual
 * Si no puede hacerlo, arroja una excepción
 */
void ArchivoTexto::terminarLinea() {
  // intenta escribir en el archivo
  archivo << endl;

  if (archivo.fail())
    //si se produjo un error, arroja una excepcion
    throw std::ios_base::failure("No se pudo terminar la linea");
}

/**
 * Lee del archivo una cadena de caracteres a partir de la posiciOn actual del cursor y hasta:
 *  - Que se encuentre un fin de linea
 *  - Se lean MAX_LENGTH caracteres
 * El contenido leido se almacena en el parametro "cadena"
 * Retorna true si pudo leer una linea, o false en caso contrario
 */
bool ArchivoTexto::leerLinea(std::string &cadena) {
  char linea[MAX_LENGTH];

  // lee del archivo a la linea, hasta haber leido:
  // MAX_LENGTH caracteres, o un fin de linea
  archivo.getline( (char*)&linea , MAX_LENGTH , '\n');
  cadena = linea;

  if (archivo.fail() ) {
    //chequea si se ha producido un error, se devuelve false
    archivo.clear();
    return false;
  }
  return true;
}

/**
 * Posiciona el cursor al comienzo del archivo
 */
void ArchivoTexto::irAlPrincipio() {
  archivo.tellg();
  archivo.clear();
  archivo.seekg(0, ios::beg);
  archivo.seekp(0, ios::beg);
  archivo.tellg();
}

/**
 * Posiciona el cursor al final del archivo
 */
void ArchivoTexto::irAlFinal() {
  archivo.tellg();
  archivo.clear();
  archivo.seekg(0, ios::end);
  archivo.seekp(0, ios::end);
  archivo.tellg();
}
