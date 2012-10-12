#include "trie.h"
#include <iostream>
#include <string>

void Trie::inicializarRaiz() {
    this->RAIZ=new TnodoPrincipalTrie;
    this->RAIZ->cantidadTotalDePalabrasEnLaColeccion=0;
    this->RAIZ->log.open("log.txt",fstream::out);
    this->RAIZ->contadorDeId_s=0;
    this->RAIZ->cantidadDeDocumentoParseados=0;
    this->RAIZ->contenedor = new vector<TnodoTerminoId*>;
}

void Trie::inicializarNodo(TnodoTrie* NODO) {
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

void Trie::aumentarCantidadDePalabrasEnLaColeccion() {
    RAIZ->cantidadTotalDePalabrasEnLaColeccion++;
}

void Trie::insertarPalabraEnRaiz(std::string palabra,int* direccion) {
    TnodoTrie* nodoAux=insertarPalabra(palabra, RAIZ->hijo,direccion);

    if(nodoAux){
        RAIZ->hijo=nodoAux;
    }
    //cada vez que ingreso una palabra aumento el contador
    this->aumentarCantidadDePalabrasEnLaColeccion();
}

TnodoTrie* Trie::insertarPalabra(std::string palabra, TnodoTrie* NODO,int* direccion) {
    //flga que indica al salir al volver si hay que modificar principio de la lista
    short int modificoPrincipioDeLista=0;

    TnodoTrie* HijoACambiar=buscarLugar(palabra[0],NODO,&modificoPrincipioDeLista);

    if(palabra.size()==1) {
        //si es la primera vez que se inserta la letra se inicializai el nodo
        if(HijoACambiar->infoArchivo==NULL){

            HijoACambiar->infoArchivo= new TnodoData;
            HijoACambiar->infoArchivo->ocurrenciasEnElDocActual=0;
            HijoACambiar->infoArchivo->id = this->obtenerContadorId();

            this->incrementarContadorId();

        }

        HijoACambiar->infoArchivo->ocurrenciasEnElDocActual++;
    }

    string palabraAux= palabra.substr(1,palabra.size()-1);

    TnodoTrie* NodoAInsertarPorLasDudas=NULL;
    //condicion de corte
    if(palabraAux.size()>0){
            NodoAInsertarPorLasDudas= insertarPalabra(palabraAux,HijoACambiar->hijo,direccion);
    }
    //si se modifico el comienzo de la lista lo actualizo el puntero al comienzo de la misma
    if(NodoAInsertarPorLasDudas){
        // //RAIZ->log<<"\nYosoy el padre: "<<NODO->letra<<" de: "<<NodoAInsertarPorLasDudas->letra<<endl;
        HijoACambiar->hijo=NodoAInsertarPorLasDudas;
    }

    if(modificoPrincipioDeLista){
        // //RAIZ->log<<"\ndevolcia hijo a cambvivar con letra: "<<HijoACambiar->letra<<endl;
        return HijoACambiar;
    }
    else{
        return NULL;
    }

}

TnodoTrie* Trie::buscarLugar(char letraEntrante, TnodoTrie* primerNodo,short int* FLAG) {
    ////RAIZ->log<<"\nSOY LA PRIMER LETRA DE LA LISTA: "<<primerNodo->letra<<endl;

    if(primerNodo->letra==FINAL_DE_PALABRA){
       // //RAIZ->log<< "PrimerNodoEstabaVacio"<<endl;
        ////RAIZ->log<<"entra la letra: "<<letraEntrante<<endl;
        TnodoTrie* nodoHijo= new TnodoTrie;

        inicializarNodo(nodoHijo);

        primerNodo->hijo=nodoHijo;
        primerNodo->letra=letraEntrante;
        primerNodo->flagParser=1;
        return primerNodo;
    }

    if (primerNodo->letra==letraEntrante){
        ////RAIZ->log<< "PrimerLetraEsIGualaMi="<< letraEntrante<<"= "<<primerNodo->letra<<endl;
        primerNodo->flagParser=1;
        return primerNodo;
    }

    //si la letra que entra es mas chica que las que ya estan
    if (primerNodo->letra>letraEntrante){
        ////RAIZ->log<< "DeboIngresarAlPRincipiodeLalistaYa:"<<letraEntrante<<" < "<<primerNodo->letra<<endl;
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

    if (primerNodo->letra<letraEntrante) {
        ////RAIZ->log<< "primerLetraEsmenosQueyo ENtro En bucle, la letra es: "<<primerNodo->letra<<" yo soy: "<<letraEntrante<<endl;

        TnodoTrie* nodoEntrante= new TnodoTrie;
        TnodoTrie* nuevoNodoHijo= new TnodoTrie;

        inicializarNodo(nuevoNodoHijo);
        inicializarNodo(nodoEntrante);

        if(primerNodo->hermano==NULL){
          //  //RAIZ->log<< "Siguuiente vacio  "<<primerNodo->letra<<" < "<<letraEntrante<<endl;

            nodoEntrante->letra=letraEntrante;
            nodoEntrante->flagParser=1;
            nodoEntrante->hijo=nuevoNodoHijo;

            primerNodo->hermano=nodoEntrante;

            return nodoEntrante;

        }

        else {
            ////RAIZ->log<< "como el primer Hermano no esta vacion entro en bucle\n"<<endl;

            TnodoTrie* nodoActual= primerNodo->hermano;

            TnodoTrie* nodoAnterior=primerNodo;

            while(nodoActual){

                if(nodoActual->letra==letraEntrante){

              //      //RAIZ->log<<"la letra de mi hijo es: "<<nodoActual->hijo->letra;
                //    //RAIZ->log <<" encontre una letra igual a mi, es la: "<<nodoActual->letra<<" yo soy "<<letraEntrante<<endl;
                    nodoActual->flagParser=1;

                    return nodoActual;

                }
                if(nodoActual->letra>letraEntrante){
                  //  //RAIZ->log<<"ACA NUNCA ENTRO";
                    ////RAIZ->log<< "me encajo en el medio de"<<nodoAnterior->letra<<" yo soy "<<letraEntrante<<" y mi hermana mayor"<< nodoActual->letra<<endl;

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
            ////RAIZ->log<<"llegue al final y no entre, yo soy: "<<letraEntrante<<"mi hermano menor es: "<<nodoAnterior->letra<<endl;

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

void Trie::destruirArbol_INI() {
    int cantidadDeNodos=0;

    destruirArbol(RAIZ->hijo,&cantidadDeNodos);

    //RAIZ->log<<"se destruyeron: "<<cantidadDeNodos<<" nodos"<<endl;
}

void Trie::destruirArbol(TnodoTrie* NODO,int* cantidadDeNodos) {
    if(NODO) {
        ////RAIZ->log<<NODO->letra;
        destruirArbol(NODO->hijo,cantidadDeNodos);
        destruirArbol(NODO->hermano,cantidadDeNodos);

        if(NODO->infoArchivo) {
            delete NODO->infoArchivo;
            *cantidadDeNodos=*cantidadDeNodos + 1;
        }
		
        delete NODO;
        (*cantidadDeNodos)++;
    }
}

//parte de busqueda

list<TnodoData*>* Trie::buscarPalabrasDelDocParseado_INI() {
    list<TnodoData*>* contenedorIdFreq = new list <TnodoData*>;
    //RAIZ->log<<endl<<endl;
    buscarPalabrasDelDocParseado(RAIZ->hijo,contenedorIdFreq);
    //RAIZ->log<<endl;

    return contenedorIdFreq;
}

void Trie::buscarPalabrasDelDocParseado(TnodoTrie* NODO,list<TnodoData*>* contenedorIdFreq ) {
    if(NODO) {
        if(NODO->flagParser) {
            //pongo en cero para que posteriores parseadas no lo reconozcan salvo que forme parte de palabras de la
            //correspondinete parseada
            NODO->flagParser=0;

            if(NODO->infoArchivo){

                contenedorIdFreq->push_back(NODO->infoArchivo);

            }

            buscarPalabrasDelDocParseado(NODO->hijo,contenedorIdFreq);
            buscarPalabrasDelDocParseado(NODO->hermano,contenedorIdFreq);
        } else{

            buscarPalabrasDelDocParseado(NODO->hermano,contenedorIdFreq);

        }
    }
}

void Trie::persistirPalabras_INI(fstream* salida) {
    string cadenaQueEscupePalabras;

    cadenaQueEscupePalabras.clear();

    persistirPalabras(RAIZ->hijo,salida,cadenaQueEscupePalabras);

    //RAIZ->log<<endl<<endl<<"cantidadTotalDePalabrasQueSeIngresaron(no quiere decir distintas): "<<RAIZ->cantidadTotalDePalabrasEnLaColeccion;

    //RAIZ->log<<endl<<"estado final del contador de IDs: "<<obtenerContadorId();

    //RAIZ->log.close();
}

void Trie::persistirPalabras(TnodoTrie* NODO,fstream* salida,string palabra) {
	if(NODO){

		palabra= palabra+NODO->letra;

		if(NODO->infoArchivo){ //si este nodo no esta vacio quiere decir que corresponde al final de una palabra

			//RAIZ->log<<palabra;
			//RAIZ->log<<"  id:"<<NODO->infoArchivo->id<<"  esta palabra aparecio: ";
			//RAIZ->log<<NODO->infoArchivo->ocurrenciasEnLaColeccion<<"  en la coleccion "<<endl;
			*salida<<palabra<<"  id: "<<NODO->infoArchivo->id<<endl;

		}

		persistirPalabras(NODO->hijo,salida,palabra);
		palabra.resize(palabra.size()-1);

		persistirPalabras(NODO->hermano,salida,palabra);
	}
}

int Trie::obternerCantidadDePalabrasIngresadas() {
    return RAIZ->cantidadTotalDePalabrasEnLaColeccion;
}

int Trie::obtenerContadorId() {
    return RAIZ->contadorDeId_s;
}

void Trie::incrementarContadorId() {
    RAIZ->contadorDeId_s++;
}

bool Trie::buscarPalabra(string palabra) {
   return buscarPalabra(palabra,RAIZ->hijo);
}

//recibe al hijo de la raiz del arbol
bool Trie::buscarPalabra(string palabra,TnodoTrie* NODO) {
    //cout<<"LETRA QUE SE ESTA BUSCANDO: "<<palabra[0]<<endl;

    //si devuele un nodo, la letra buscada entonces fue hallada
    //entonces la busqueda continua de lo contrario quiere decir que no se halla alguna de
    //las letras que forman la palabra buscada, la busqueda pincha
    TnodoTrie* nodoSiguiente=buscarLetra(palabra[0],NODO);

    if(nodoSiguiente){
        //si no estoy analizando la ultima letra de la palabra buscada
       if((palabra.size()>1) ){

            palabra=palabra.substr(1,palabra.size()-1);
            //cout<<"letra que esta por entrar a la sgte busqueda: "<<palabra[0]<<endl;
            return buscarPalabra(palabra,nodoSiguiente->hijo);

       }else{
            //despues cambiar esta parte el operador ternario
            if(nodoSiguiente->infoArchivo){
               // cout<<"contenido NODO->INFO->ID: "<<nodoSiguiente->infoArchivo->id<<endl;
                return true;
            }else{
          //      cout<<"encontre una subcadena pero la palabra cno esta"<<endl<<endl;
            //    cout<<"contenido NODO->INFO: "<<nodoSiguiente->infoArchivo<<endl;
                return false;
            }
       }
    }
    else{
        //ENTRO ACA SI LA LETRA QUE SE ESTABA BUSCANDO NO SE ENCUENTRA EN LA LISTA
        //cout<<"fallo en la letra: "<<NODO->letra<<endl;
        return false;
    }
}

TnodoTrie* Trie::buscarLetra(char letraBuscada, TnodoTrie* NODO) {
    //cadena incompleta
    if(NODO->letra==FINAL_DE_PALABRA) {

        //cout<<"dice que el nodo esta vacio"<<endl;
        return NULL;
    }
    //primer letra del Nodo es la que busco
    else if (NODO->letra==letraBuscada) {
        //cout<< "PrimerLetraEsIGualaMi=="<< letraBuscada<<endl;
        return NODO;
    }

    //si la letra que entra es mas chica que las que ya estan
    else if (NODO->letra>letraBuscada) {
        //cout<< "letra desigual yo busco una: "<<letraBuscada<<" y es una:  "<<NODO->letra<<endl;

        return NULL;
    }

    else if (NODO->letra<letraBuscada){
       //cout<< "primerLetraEsmenosQueyo:   "<<NODO->letra<<" ENtro En bucle"<<endl;


            TnodoTrie* nodoActual=NODO->hermano;
            TnodoTrie* nodoAnterior=NODO;

            while(!(nodoActual==NULL)){

                if(nodoActual->letra==letraBuscada){
        //            cout <<"encontre una letra igual a mi, es la: "<<nodoActual->letra<<" yo soy "<<letraBuscada<<endl;
                    return nodoActual;

                }
                //BUSCO EN EL SGTE NODO
                nodoAnterior=nodoActual;
                nodoActual=nodoActual->hermano;
            }
      //      cout<<"LLEGUE AL FINAL Y NO ENCONTRE LA LETRA"<<endl;
            return NULL;
    }

}

//se usa al final de la indexacion, vuelca todo en un vector, para facilitar la actualizacion de los id´s
// luego de la eliminaicon de las stopwords
vector<TnodoTerminoId*>* Trie::exportarPalabrasContenedor_INI(){

    RAIZ->contenedor->resize(this->obtenerContadorId()); //el id arranca desde cero

    string palabraAux = "";

    this->exportarPalabrasContenedor(this->RAIZ->hijo,RAIZ->contenedor,palabraAux);

    return RAIZ->contenedor;

}

void Trie::exportarPalabrasContenedor(TnodoTrie* NODO ,vector<TnodoTerminoId*>*contenedor, string palabra){

    if(NODO){
            palabra= palabra + NODO->letra;

            if(NODO->infoArchivo){ //si este nodo no esta vacio quiere decir que corresponde al final de una palabra

                //RAIZ->log<<palabra;
                //RAIZ->log<<"  id:"<<NODO->infoArchivo->id<<"  esta palabra aparecio: ";
                //RAIZ->log<<NODO->infoArchivo->ocurrenciasEnLaColeccion<<"  en la coleccion "<<endl;
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

void Trie::eliminarStopWord_INI(string palabraParaEliminar){

    eliminarStoprWord(RAIZ->hijo,palabraParaEliminar);

}

//este metodo no elimina ninguna palabra, solamente elimina el nodo que se usa de flag para que el trie lo
//deje de reconocer como palabra
void Trie::eliminarStoprWord(TnodoTrie* NODO, string palabraParaEliminar){

    TnodoTrie* nodoAnalizado = buscarLetra(palabraParaEliminar[0],NODO);

    if(palabraParaEliminar.size()==1){
        if(nodoAnalizado->infoArchivo){

            this->quitarTermindoDelContenedor(nodoAnalizado->infoArchivo->id);

            delete nodoAnalizado->infoArchivo;
            nodoAnalizado->infoArchivo=NULL;

        }else{
            cout<<"la palabra buscada para eliminar no se encuentra dentro del buffer"<<endl;
        }
    }else{
        palabraParaEliminar= palabraParaEliminar.substr(1,palabraParaEliminar.size()-1);
        eliminarStoprWord(nodoAnalizado->hijo,palabraParaEliminar);
    }
}

void Trie::quitarTermindoDelContenedor(int id){

    RAIZ->contenedor->at(id)=NULL;

    actualizarIds(id);
}

void Trie::actualizarIds(int idBorrado){

    for(int i=idBorrado+1; i<RAIZ->contenedor->size();i++){
        if(RAIZ->contenedor->at(i)){
            cout<<--*RAIZ->contenedor->at(i)->id<<" ";
        }
    }
}

void Trie::persistirPalabrasContenedor(fstream* salida){

    cout<<"persisteicno"<<endl;

    for(int i=0; i<RAIZ->contenedor->size();i++){
        //si no esta vacio
        if(RAIZ->contenedor->at(i)){
            *salida <<*RAIZ->contenedor->at(i)->id <<"  "<<RAIZ->contenedor->at(i)->palabra<<endl;
        }
    }
}
