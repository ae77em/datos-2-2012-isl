#include "Consulter.h"

Consulter::Consulter(unsigned int unK,std::string pathMatrizU,std::string pathMatrizS,std::string pathMatrizV) {

    this->calculer = new CalculosAlgebraicos();
	this->parserQuery = new ParserQuery("diccionario.txt","offsetDiccionario.txt");
	this-> K = unK;

    this->documento = new std::vector<double*>;
    this->iniDoc();

	this-> vectorS = new std::vector<double*>;
	this-> vectorS->resize(K);

    matrizU.open(pathMatrizU.c_str(),std::ifstream::binary);
    matrizS.open(pathMatrizS.c_str(),std::ifstream::binary);
    matrizV.open(pathMatrizV.c_str(),std::ifstream::binary);

    cargarS();

}

void Consulter::iniDoc(){

    this->documento->resize(K);

    for(unsigned int i=0; i<K;i++){
        documento->at(i) = new double(0);
    }


}

void Consulter::cargarS(){
    //la matriz S es una sola fila, compuesta por los valores singulares de la SVD
    double* filaS = new double[K];

    matrizS.read((char*)filaS,sizeof(double)*K);

    for(unsigned int i=0; i<K;i++){

        vectorS->at(i) = new double(filaS[i]);

    }

}

Consulter::~Consulter() {
	// TODO Auto-generated destructor stub
}

void Consulter::rankearConsulta(std::string consulta){

	//toma un conjuento de palabras representado por el string y devuelve un vector que representa la consulta
	this->query = parserQuery->parsearConsulta(consulta);

    //este vector hay que normalizarlo, luego aplicale el metodo del coseno junton con todas las
    //columnas de VT o la filas de V, depende de como se haya almacenado la matriz
    this->queryProyectada = this->proyectarQuery();

    evaluar();
}

void Consulter::evaluar(){

    std::cout.unsetf(std::ios::floatfield);
    std::cout.precision(15);

    //primero normalizo el vector query
    calculer->normalizarVector(this->queryProyectada);

    crearRegistro(); //pide memoria para el registro que levatara los documentos

    std::cout<<"MOSTRANDO RESULTADOS:"<<std::endl<<std::endl;

    while(hayDocumentos()){

        //deberia de estar normalizado
        obtenerDocumento();

        std::cout<<calculer->metodoCoseno(this->queryProyectada , this->documento)<<std::endl;

    }

    liberarRegistro();

}

void Consulter::crearRegistro(){

    registroV = new double[this->K];

}

void Consulter::liberarRegistro(){

    delete [] registroV;
}

bool Consulter::hayDocumentos(){

    return !matrizV.eof();

}

void Consulter::obtenerDocumento(){

    matrizV.read((char*)registroV,sizeof(double)*this->K);

    for(unsigned int i=0; i< K ; i++){
        *documento->at(i) = registroV[i]; //solo es un camio de formato
        //std::cout<<documento->at(i)<<" ";
    }

}

std::vector<double*>* Consulter::proyectarQuery(){

    return this->multiplicarContraS( this->multiplicarContraU());

}

std::vector<double*>* Consulter::multiplicarContraU(){

    //como lo indices del vector query son 1, el producto interno entre el queyr y cada una de las columnas
    //sera la sumatoria de cada uno de los indices de esas columnas

    //vector que ira acumulando la sumatoria resultante del producto intenrno;
    std::vector<double*>* productoInternoQcontraU = new std::vector<double*>;

    productoInternoQcontraU->resize(this->K); //tendra el tama�o de la cantidad de topicos del indice

    //inicializamos
    for(int i=0; i<productoInternoQcontraU->size(); i++){
        productoInternoQcontraU->at(i)= new double(0);
    }

    //registro donde se iran almacenando las filas de U
    double* filaMatrizU = new double[K];

    //comienza multiplicacion

    for(unsigned int i=0; i<query->size(); i++){
        //me posiciono en la fila que indica el indice del vector querya analizado
        matrizU.seekg(*query->at(i)*sizeof(double)*K);

        //levanto fila
        matrizU.read((char*)filaMatrizU,sizeof(double)*K);

        //voy realizando las sumas parciales
        for(int i=0; i<productoInternoQcontraU->size(); i++){
            *productoInternoQcontraU->at(i) += filaMatrizU[i];

        }
    }

    delete [] filaMatrizU;

    return productoInternoQcontraU;
}

std::vector<double*>* Consulter::multiplicarContraS(std::vector<double*>* productoInternoQcontraU){

    for(unsigned int i=0;i<productoInternoQcontraU->size();i++){
        *productoInternoQcontraU->at(i) *= *vectorS->at(i);
    }

    return productoInternoQcontraU;
}

