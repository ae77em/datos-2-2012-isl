#include "trie.h"
#include <iostream>
#include <string>

void Trie::inicializarRaiz(){

    this->RAIZ=new TnodoPrincipalTrie;
    this->RAIZ->cantidadTotalDePalabrasEnLaColeccion=0;
    this->RAIZ->log.open("log.txt",fstream::out);
    this->RAIZ->contadorDeId_s=0;
    this->RAIZ->cantidadDeDocumentoParseados=0;

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

void Trie::aumentarCantidadDePalabrasEnLaColeccion(){

    RAIZ->cantidadTotalDePalabrasEnLaColeccion++;

}

void Trie::insertarPalabraEnRaiz(std::string palabra,int* direccion){


    TnodoTrie* nodoAux=insertarPalabra(palabra, RAIZ->hijo,direccion);

    if(nodoAux){
        RAIZ->hijo=nodoAux;
    }

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
            HijoACambiar->infoArchivo->ocurrenciasEnDocDistintos=0;
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
        // RAIZ->log<<"\nYosoy el padre: "<<NODO->letra<<" de: "<<NodoAInsertarPorLasDudas->letra<<endl;
        HijoACambiar->hijo=NodoAInsertarPorLasDudas;
    }

    if(modificoPrincipioDeLista){
        // RAIZ->log<<"\ndevolcia hijo a cambvivar con letra: "<<HijoACambiar->letra<<endl;
        return HijoACambiar;
    }
    else{
        return NULL;
    }

}

TnodoTrie* Trie::buscarLugar(char letraEntrante, TnodoTrie* primerNodo,short int* FLAG){

    //RAIZ->log<<"\nSOY LA PRIMER LETRA DE LA LISTA: "<<primerNodo->letra<<endl;

    if(primerNodo->letra==FINAL_DE_PALABRA){
       // RAIZ->log<< "PrimerNodoEstabaVacio"<<endl;
        //RAIZ->log<<"entra la letra: "<<letraEntrante<<endl;
        TnodoTrie* nodoHijo= new TnodoTrie;

        inicializarNodo(nodoHijo);

        primerNodo->hijo=nodoHijo;
        primerNodo->letra=letraEntrante;
        primerNodo->flagParser=1;
        return primerNodo;
    }


    if (primerNodo->letra==letraEntrante){
        //RAIZ->log<< "PrimerLetraEsIGualaMi="<< letraEntrante<<"= "<<primerNodo->letra<<endl;
        primerNodo->flagParser=1;
        return primerNodo;
    }

    //si la letra que entra es mas chica que las que ya estan
    if (primerNodo->letra>letraEntrante){
        //RAIZ->log<< "DeboIngresarAlPRincipiodeLalistaYa:"<<letraEntrante<<" < "<<primerNodo->letra<<endl;

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
        //RAIZ->log<< "primerLetraEsmenosQueyo ENtro En bucle, la letra es: "<<primerNodo->letra<<" yo soy: "<<letraEntrante<<endl;

        TnodoTrie* nodoEntrante= new TnodoTrie;
        TnodoTrie* nuevoNodoHijo= new TnodoTrie;

        inicializarNodo(nuevoNodoHijo);
        inicializarNodo(nodoEntrante);

        if(primerNodo->hermano==NULL){

          //  RAIZ->log<< "Siguuiente vacio  "<<primerNodo->letra<<" < "<<letraEntrante<<endl;

            nodoEntrante->letra=letraEntrante;
            nodoEntrante->flagParser=1;
            nodoEntrante->hijo=nuevoNodoHijo;

            primerNodo->hermano=nodoEntrante;

            return nodoEntrante;

        }

        else {
            //RAIZ->log<< "como el primer Hermano no esta vacion entro en bucle\n"<<endl;

            TnodoTrie* nodoActual= primerNodo->hermano;

            TnodoTrie* nodoAnterior=primerNodo;

            while(nodoActual){

                if(nodoActual->letra==letraEntrante){

              //      RAIZ->log<<"la letra de mi hijo es: "<<nodoActual->hijo->letra;
                //    RAIZ->log <<" encontre una letra igual a mi, es la: "<<nodoActual->letra<<" yo soy "<<letraEntrante<<endl;
                    nodoActual->flagParser=1;

                    return nodoActual;

                }
                if(nodoActual->letra>letraEntrante){
                  //  RAIZ->log<<"ACA NUNCA ENTRO";
                    //RAIZ->log<< "me encajo en el medio de"<<nodoAnterior->letra<<" yo soy "<<letraEntrante<<" y mi hermana mayor"<< nodoActual->letra<<endl;

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
            //RAIZ->log<<"llegue al final y no entre, yo soy: "<<letraEntrante<<"mi hermano menor es: "<<nodoAnterior->letra<<endl;

            nodoAnterior->hermano=nodoEntrante;

            nodoEntrante->letra=letraEntrante;
            nodoEntrante->flagParser=1;
            nodoEntrante->hijo=nuevoNodoHijo;

          /*  delete nodoActual;
            delete nodoAnterior;*/
            return nodoEntrante;
        }


    }

}

void Trie::destruirArbol_INI(){

    int cantidadDeNodos=0;

    destruirArbol(RAIZ->hijo,&cantidadDeNodos);

    RAIZ->log<<"se destruyeron: "<<cantidadDeNodos<<" nodos"<<endl;

}


void Trie::destruirArbol(TnodoTrie* NODO,int* cantidadDeNodos){

    if(NODO){
        //RAIZ->log<<NODO->letra;
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

//parte de busqueda

void Trie::buscarPalabrasDeLaParseada_INI(){

    string cadenaQueEscupePalabras;

    cadenaQueEscupePalabras.clear();

    string aux="";
    RAIZ->log<<endl<<endl;
    buscarPalabrasDeLaParseada(RAIZ->hijo,cadenaQueEscupePalabras,aux);
    RAIZ->log<<endl;

}

void Trie::buscarPalabrasDeLaParseada(TnodoTrie* NODO,string palabra,string aux){

    if(NODO){
        if(NODO->flagParser){
            palabra= palabra+NODO->letra;
            //pongo en cero para que posteriores parseadas no lo reconozcan salvo que forme parte de palabras de la
            //correspondinete parseada
            NODO->flagParser=0;

            if(NODO->infoArchivo){
                RAIZ->log<<palabra;
                RAIZ->log<<" FILA: "<<NODO->infoArchivo->id<<endl;
            }

            buscarPalabrasDeLaParseada(NODO->hijo,palabra,aux);
            palabra.resize(palabra.size()-1);

            buscarPalabrasDeLaParseada(NODO->hermano,palabra,aux);
        }
        else{

            buscarPalabrasDeLaParseada(NODO->hermano,palabra,aux);

        }
    }
}



bool Trie::buscarPalabra(string palabra){

    bool encontro=false;

    return encontro=buscarPalabra(palabra,RAIZ->hijo);

}

//recibe al hijo de la raiz del arbol
bool Trie::buscarPalabra(string palabra,TnodoTrie* NODO){

    RAIZ->log<<"LETRA QUE SE ESTA BUSCANDO: "<<palabra[0]<<endl;
    TnodoTrie* nodoSiguiente=buscarLetra(palabra[0],NODO);

    //si devuele un nodo, la letra esta entonces
    //la busqueda continua de lo contrario quiere decir que no se halla alguna de las letras requeridas busqueda pincha
    if(nodoSiguiente){

       string palabraAux=palabra.substr(1,palabra.size()-1);
       if((palabraAux.size()>0) ){
           // RAIZ->log<<"letra que esta por entrar a la sgte busqueda: "<<
             return buscarPalabra(palabraAux,nodoSiguiente->hijo);
       }
    }
    else{
        RAIZ->log<<"fallo en la letra: "<<NODO->letra<<endl;
        return false;
    }

    //si se llago al final de la cadena buscada y esta esta en el arbol
    if(NODO->infoArchivo){
            return true;
    }
    else{
        RAIZ->log<<"esta la subcadena pero no la palabra"<<endl;
    }
}

TnodoTrie* Trie::buscarLetra(char letraBuscada, TnodoTrie* NODO){
    //cadena incompleta
    if(NODO->letra==FINAL_DE_PALABRA){

      //  RAIZ->log <<"dice que el nodo esta vacio"<<endl;
        return NULL;
    }
    //primer letra del Nodo es la que busco
    if (NODO->letra==letraBuscada){
        //RAIZ->log<< "PrimerLetraEsIGualaMi=="<< letraBuscada<<endl;
        return NODO;
    }

    //si la letra que entra es mas chica que las que ya estan
    if (NODO->letra>letraBuscada){
        RAIZ->log<< "letra desigual yo busco una: "<<letraBuscada<<" y es una:  "<<NODO->letra<<endl;

        return NULL;
    }

    if (NODO->letra<letraBuscada){
       // RAIZ->log<< "primerLetraEsmenosQueyo:   "<<NODO->letra<<" ENtro En bucle"<<endl;


            TnodoTrie* nodoActual=NODO->hermano;
            TnodoTrie* nodoAnterior=NODO;

            while(!(nodoActual==NULL)){

                if(nodoActual->letra==letraBuscada){
                  //  RAIZ->log <<"encontre una letra igual a mi, es la: "<<nodoActual->letra<<" yo soy "<<letraBuscada<<endl;
                    return nodoActual;

                }
                //BUSCO EN EL SGTE NODO
                nodoAnterior=nodoActual;
                nodoActual=nodoActual->hermano;
            }
        //    RAIZ->log<<"LLEGUE AL FINAL Y NO ENCONTRE LA LETRA"<<endl;
            return NULL;
    }

}

void Trie::exportarPalabras_INI(fstream* salida){

    string cadenaQueEscupePalabras;

    cadenaQueEscupePalabras.clear();

    exportarPalabras(RAIZ->hijo,salida,cadenaQueEscupePalabras);

    RAIZ->log<<endl<<endl<<"cantidadTotalDePalabrasQueSeIngresaron(no quiere decir distintas): "<<RAIZ->cantidadTotalDePalabrasEnLaColeccion;

    RAIZ->log<<endl<<"estado final del contador de IDs: "<<obtenerContadorId();

    RAIZ->log.close();

}

void Trie::exportarPalabras(TnodoTrie* NODO,fstream* salida,string palabra){

        if(NODO){

            palabra= palabra+NODO->letra;

            if(NODO->infoArchivo){ //si este nodo no esta vacio quiere decir que corresponde al final de una palabra

                RAIZ->log<<palabra;
                RAIZ->log<<"  id:"<<NODO->infoArchivo->id<<"  esta palabra aparecio: ";
                RAIZ->log<<NODO->infoArchivo->ocurrenciasEnLaColeccion<<"  en la coleccion "<<endl;


                *salida<<palabra<<"  id: "<<NODO->infoArchivo->id
                <<endl;

            }

            exportarPalabras(NODO->hijo,salida,palabra);
            palabra.resize(palabra.size()-1);

            exportarPalabras(NODO->hermano,salida,palabra);
        }

}

int Trie::obtenerContadorId(){

    return RAIZ->contadorDeId_s;

}

void Trie::incrementarContadorId(){

    RAIZ->contadorDeId_s++;

}

