#include "Consulter.h"

#include <ctime>

Consulter::Consulter(std::string repositorio) {
	std::string home = getenv("HOME");
	std::string rutaRepositorio = home + "/" + repositorio;

	//solo es para que imprima decimales
	std::cout.unsetf(std::ios::floatfield);
	std::cout.precision(15);

	heap = new Heap();
	calculer = new CalculosAlgebraicos();
    parserQuery = new ParserQuery(rutaRepositorio + "/diccionarioTerminos", rutaRepositorio + "/offsetDiccionarioTermino");

    cargarNombreArchivos(rutaRepositorio);

	matrizU.open((rutaRepositorio + "/U.bin").c_str(), std::ios_base::binary);
    matrizS.open((rutaRepositorio + "/S.bin").c_str(), std::ios_base::binary);
    matrizV.open((rutaRepositorio + "/V.bin").c_str(), std::ios_base::binary);

	cargarS();
	cargarV(); //se levanta normal, no esta traspuesta
}


void Consulter::cargarNombreArchivos(std::string rutaRepositorio) {
	std::ifstream archivos;
	archivos.open( (rutaRepositorio + "/nombreArchivos").c_str());

	std::string nombreArchivo="";

	while(archivos.good() && std::getline(archivos,nombreArchivo)){
		contenedorNombreArchivos.push_back(nombreArchivo);
	}

	archivos.close();

}

void Consulter::cargarS() {
	// Leo el tamaño de la matriz
	matrizS.read((char*)(&cantAutovalores), sizeof(int));

	// Inicializo vector S
	this->vectorS = new std::vector<double>;
	this->vectorS->resize(cantAutovalores);

	double* regS = new double[cantAutovalores];

	matrizS.read((char*) regS, sizeof(double) * cantAutovalores);

	for(unsigned int i = 0; i < cantAutovalores ; i++){
		this->vectorS->at(i) = regS[i];
	}

	delete[] regS;
}

void Consulter::cargarV() {
	generarContenedorMatrizV();
	cargarMatrizV();
}

void Consulter::generarContenedorMatrizV() {
	contenedorMatrizV = new std::vector< std::vector<double>* >;

	for(unsigned int i = 0 ; i < cantAutovalores ; i++){
		contenedorMatrizV->push_back(new std::vector<double>);
	}
}

void Consulter::cargarMatrizV() {
	registroV = new double[this->cantAutovalores];

	for (unsigned int j = 0; j < cantAutovalores; j++) {
		matrizV.read((char*) registroV, sizeof(double) * this->cantAutovalores);

		for(unsigned int i = 0; i < cantAutovalores ; i++){
			contenedorMatrizV->at(j)->push_back( registroV[i] ); //solo es un camio de formato
		}
	}

	delete [] registroV;
}


Consulter::~Consulter() {

}

int Consulter::rankearConsulta(std::list<std::string>* terminosConsulta) {
	time_t tiempoInicioConsulta, tiempoFinConsulta;
	double tiempoTotal;

	tiempoInicioConsulta = time(NULL);

	//toma un conjuento de palabras representado por el string y devuelve un vector que representa la consulta
	query = parserQuery->parsearConsulta(terminosConsulta);

	if(query != NULL){
		queryProyectada = proyectarQuery();

		evaluar();

		tiempoFinConsulta = time(NULL);
		tiempoTotal = tiempoFinConsulta - tiempoInicioConsulta;

		std::cout << "Tiempo tardado en realizar la consulta: " << (tiempoTotal / 1000) << " segundos" << std::endl;
		return 1;
	}else{
		return 0;
	}
}

void Consulter::evaluar(){

    //primero normalizo el vector query
    calculer->normalizarVector(this->queryProyectada);

    TnodoHeapDocPuntaje nodoHeap;

    //metodo coseno
    for(unsigned int i=0; i< cantAutovalores; i++){

    	nodoHeap.puntaje = calculer->productoInterno(this->queryProyectada , this->contenedorMatrizV->at(i) );
    	nodoHeap.doc = i;
    	heap->cargarElemento(nodoHeap);

    }

    mostrarRankings();

}
void Consulter::mostrarRankings(){

	unsigned int cantDocSolicitados;

	std::cout<<"INGRESE CANTIDAD DE DOCUMENTOS A LISTAR"<<std::endl;
	std::cin>>cantDocSolicitados;

	std::cout<<"MOSTRANDO RESULTADOS"<<std::endl;

	for(unsigned int i=0; i<cantDocSolicitados; i++ ){

		TnodoHeapDocPuntaje nodoHeap = heap->obtenerMaximo();

		std::string nombreArchivo = obtenerNombreArchivo(nodoHeap.doc);

		std::cout<<"RANK: "<<i+1<<" NombreArchivo: "<<nombreArchivo<<"       Puntaje: "<<nodoHeap.puntaje<<std::endl;

	}


}

std::string Consulter::obtenerNombreArchivo(unsigned int pos) {
	return contenedorNombreArchivos.at(pos);
}

std::vector<double>* Consulter::proyectarQuery() {
    return this->multiplicarContraS(this->multiplicarContraU());
}

std::vector<double>* Consulter::multiplicarContraU() {
    //como lo indices del vector query son 1, el producto interno entre el query y cada una de las columnas
    //sera la sumatoria de cada uno de los indices de esas columnas

    //vector que ira acumulando la sumatoria resultante del producto intenrno;
    std::vector<double>* productoInternoQcontraU = new std::vector<double>;

    productoInternoQcontraU->resize(this->cantAutovalores); //tendra el tama�o de la cantidad de topicos del indice

    //inicializamos
    for(unsigned int i=0; i<productoInternoQcontraU->size(); i++){
        productoInternoQcontraU->at(i)= 0;
    }

    //registro donde se iran almacenando las filas de U
    double* filaMatrizU = new double[cantAutovalores];

    //comienza multiplicacion
    for(unsigned int i=0; i<query->size(); i++){
    	//me posiciono en la fila que indica el indice del vector query
        matrizU.seekg(query->at(i)*sizeof(double)*cantAutovalores);

        //levanto fila
        matrizU.read((char*)filaMatrizU,sizeof(double)*cantAutovalores);

        //voy realizando las sumas parciales
        for(unsigned int i=0; i<productoInternoQcontraU->size(); i++){
            productoInternoQcontraU->at(i) += filaMatrizU[i];
        }
    }

    delete[] filaMatrizU;
    return productoInternoQcontraU;
}

std::vector<double>* Consulter::multiplicarContraS(std::vector<double>* productoInternoQcontraU) {
    for(unsigned int i=0;i<productoInternoQcontraU->size();i++){
        productoInternoQcontraU->at(i) *= vectorS->at(i);
    }

    return productoInternoQcontraU;
}