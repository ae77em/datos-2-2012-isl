#include "Trie.h"
#include <iostream>
#include <string>
#include <stdio.h>
#include <stdlib.h>

void Trie::inicializarRaiz(){

    this->RAIZ=new TnodoPrincipalTrie();
    this->RAIZ->cantidadTotalDePalabrasEnLaColeccion=0;
    this->RAIZ->contadorDeId_s=0;
    this->RAIZ->cantidadDeDocumentoParseados=0;
    this->RAIZ->contenedor = new std::vector<TnodoTerminoId*>;
    this->RAIZ->contenedorParcial = new std::vector<TnodoData*>;
    this->RAIZ->contenedorEntropia = new std::vector<TacumEntropia*>;
    this->RAIZ->padreSupremo = NULL;
}

void Trie::inicializarNodo(TnodoTrie* NODO){

    NODO->letra=FINAL_DE_PALABRA;
    NODO->hermano=NULL;
    NODO->hijo=NULL;
    NODO->infoArchivo=NULL;
    NODO->flagParser=0;

}

Trie::Trie (){

    this->inicializarRaiz();

    TnodoTrie* padreSupremo=new TnodoTrie();

    inicializarNodo(padreSupremo);

    RAIZ->padreSupremo=padreSupremo;

}

Trie::~Trie(void){

    this->vaciarContenedores();

    //los clear sgtes, son necesarios???
    RAIZ->contenedor->clear();
    RAIZ->contenedorParcial->clear();
    RAIZ->contenedorEntropia->clear();

    delete RAIZ->contenedor;
    delete RAIZ->contenedorParcial;
    delete RAIZ->contenedorEntropia;
    delete RAIZ;
}

int Trie::obtenerCantidadDePalabrasIngresadas(){

    return RAIZ->cantidadTotalDePalabrasEnLaColeccion;

}

int Trie::obtenerCantidadDeDocumentosParseados(){

    return RAIZ->cantidadDeDocumentoParseados;

}

int Trie::obtenerContadorId(){

    return RAIZ->contadorDeId_s;

}

void Trie::incrementarContadorId(){

    RAIZ->contadorDeId_s++;

}


void Trie::aumentarCantidadDePalabrasEnLaColeccion(){

    RAIZ->cantidadTotalDePalabrasEnLaColeccion++;

}

void Trie::aumentarCantidadDeDocParseados(){

    RAIZ->cantidadDeDocumentoParseados++;

}

bool Trie::buscarPalabra(std::string palabra){

	return buscarPalabra(palabra,RAIZ->padreSupremo->hijo);

}

//recibe al hijo de la raiz del arbol
bool Trie::buscarPalabra(std::string palabra,TnodoTrie* NODO){

    //si devuele un nodo, la letra buscada entonces fue hallada
    //entonces la busqueda continua de lo contrario quiere decir que no se halla alguna de
    //las letras que forman la palabra buscada, la busqueda pincha
    TnodoTrie* nodoSiguiente=buscarLetra(palabra[0],NODO);

    if(nodoSiguiente){
        //si no estoy analizando la ultima letra de la palabra buscada
       if((palabra.size()>1) ){

            palabra=palabra.substr(1,palabra.size()-1);
            return buscarPalabra(palabra,nodoSiguiente->hijo);

       }else{
            //despues cambiar esta parte el operador ternario
            if(nodoSiguiente->infoArchivo){
                return true;
            }else{
                return false;
            }
       }
    }
    else{
        //ENTRO ACA SI LA LETRA QUE SE ESTABA BUSCANDO NO SE ENCUENTRA EN LA LISTA
        return false;
    }


}

TnodoTrie* Trie::buscarLetra(char letraBuscada, TnodoTrie* NODO){
    //cadena incompleta
    if(NODO->letra==FINAL_DE_PALABRA){

        return NULL;
    }
    //primer letra del Nodo es la que busco
    else if (NODO->letra==letraBuscada){
        return NODO;
    }

    //si la letra que entra es mas chica que las que ya estan
    else if (NODO->letra>letraBuscada){

        return NULL;
    }

    TnodoTrie* nodoActual=NODO->hermano;

	while(!(nodoActual==NULL)){

		if(nodoActual->letra==letraBuscada){
			return nodoActual;

		}
		//BUSCO EN EL SGTE NODO
		nodoActual=nodoActual->hermano;
	}
	return NULL;
}


//parte de busqueda

std::vector<TnodoData*>* Trie::buscarPalabrasDelDocParseado_INI(){

	//solucion parcial al problema del heap, mejora busqeuda, pero necesita memori innecesaria
	//despues controlar con un if si es NECESARIO O NO EL RESIZE, PROVISIRIO
	RAIZ->contenedorParcial->resize(this->obtenerContadorId());

    buscarPalabrasDelDocParseado(RAIZ->padreSupremo->hijo,RAIZ->contenedorParcial);

    return RAIZ->contenedorParcial;

}

void Trie::buscarPalabrasDelDocParseado(TnodoTrie* NODO,std::vector<TnodoData*>* contenedorIdFreq ){

    if(NODO){
        if(NODO->flagParser){
            //pongo en cero para que posteriores parseadas no lo reconozcan salvo que forme parte de palabras de la
            //correspondinete parseada
            NODO->flagParser=0;
            if ((NODO->infoArchivo!=NULL) && (NODO->infoArchivo->ocurrenciasEnElDocActual > 0) ){
                contenedorIdFreq->at(NODO->infoArchivo->id) = NODO->infoArchivo ;

            }

            buscarPalabrasDelDocParseado(NODO->hijo,contenedorIdFreq);
            buscarPalabrasDelDocParseado(NODO->hermano,contenedorIdFreq);
        }
        else{

            buscarPalabrasDelDocParseado(NODO->hermano,contenedorIdFreq);

        }
    }
}


void Trie::vaciarContenedorParcial(){

    for(unsigned int i=0;i<RAIZ->contenedorParcial->size();i++){
        RAIZ->contenedorParcial->at(i)=NULL;
    }
}

void Trie::inicializarFrecuenciasLocales(){

	for(unsigned int i=0; i<RAIZ->contenedorParcial->size();i++ ){
		if(RAIZ->contenedorParcial->at(i)!=NULL){
			RAIZ->contenedorParcial->at(i)->ocurrenciasEnElDocActual=0;
		}
	}

}

std::vector<TacumEntropia*>* Trie::exportarDatosParaEntropia_INI(){

	this->RAIZ->contenedorEntropia->resize(this->obtenerContadorId());

	this->exportarDatosParaEntropia(this->RAIZ->contenedorEntropia, this->RAIZ->padreSupremo->hijo);

	return this->RAIZ->contenedorEntropia;

}

void Trie::exportarDatosParaEntropia(std::vector<TacumEntropia*>* contenedorEntropia,TnodoTrie* NODO){
	//condicion de corte
	if(NODO){
	            if(NODO->infoArchivo){ //si este nodo no esta vacio quiere decir que corresponde al final de una palabra

	            	TacumEntropia* acumEntropia = new TacumEntropia();

	            	acumEntropia->infoTerm = NODO->infoArchivo;
	                acumEntropia->acumEntropia = 0;

	                contenedorEntropia->at( NODO->infoArchivo->id) = acumEntropia;
	            }

	            exportarDatosParaEntropia(contenedorEntropia,NODO->hijo);
	            exportarDatosParaEntropia(contenedorEntropia,NODO->hermano);
	}

}

void Trie::destruirArbol_INI(){

    int cantidadDeNodos=0;

    destruirArbol(RAIZ->padreSupremo->hijo,&cantidadDeNodos);

}

void Trie::destruirArbol(TnodoTrie* NODO,int* cantidadDeNodos){

    if(NODO){
        destruirArbol(NODO->hijo,cantidadDeNodos);
        destruirArbol(NODO->hermano,cantidadDeNodos);


        if(NODO->infoArchivo){
            delete NODO->infoArchivo;
            *cantidadDeNodos=*cantidadDeNodos + 1;
        }
        delete NODO;
        (*cantidadDeNodos)++;
    }
}

void Trie::vaciarContenedores(){

    for(unsigned int i=0;i<this->RAIZ->contenedor->size();i++){
        delete this->RAIZ->contenedor->at(i);
    }

    for(unsigned int i=0;i<this->RAIZ->contenedorParcial->size();i++){
        delete this->RAIZ->contenedorParcial->at(i);
    }

    for(unsigned int i=0;i<this->RAIZ->contenedorEntropia->size();i++){
        delete this->RAIZ->contenedorEntropia->at(i);
    }

}

void Trie::persistirPalabrasContenedor(std::ofstream* salida){

    for(unsigned int i=0; i<RAIZ->contenedor->size();i++){
        //si no esta vacio
        if(RAIZ->contenedor->at(i)){
            *salida <<*RAIZ->contenedor->at(i)->id <<"  "<<RAIZ->contenedor->at(i)->palabra<<std::endl;
        }
    }
}

void Trie::persistirPalabras_INI(std::ofstream* salida, std::ofstream* offsetLexico){

	std::string cadenaParcialDePalabras;

    cadenaParcialDePalabras.clear();

    int offsetL=0;

    persistirPalabras(RAIZ->padreSupremo->hijo,salida,offsetLexico,&offsetL,cadenaParcialDePalabras);
}

void Trie::persistirPalabras(TnodoTrie* NODO, std::ofstream* salida,std::ofstream* offsetLexico,int* offset,std::string palabra){

        if(NODO){

            palabra= palabra+NODO->letra;
            if(NODO->infoArchivo){ //si este nodo no esta vacio quiere decir que corresponde al final de una palabra

                char tamanio = sprintf(buffer,"%d",NODO->infoArchivo->id);
                *salida<<palabra<<" "<<buffer<<" ";
                *offsetLexico<<*offset<<std::endl;

				//actualizo offset
               *offset += palabra.size() + 1 + (int)tamanio + 1; //el offset contiene el tamaño del string, del string id ,y dos \b

            }
            persistirPalabras(NODO->hijo,salida,offsetLexico,offset,palabra);
            palabra.resize(palabra.size()-1);
            persistirPalabras(NODO->hermano,salida,offsetLexico,offset,palabra);
        }
}


void Trie::insertarPalabra(std::string palabra){


    insertarPalabra(palabra,this->RAIZ->padreSupremo);

    this->aumentarCantidadDePalabrasEnLaColeccion();


}

void Trie::insertarPalabra(std::string palabra,TnodoTrie* padre){

	//condicion de corte
	if(palabra.size()==0){
		//si se inserto toda la palabra y no esta marcado el fin de palabra. inicializo nodo data, acutaliza contadores
		if(padre->infoArchivo==NULL){
			padre->infoArchivo= new TnodoData();
			padre->infoArchivo->ocurrenciasEnElDocActual=0;
			padre->infoArchivo->ocurrenciasEnLaColeccion=0;
			padre->infoArchivo->id = this->obtenerContadorId();

		    this->incrementarContadorId();
		}
		padre->infoArchivo->ocurrenciasEnElDocActual++;
		padre->infoArchivo->ocurrenciasEnLaColeccion++;

	}else{//sepan disculpar esta parte va a seguir siendo un quilombo, estoy manipulando una lista a mano

		//si el hijo esta vacio entra letra nomas
		if(padre->hijo==NULL){

		//	std::cout<<"entrando en nodo vacio, se inserto letra: "<<palabra[0]<<std::endl;

			padre->hijo = new TnodoTrie();
			this->inicializarNodo(padre->hijo);
			padre->hijo->letra = palabra.at(0);
			padre->hijo->flagParser = 1;

			insertarPalabra(palabra.substr(1),padre->hijo);


		}else if ( padre->hijo->letra == palabra.at(0) ){//si la letra que va a entrar ya esta

			//std::cout<<"entrando en nodo existentes"<<std::endl;
			//std::cout<<""<<padre->hijo->letra<<" igual a: "<<palabra[0]<<std::endl;

			padre->hijo->flagParser = 1;
			insertarPalabra(palabra.substr(1),padre->hijo);

		}else if (padre->hijo->letra > palabra.at(0)){ //si debo cambiar el comienzo de la lista

			//std::cout<<"cambiando principio de la,letra: "<<padre->hijo->letra<<" mayor a: "<<palabra[0]<<std::endl;

			TnodoTrie* aux = padre->hijo;

			padre->hijo = new TnodoTrie();
			this->inicializarNodo(padre->hijo);
			padre->hijo->letra = palabra.at(0);
			padre->hijo->flagParser = 1;

			padre->hijo->hermano = aux;
			insertarPalabra(palabra.substr(1),padre->hijo);

		}else { //si no esta vacio, o no es la misma letra, o no va antes del principio de la lista, debo buscar lugar dentro
				//de la misma
			//std::cout<<"buscando lugar en la lista"<<std::endl;

			//si la lista tiene mas de un elemento
			if(padre->hijo->hermano){
				bool insertarAlFinal = true;

				TnodoTrie* actual = padre->hijo->hermano;
				TnodoTrie* anterior = padre->hijo;
				//std::cout<<"analizando anterior "<<anterior->letra<<" entrando: "<<palabra.at(0)<<" posterior"<< actual->letra<<std::endl;

				while(actual && insertarAlFinal){

					if(actual->letra == palabra.at(0)){ //si encunetro una letra igual a la que quiero ingresar, en el medio de la lista paso derecho
						//std::cout<<"encontre letra igual que la mia, paso no mas : "<<actual->letra<<" igual a: "<<palabra[0]<<std::endl;
						insertarAlFinal = false;
						actual->flagParser=1;
						insertarPalabra(palabra.substr(1),actual);
					}

					else if( actual->letra > palabra.at(0) ){
						//std::cout<<"insertando en el medio de : "<<anterior->letra<<"  "<<palabra.at(0)<<" y "<<actual->letra<<std::endl;

						TnodoTrie* aux = actual;

						anterior->hermano = new TnodoTrie();

						this->inicializarNodo(anterior->hermano);

						anterior->hermano->letra = palabra.at(0);
						anterior->hermano->flagParser = 1;
						anterior->hermano->hermano = aux;

						insertarAlFinal = false;
						insertarPalabra(palabra.substr(1),anterior->hermano);
					}
					else{
						anterior = actual;
						actual = actual->hermano;
					}
				}

                //si se llega a este if, anterior queda con el valor del ultimo elemento de la lista
				if(insertarAlFinal==true){
					//std::cout<<"inserte al final porque soy la mayor de todas en la lista "<<palabra.at(0)<<std::endl;
					anterior->hermano = new TnodoTrie();
					this->inicializarNodo(anterior->hermano);
					anterior->hermano->letra = palabra.at(0);
					anterior->hermano->flagParser=1;

					insertarPalabra(palabra.substr(1),anterior->hermano);
				}

			}else{ //si la lista solo tiene un elemento, inserto al lado del mismo la letra entrante
				//std::cout<<"la lista tiene una sola letra "<<padre->hijo->letra<<" menor a: "<<palabra[0]<<std::endl;

				padre->hijo->hermano = new TnodoTrie();
				this->inicializarNodo(padre->hijo->hermano);

				padre->hijo->hermano->letra = palabra.at(0);
				padre->hijo->hermano->flagParser = 1;

				insertarPalabra(palabra.substr(1),padre->hijo->hermano);
			}
		}
	}
}

void Trie::recorrer(){

    std::ofstream salida;
    salida.open("contenidoTrie.txt");

	std::string palabra="";

	recorrer(RAIZ->padreSupremo->hijo,palabra,&salida);

	salida<<"IDs: "<<obtenerContadorId()<<std::endl;
	salida.close();
}

void Trie::recorrer(TnodoTrie* NODO,std::string palabra,std::ofstream* salida){

	if(NODO){

            palabra = palabra + NODO->letra;
            if(NODO->infoArchivo){ //si este nodo no esta vacio quiere decir que corresponde al final de una palabra
            	*salida<<palabra<<" ID: "<<NODO->infoArchivo->id<<std::endl;
            }
            recorrer(NODO->hijo,palabra,salida);
            palabra.resize(palabra.size()-1);
            recorrer(NODO->hermano,palabra,salida);
	}

}


