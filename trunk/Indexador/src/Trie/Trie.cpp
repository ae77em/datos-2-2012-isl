#include "Trie.h"
#include <iostream>
#include <fstream>
#include <string>
#include <sys/stat.h>
#include <sys/types.h>
//#include <cdirect>

void Trie::inicializarNodo(TnodoTrie* NODO){

    NODO->letra=64;
    NODO->hermano=NULL;
    NODO->hijo=NULL;
    NODO->infoArchivo=NULL;
    NODO->flagParser=0;

}
Trie::Trie(){

    RAIZ=new TnodoTrie;
    TnodoTrie* HIJO=new TnodoTrie;
    RAIZ->contadorDeFila=0;

    inicializarNodo(RAIZ);
    inicializarNodo(HIJO);

    RAIZ->hijo=HIJO;
}

Trie::~Trie(){
	destruirArbol_INI();
}

void Trie::insertarPalabra(std::string palabra,int* direccion){

    //cout<<"\nPALABRA A INGRESAR: "<< palabra<<endl;

    TnodoTrie* nodoAux= new TnodoTrie;
    nodoAux = insertarPalabra(palabra, RAIZ->hijo,direccion);

    if(nodoAux){
        RAIZ->hijo=nodoAux;
    }

}


TnodoTrie* Trie::insertarPalabra(std::string palabra, TnodoTrie* NODO,int* direccion){
        //flga que indica al salir al volver si hay que modificar principio de la lista
        short int modificoPrincipioDeLista=0;

        TnodoTrie* HijoACambiar=buscarLugar(palabra[0],NODO,&modificoPrincipioDeLista);

        //cout<<HijoACambiar->letra<<endl;
       // cout<<"\nMODIFICO PRINCIPIO:  "<< modificoPrincipioDeLista<< endl;
        if(palabra.size()==1){
            //si es la primera vez que se inserta la letra se inicializai el nodo
            if(HijoACambiar->infoArchivo==NULL){

                HijoACambiar->infoArchivo = new TnodoData;
                HijoACambiar->infoArchivo->ocurrenciasEnDocDistintos=0;
                HijoACambiar->infoArchivo->ocurrenciasEnElDocActual=0;
                HijoACambiar->infoArchivo->ocurrenciasEnLaColeccion=0;
                HijoACambiar->infoArchivo->nroDeFila=0;
            }

            HijoACambiar->infoArchivo->ocurrenciasEnElDocActual++;
            //cout<<"mi frecuencia es: "<<HijoACambiar->infoArchivo->ocurrenciasEnElDocActual<<endl;
        }

        string palabraAux= palabra.substr(1,palabra.size()-1);

        //cout<<"\nDEBERIA DE SER UNA: "<<palabra[0]<<" y soy una: "<<HijoACambiar->letra<<endl<<endl;

        // captura el nodo que modificaria el principio de la lista del nivel anterior
        TnodoTrie* NodoAInsertarPorLasDudas=NULL;
        //condicion de corte
        if(palabraAux.size()>0){
             NodoAInsertarPorLasDudas= insertarPalabra(palabraAux,HijoACambiar->hijo,direccion);
        }
        //si se modifico el comienzo de la lista lo actualizo el puntero al comienzo de la misma
        if(NodoAInsertarPorLasDudas){
           // cout<<"\nYosoy el padre: "<<NODO->letra<<" de: "<<NodoAInsertarPorLasDudas->letra<<endl;
            HijoACambiar->hijo=NodoAInsertarPorLasDudas;
        }

        if(modificoPrincipioDeLista){
           // cout<<"\ndevolcia hijo a cambvivar con letra: "<<HijoACambiar->letra<<endl;
            return HijoACambiar;
        }
        else{
            return NULL;
        }
}


/* si la letra a ingresar es menor que la primera devuelve el nodo ingresante, sino NULL*/

TnodoTrie* Trie::buscarLugar(char letraEntrante, TnodoTrie* primerNodo,short int* FLAG){

    if(primerNodo->letra==64){
       // cout<< "PrimerNodoEstabaVacio"<<endl;
        //cout<<"entra la letra: "<<letraEntrante<<endl;
        TnodoTrie* nodoHijo= new TnodoTrie;

        inicializarNodo(nodoHijo);

        primerNodo->hijo=nodoHijo;
        primerNodo->letra=letraEntrante;
        primerNodo->flagParser=1;
        return primerNodo;
    }


    if (primerNodo->letra==letraEntrante){
        //cout<< "PrimerLetraEsIGualaMi="<< letraEntrante<<"= "<<primerNodo->letra<<endl;
        primerNodo->flagParser=1;
        return primerNodo;
    }

    //si la letra que entra es mas chica que las que ya estan
    if (primerNodo->letra>letraEntrante){
        //cout<< "DeboIngresarAlPRincipiodeLalistaYa:"<<letraEntrante<<" < "<<primerNodo->letra<<endl;

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

        delete nodoEntrante;
        delete nuevoNodoHijo;
    }

    if (primerNodo->letra<letraEntrante){
        //cout<< "primerLetraEsmenosQueyo ENtro En bucle, la letra es: "<<primerNodo->letra<<" yo soy: "<<letraEntrante<<endl;

        TnodoTrie* nodoEntrante = new TnodoTrie;
        TnodoTrie* nuevoNodoHijo = new TnodoTrie;

        inicializarNodo(nuevoNodoHijo);
        inicializarNodo(nodoEntrante);

        if(primerNodo->hermano==NULL){

          //  cout<< "Siguuiente vacio  "<<primerNodo->letra<<" < "<<letraEntrante<<endl;

            nodoEntrante->letra=letraEntrante;
            nodoEntrante->flagParser=1;
            nodoEntrante->hijo=nuevoNodoHijo;

            primerNodo->hermano=nodoEntrante;

            return nodoEntrante;
        } else {
            //cout<< "como el primer Hermano no esta vacion entro en bucle\n"<<endl;

            TnodoTrie* nodoActual= primerNodo->hermano;

            TnodoTrie* nodoAnterior=primerNodo;

            while(nodoActual){

                if(nodoActual->letra==letraEntrante){

              //      cout<<"la letra de mi hijo es: "<<nodoActual->hijo->letra;
                //    cout <<" encontre una letra igual a mi, es la: "<<nodoActual->letra<<" yo soy "<<letraEntrante<<endl;
                    nodoActual->flagParser=1;

                    return nodoActual;
                    delete nodoActual;
                }
                if(nodoActual->letra>letraEntrante){
                  //  cout<<"ACA NUNCA ENTRO";
                    //cout<< "me encajo en el medio de"<<nodoAnterior->letra<<" yo soy "<<letraEntrante<<" y mi hermana mayor"<< nodoActual->letra<<endl;

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
            //cout<<"llegue al final y no entre, yo soy: "<<letraEntrante<<"mi hermano menor es: "<<nodoAnterior->letra<<endl;

            nodoAnterior->hermano=nodoEntrante;

            nodoEntrante->letra=letraEntrante;
            nodoEntrante->flagParser=1;
            nodoEntrante->hijo=nuevoNodoHijo;

          /*  delete nodoActual;
            delete nodoAnterior;*/
            return nodoEntrante;
            delete nodoActual;
        }
        delete nuevoNodoHijo;
		delete nodoEntrante;
    }
    return NULL;

}

//si el nodo esta vacio


TnodoTrie* Trie::getNodo(){

    return RAIZ;
}

void Trie::destruirArbol_INI(){

   // cout<<"\nDESTRUYENDO ARBOL\n"<<endl;

    int cantidadDeNodos=0;

    destruirArbol(RAIZ->hijo,&cantidadDeNodos);

    //cout<<"se destruyeron: "<<cantidadDeNodos<<" nodos"<<endl;

    delete RAIZ;

}


void Trie::destruirArbol(TnodoTrie* NODO,int* cantidadDeNodos){

    if(NODO){
        //cout<<NODO->letra;
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

    incrementarCantidadDeDocumentos(); // actualizo la cantidad de documentos para la proxima

    buscarPalabrasDeLaParseada(RAIZ->hijo,cadenaQueEscupePalabras,aux,true);

    //cout<<"Matriz luego de la parseada numero "<<indice.cols()<<"\n"<< indice;

}

void Trie::buscarPalabrasDeLaParseada(TnodoTrie* NODO,string palabra,string aux,bool indexar){

    if(NODO){
        if(NODO->flagParser){
            palabra= palabra+NODO->letra;
            //pongo en cero para que posteriores parseadas no lo reconozcan salvo que forme parte de palabras de la
            //correspondinete parseada
            NODO->flagParser=0;

            if(NODO->infoArchivo){

                if(NODO->infoArchivo->nroDeFila==0){
                    RAIZ->contadorDeFila++;
                    NODO->infoArchivo->nroDeFila=RAIZ->contadorDeFila;
                }

                NODO->infoArchivo->ocurrenciasEnDocDistintos++;//indica si la palabra estuvo en la parseada actual

                NODO->infoArchivo->ocurrenciasEnLaColeccion=NODO->infoArchivo->ocurrenciasEnLaColeccion + NODO->infoArchivo->ocurrenciasEnElDocActual;

                unsigned nroDeFila = NODO->infoArchivo->nroDeFila;
                unsigned ocurrenciasEnElDocActual = NODO->infoArchivo->ocurrenciasEnElDocActual;
                unsigned ocurrenciasEnDocDistintos = NODO->infoArchivo->ocurrenciasEnDocDistintos;
                unsigned ocurrenciasEnLaColeccion = NODO->infoArchivo->ocurrenciasEnLaColeccion;


                cout<<"soy la palabra: '"<<palabra<<"' con nro de fila: "<< nroDeFila <<endl<<endl;
                cout<<"esta palabra se repitio en el doc actual: "<< ocurrenciasEnElDocActual <<" veces"<<endl;
                cout<<"esta palabra aparecio en: "<< ocurrenciasEnDocDistintos <<" documentos distintos"<<endl;
                cout<<"esta palabra se repitio en la coleccion: "<< ocurrenciasEnLaColeccion<<" veces\n"<<endl;

                if ( indexar ){
					//inicializo contador para la proxima parseada
					/*if ( indice->rows() < nroDeFila )
						utilidades.cambiarFilas(*indice,nroDeFila);
					if ( indice->cols() < cantidadDeDocumentos )
						utilidades.cambiarColumnas(*indice,cantidadDeDocumentos);*/

					/*unsigned i = nroDeFila - 1;
					unsigned j = cantidadDeDocumentos - 1;*/

					//(*indice)(i,j) = ocurrenciasEnElDocActual; //utilidades.ponderacionLocal( ocurrenciasEnElDocActual );
                }

                NODO->infoArchivo->ocurrenciasEnElDocActual=0;

            }

            buscarPalabrasDeLaParseada(NODO->hijo,palabra,aux,true);
            palabra.resize(palabra.size()-1);

            buscarPalabrasDeLaParseada(NODO->hermano,palabra,aux,true);
        }
        else{

            buscarPalabrasDeLaParseada(NODO->hermano,palabra,aux,true);

        }
    }
}



bool Trie::buscarPalabra(string palabra){

    bool encontro=false;
    unsigned fila;
    return encontro=buscarPalabra(palabra,RAIZ->hijo, fila );

}

bool Trie::buscarPalabra(string palabra, unsigned & nroFila){

    bool encontro=false;

    return encontro=buscarPalabra(palabra,RAIZ->hijo, nroFila );

}

//recibe al hijo de la raiz del arbol
bool Trie::buscarPalabra(string palabra,TnodoTrie* NODO, unsigned & nroFila){

    cout<<"LETRA QUE SE ESTA BUSCANDO: "<<palabra[0]<<endl;
    TnodoTrie* nodoSiguiente=buscarLetra(palabra[0],NODO);

    //si devuele un nodo, la letra esta entonces
    //la busqueda continua de lo contrario quiere decir que no se halla alguna de las letras requeridas busqueda pincha
    if(nodoSiguiente){

       string palabraAux=palabra.substr(1,palabra.size()-1);
       if((palabraAux.size()>0) ){
           // cout<<"letra que esta por entrar a la sgte busqueda: "<<
             return buscarPalabra(palabraAux,nodoSiguiente->hijo,nroFila);
       }
    }
    else{
        cout<<"fallo en la letra: "<<NODO->letra<<endl;
        return false;
    }

    //si se llago al final de la cadena buscada y esta esta en el arbol
    if(NODO->infoArchivo){
    	nroFila = NODO->infoArchivo->nroDeFila; // asi se en que fila estaba
    	return true;
    }
    else{
        cout<<"esta la subcadena pero no la palabra"<<endl;
        return false;
    }
}

TnodoTrie* Trie::buscarLetra(char letraBuscada, TnodoTrie* NODO){
    //cadena incompleta
    if(NODO->letra==0){

      //  cout <<"dice que el nodo esta vacio"<<endl;
        return NULL;
    }
    //primer letra del Nodo es la que busco
    if (NODO->letra==letraBuscada){
        //cout<< "PrimerLetraEsIGualaMi=="<< letraBuscada<<endl;
        return NODO;
    }

    //if(NODO->)


    //si la letra que entra es mas chica que las que ya estan
    if (NODO->letra>letraBuscada){
        cout<< "letra desigual yo busco una: "<<letraBuscada<<" y es una:  "<<NODO->letra<<endl;

        return NULL;
    }

    if (NODO->letra<letraBuscada){
       // cout<< "primerLetraEsmenosQueyo:   "<<NODO->letra<<" ENtro En bucle"<<endl;
            TnodoTrie* nodoActual=NODO->hermano;
            TnodoTrie* nodoAnterior=NODO;
            //int llegoAlFinal=0;

            while(!(nodoActual==NULL)){

                if(nodoActual->letra==letraBuscada){
                  //  cout <<"encontre una letra igual a mi, es la: "<<nodoActual->letra<<" yo soy "<<letraBuscada<<endl;
                    return nodoActual;
                }
                //BUSCO EN EL SGTE NODO
                nodoAnterior=nodoActual;
                nodoActual=nodoActual->hermano;
            }
        //    cout<<"LLEGUE AL FINAL Y NO ENCONTRE LA LETRA"<<endl;
            return NULL;
    }
    return NULL;

}

void Trie::buscarPalabrasParaGuardar_INI( string & arch ){

    string cadenaQueEscupePalabras;

    cadenaQueEscupePalabras.clear();

    string aux="";

    incrementarCantidadDeDocumentos(); // actualizo la cantidad de documentos para la proxima

    buscarPalabrasParaGuardar(RAIZ->hijo,cadenaQueEscupePalabras,aux,arch);

    //cout<<"Matriz luego de la parseada numero "<<indice.cols()<<"\n"<< indice;

}

void Trie::buscarPalabrasParaGuardar(TnodoTrie* NODO,string palabra,string aux,string & archivo){

	if(NODO){
        if(NODO->flagParser){
            palabra= palabra+NODO->letra;
            //pongo en cero para que posteriores parseadas no lo reconozcan salvo que forme parte de palabras de la
            //correspondinete parseada
            NODO->flagParser=0;

            if(NODO->infoArchivo){

                if(NODO->infoArchivo->nroDeFila==0){
                    RAIZ->contadorDeFila++;
                    NODO->infoArchivo->nroDeFila=RAIZ->contadorDeFila;
                }

                NODO->infoArchivo->ocurrenciasEnDocDistintos++;//indica si la palabra estuvo en la parseada actual

                NODO->infoArchivo->ocurrenciasEnLaColeccion=NODO->infoArchivo->ocurrenciasEnLaColeccion + NODO->infoArchivo->ocurrenciasEnElDocActual;

                unsigned nroDeFila = NODO->infoArchivo->nroDeFila;
                unsigned ocurrenciasEnLaColeccion = NODO->infoArchivo->ocurrenciasEnLaColeccion;

                // aca guardo las palabras en el archivo
                string path = "Palabras/" + archivo;

            	//mkdir( path.c_str(), S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH);
                mkdir( path.c_str(),S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH);

               	ofstream fsalida(path.c_str(),ios::out/* | ios::binary*/);
               	fsalida.open(path.c_str(),ios::out);
               	//cout << path;
               	fsalida << "\n[" << palabra << "]";
               	fsalida << "," << nroDeFila;
               	fsalida << "," << ocurrenciasEnLaColeccion << "]";

               	fsalida.close();

            }

            buscarPalabrasParaGuardar(NODO->hijo,palabra,aux,archivo);
            palabra.resize(palabra.size()-1);

            buscarPalabrasParaGuardar(NODO->hermano,palabra,aux,archivo);
        }
        else{

            buscarPalabrasParaGuardar(NODO->hermano,palabra,aux,archivo);

        }
    }
}

