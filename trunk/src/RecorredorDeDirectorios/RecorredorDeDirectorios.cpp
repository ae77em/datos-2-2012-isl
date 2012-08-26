/*
 * RecorredorDeDirectorios.cpp
 *
 *  Created on: 22/10/2011
 *      Author: user
 */
#include "RecorredorDeDirectorios.h"
#include <list>
#include <iostream>

using namespace std;

RecorredorDeDirectorios::RecorredorDeDirectorios(){
	listaDeDirectorios = new list<string>;
}

RecorredorDeDirectorios::~RecorredorDeDirectorios(){}


void RecorredorDeDirectorios::contarDirectoriosArchivos(string & path,int* contDir ,int* contArchivo,int* contOtroTipoDeArchivo){

  DIR *dir;
  struct dirent *ent;

  cout<<"este es el path que estoy abriendo: "<<path<<endl;
  cout<<"este es el tamaño del path: "<<path.size()<<endl;
  dir = opendir (path.c_str());

  if (dir == NULL){
      //cout<<"No se pudo abrir el directorio: "<<path << endl;
  	  cout<<"Salgo recorredor"<<endl;;
  	  return;
  }
  else {
      string punto=".";
      string dosPuntos="..";

      while ((ent = readdir (dir)) != NULL){

          if( not ((ent->d_name==punto )||( ent->d_name==dosPuntos))){

                struct stat buffer;
                stat(ent->d_name,&buffer);
                cout << "\nStat = "<< true;
                cout << "\nBuffer = "<< &buffer;

                switch(buffer.st_mode & S_IFMT){
                 	case S_IFDIR : cout<<"\nDirectorio "; break;
                	case S_IFREG : cout<<"\nFichero regular "; break;
                	case S_IFCHR : cout<<"\nDispositivo de tipo caracter "; break;
                	case S_IFBLK : cout<<"\nDispositivo de tipo bloque "; break;
                	case S_IFIFO : cout<<"\nTuberRa nominada "; break;
                	default : cout<<"\ntipo desconocido";break;
                }

                //cout<<"este es el tipo del archivo: "<< buffer.st_mode<<endl;
                if ( (buffer.st_mode & S_IFMT) == S_IFREG ){
                    *contArchivo= *contArchivo + 1;
                    cout<<"esto es un archivo de texto con nombre: "<<ent->d_name<<endl;
                    listaDeDirectorios->push_front((string&)ent->d_name);
                }

                if ( (buffer.st_mode & S_IFMT) == S_IFDIR ){
                    *contDir=*contDir + 1;
                    cout<<"entro en el directorio: "<< ent->d_name<<endl;
                    string subPath=ent->d_name;
                    this->contarDirectoriosArchivos(subPath,contDir,contArchivo,contOtroTipoDeArchivo);
                }
                else
                    *contOtroTipoDeArchivo=*contOtroTipoDeArchivo + 1;

                //cout<<ent->d_name<<endl;
          }
              //  S_ISREG (datosFiche.st_mode);
           // S_ISDIR (datosFichero.st_mode);
       //if ( (strcmp(ent->d_name, ".")!=0) && (strcmp(ent->d_name, "..")!=0) )

        }
      cout<<"\nSalgo recorredor";
      closedir (dir);
    }

}

list<string>* RecorredorDeDirectorios::obtenerListaDeDirectorios(){
	cout<<"Intento obtener lista de directorios"<<endl;
	return listaDeDirectorios;

}

