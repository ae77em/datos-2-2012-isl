#include "Trie.h"
#include <iostream>
#include <string>

void Trie::inicializarRaiz(){

    this->RAIZ=new TnodoPrincipalTrie;
    this->RAIZ->cantidadTotalDePalabrasEnLaColeccion=0;
    this->RAIZ->contadorDeId_s=0;
    this->RAIZ->cantidadDeDocumentoParseados=0;
    this->RAIZ->contenedor = new vector<TnodoTerminoId*>;
    this->RAIZ->contenedorParcial = new vector<TnodoData*>;
    this->RAIZ->contenedorEntropia = new vector<TacumEntropia*>;

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

    TnodoTrie* HIJO=new TnodoTrie;

    inicializarNodo(HIJO);

    RAIZ->hijo=HIJO;

}

Trie::~Trie(void){

    cout<<"DESTRUCTOR TRIE"<<endl;

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

void Trie::insertarPalabraEnRaiz(std::string palabra,int* direccion){


    TnodoTrie* nodoAux=insertarPalabra(palabra, RAIZ->hijo,direccion);

    if(nodoAux){
        RAIZ->hijo=nodoAux;
    }
    //cada vez que ingreso una palabra aumento el contador
    this->aumentarCantidadDePalabrasEnLaColeccion();
}


TnodoTrie* Trie::insertarPalabra(std::string palabra, TnodoTrie* NODO,int* direccion){

    //flga que indica al salir al volver si hay que modificar principio de la lista
    short int modificoPrincipioDeLista=0;

    TnodoTrie* HijoACambiar=buscarLugar(palabra[0],NODO,&modificoPrincipioDeLista);

    if(palabra.size()==1){
        //si es la primera vez que se inserta la letra se inicializai el nodo
        if(HijoACambiar->infoArchivo==NULL){

            HijoACambiar->infoArchivo= new TnodoData;
            HijoACambiar->infoArchivo->ocurrenciasEnElDocActual=0;
            HijoACambiar->infoArchivo->ocurrenciasEnLaColeccion=0;
            HijoACambiar->infoArchivo->id = this->obtenerContadorId();

            this->incrementarContadorId();

        }

        HijoACambiar->infoArchivo->ocurrenciasEnElDocActual++;
        HijoACambiar->infoArchivo->ocurrenciasEnLaColeccion++;
    }

    string palabraAux= palabra.substr(1,palabra.size()-1);

    TnodoTrie* NodoAInsertarPorLasDudas=NULL;
    //condicion de corte
    if(palabraAux.size()>0){
            NodoAInsertarPorLasDudas= insertarPalabra(palabraAux,HijoACambiar->hijo,direccion);
    }
    //si se modifico el comienzo de la lista lo actualizo el puntero al comienzo de la misma
    if(NodoAInsertarPorLasDudas){
        HijoACambiar->hijo=NodoAInsertarPorLasDudas;
    }

    if(modificoPrincipioDeLista){
        return HijoACambiar;
    }
    else{
        return NULL;
    }

}

TnodoTrie* Trie::buscarLugar(char letraEntrante, TnodoTrie* primerNodo,short int* FLAG){


    if(primerNodo->letra==FINAL_DE_PALABRA){
        TnodoTrie* nodoHijo= new TnodoTrie;

        inicializarNodo(nodoHijo);

        primerNodo->hijo=nodoHijo;
        primerNodo->letra=letraEntrante;
        primerNodo->flagParser=1;
        return primerNodo;
    }


    if (primerNodo->letra==letraEntrante){
        primerNodo->flagParser=1;
        return primerNodo;
    }

    //si la letra que entra es mas chica que las que ya estan
    if (primerNodo->letra>letraEntrante){

        *FLAG=1;

        TnodoTrie* nodoEntrante= new TnodoTrie ;
        TnodoTrie* nuevoNodoHijo= new TnodoTrie;

        inicializarNodo(nuevoNodoHijo);
        inicializarNodo(nodoEntrante);

        nodoEntrante->letra=letraEntrante;
        nodoEntrante->flagParser=1;
        nodoEntrante->hijo=nuevoNodoHijo;
        nodoEntrante->hermano=primerNodo;

        return nodoEntrante;
    }

    if (primerNodo->letra<letraEntrante){

        TnodoTrie* nodoEntrante= new TnodoTrie;
        TnodoTrie* nuevoNodoHijo= new TnodoTrie;

        inicializarNodo(nuevoNodoHijo);
        inicializarNodo(nodoEntrante);

        if(primerNodo->hermano==NULL){

            nodoEntrante->letra=letraEntrante;
            nodoEntrante->flagParser=1;
            nodoEntrante->hijo=nuevoNodoHijo;

            primerNodo->hermano=nodoEntrante;

            return nodoEntrante;

        }

        else {

            TnodoTrie* nodoActual= primerNodo->hermano;

            TnodoTrie* nodoAnterior=primerNodo;

            while(nodoActual){

                if(nodoActual->letra==letraEntrante){

                    nodoActual->flagParser=1;

                    return nodoActual;

                }
                if(nodoActual->letra>letraEntrante){

                    nodoEntrante->letra=letraEntrante;
                    nodoEntrante->hijo=nuevoNodoHijo;
                    nodoEntrante->flagParser=1;
                    nodoEntrante->hermano=nodoActual;
                    nodoAnterior->hermano=nodoEntrante;
                    return nodoEntrante;
                }
                //si el que sgue es el ultimo
                nodoAnterior=nodoActual;
                nodoActual=nodoActual->hermano;

            }
            //si salgo del while quiere decir que la letra que quiero ingresar a mayor a todas

            nodoAnterior->hermano=nodoEntrante;

            nodoEntrante->letra=letraEntrante;
            nodoEntrante->flagParser=1;
            nodoEntrante->hijo=nuevoNodoHijo;

            return nodoEntrante;
        }


    }

    return NULL;
}

//////////************************************
bool Trie::buscarPalabra(string palabra){

   return buscarPalabra(palabra,RAIZ->hijo);

}

//recibe al hijo de la raiz del arbol
bool Trie::buscarPalabra(string palabra,TnodoTrie* NODO){

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

    else if (NODO->letra<letraBuscada){


            TnodoTrie* nodoActual=NODO->hermano;
            TnodoTrie* nodoAnterior=NODO;

            while(!(nodoActual==NULL)){

                if(nodoActual->letra==letraBuscada){
                    return nodoActual;

                }
                //BUSCO EN EL SGTE NODO
                nodoAnterior=nodoActual;
                nodoActual=nodoActual->hermano;
            }
            return NULL;
    }

}


//parte de busqueda

vector<TnodoData*>* Trie::buscarPalabrasDelDocParseado_INI(){

	//solucion parcial al problema del heap, mejora busqeuda, pero necesita memori innecesaria
	//despues controlar con un if si es NECESARIO O NO EL RESIZE, PROVISIRIO
	RAIZ->contenedorParcial->resize(this->obtenerContadorId());

    buscarPalabrasDelDocParseado(RAIZ->hijo,RAIZ->contenedorParcial);

    return RAIZ->contenedorParcial;

}

void Trie::buscarPalabrasDelDocParseado(TnodoTrie* NODO,vector<TnodoData*>* contenedorIdFreq ){

    if(NODO){
        if(NODO->flagParser){

            //pongo en cero para que posteriores parseadas no lo reconozcan salvo que forme parte de palabras de la
            //correspondinete parseada
            NODO->flagParser=0;

            if(NODO->infoArchivo && NODO->infoArchivo->ocurrenciasEnElDocActual){
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


void Trie::persistirPalabras_INI(fstream* salida){

    string cadenaParcialDePalabras;

    cadenaParcialDePalabras.clear();

    persistirPalabras(RAIZ->hijo,salida,cadenaParcialDePalabras);


}

void Trie::persistirPalabras(TnodoTrie* NODO,fstream* salida,string palabra){

        if(NODO){

            palabra= palabra+NODO->letra;

            if(NODO->infoArchivo){ //si este nodo no esta vacio quiere decir que corresponde al final de una palabra

                *salida<<palabra<<"  id: "<<NODO->infoArchivo->id<<endl;

            }

            persistirPalabras(NODO->hijo,salida,palabra);
            palabra.resize(palabra.size()-1);

            persistirPalabras(NODO->hermano,salida,palabra);
        }

}


//se usa al final de la indexacion, vuelca todo en un vector, para facilitar la actualizacion de los id�s
// luego de la eliminaicon de las stopwords
vector<TnodoTerminoId*>* Trie::exportarPalabrasContenedor_INI(){

    RAIZ->contenedor->resize(this->obtenerContadorId()); //el id arranca desde cero

    string palabraAux = "";

    this->exportarPalabrasContenedor(this->RAIZ->hijo,RAIZ->contenedor,palabraAux);

    return RAIZ->contenedor;

}

//SE USA para volvar la data ID,TERM a un vector,
void Trie::exportarPalabrasContenedor(TnodoTrie* NODO ,vector<TnodoTerminoId*>*contenedor, string palabra){

    if(NODO){
            palabra= palabra + NODO->letra;

            if(NODO->infoArchivo){ //si este nodo no esta vacio quiere decir que corresponde al final de una palabra

                TnodoTerminoId* terminoId = new TnodoTerminoId;

                terminoId->id = &NODO->infoArchivo->id;
                terminoId->palabra = palabra;

                contenedor->at(*terminoId->id)=terminoId;

            }

            exportarPalabrasContenedor(NODO->hijo,contenedor,palabra);
            palabra.resize(palabra.size()-1);

            exportarPalabrasContenedor(NODO->hermano,contenedor,palabra);
        }
}


void Trie::persistirPalabrasContenedor(fstream* salida){

    for(register unsigned int i=0; i<RAIZ->contenedor->size();i++){
        //si no esta vacio
        if(RAIZ->contenedor->at(i)){
            *salida <<*RAIZ->contenedor->at(i)->id <<"  "<<RAIZ->contenedor->at(i)->palabra<<endl;
        }
    }
}

void Trie::vaciarContenedorParcial(){

    for(register int i=0;i<RAIZ->contenedorParcial->size();i++){
        RAIZ->contenedorParcial->at(i)=NULL;
    }
}

void Trie::inicializarFrecuenciasLocales(){

	for(register unsigned int i=0; i<RAIZ->contenedorParcial->size();i++ ){
		RAIZ->contenedorParcial->at(i)->ocurrenciasEnElDocActual=0;
	}

}

vector<TacumEntropia*>* Trie::exportarDatosParaEntropia_INI(){

	this->RAIZ->contenedorEntropia->resize(this->obtenerContadorId());

	this->exportarDatosParaEntropia(this->RAIZ->contenedorEntropia, this->RAIZ->hijo);

	return this->RAIZ->contenedorEntropia;

}

void Trie::exportarDatosParaEntropia(vector<TacumEntropia*>* contenedorEntropia,TnodoTrie* NODO){
	//condicion de corte
	if(NODO){
	            if(NODO->infoArchivo){ //si este nodo no esta vacio quiere decir que corresponde al final de una palabra

	            	TacumEntropia* acumEntropia = new TacumEntropia;

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

    destruirArbol(RAIZ->hijo,&cantidadDeNodos);

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

    for(register int i=0;i<this->RAIZ->contenedor->size();i++){
        delete this->RAIZ->contenedor->at(i);
    }

    for(register int i=0;i<this->RAIZ->contenedorParcial->size();i++){
        delete this->RAIZ->contenedorParcial->at(i);
    }

    for(register int i=0;i<this->RAIZ->contenedorEntropia->size();i++){
        delete this->RAIZ->contenedorEntropia->at(i);
    }

}
