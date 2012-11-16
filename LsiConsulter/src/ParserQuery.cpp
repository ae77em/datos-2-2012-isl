#include "ParserQuery.h"

ParserQuery::ParserQuery(std::string pathDiccionario, std::string pathOffsetDiccionario) {

	diccionario.open(pathDiccionario.c_str(), std::fstream::in);
	offsetDiccionario.open(pathOffsetDiccionario.c_str(),std::fstream::in);

	if(!diccionario.good() || !offsetDiccionario.good()){
        std::cout<<"no se pudiento abrir diccioarnios"<<std::endl;
	}

	stemmer = new Stemmer();

	palabras = new std::list<std::string>;
	palabrasStemezadas = new std::list<std::string>;
	contenedorOffsetDiccionario = new std::vector<unsigned int>;

	cargarOffsetDiccionario();

}

void ParserQuery::cargarOffsetDiccionario(){

    unsigned int offset;

    while(!offsetDiccionario.eof()){
        offsetDiccionario>>offset;
        std::cout<<offset<<" ";
        contenedorOffsetDiccionario->push_back(offset);
    }

    contenedorOffsetDiccionario->pop_back();
}

ParserQuery::~ParserQuery() {
	// TODO Auto-generated destructor stub
}

std::vector<unsigned int*>* ParserQuery::parsearConsulta(std::string consulta){

	this->consulta = consulta;

	splitQuery();

	stemezarPalabras();

	return recuperarIds();

}

void ParserQuery::splitQuery(){


	std::string palabraParseada = "";

	char letra = 32;

	for(unsigned int i=0; i<consulta.size(); i++){

		if(consulta.at(i) != letra){
   			palabraParseada += consulta.at(i);
		}else{
			std::string palabraParseadaParaLista = palabraParseada;
			palabras->push_back(palabraParseadaParaLista);

			palabraParseada = "";
		}
	}

    //la ultima palabra queda siempre colgada poque al final de la misma no hay un espacio
	if (palabraParseada != ""){
	    palabras->push_back(palabraParseada);
	}

}

void ParserQuery::stemezarPalabras(){

	std::list<std::string>::iterator b = palabras->begin();
	std::list<std::string>::iterator e = palabras->end();

	while(b!=e){
		palabrasStemezadas->push_back(stemmer->stemPalabra( *(b) ) );
		b++;
	}

}

std::vector<unsigned int*>* ParserQuery::recuperarIds(){

	std::vector<unsigned int*>* ids = new std::vector<unsigned int*>;

	std::list<std::string>::iterator b = palabrasStemezadas->begin();
	std::list<std::string>::iterator e = palabrasStemezadas->end();

	while(b!=e){

        std::cout<<"palabra buscando ID: "<<*(b)<<std::endl;

		unsigned int* id = buscarIdTermino( *(b) );

        std::cout<<"ID hallado: "<<*id<<std::endl;

		ids->push_back( id );

		b++;
	}

	return ids;
}

unsigned int* ParserQuery::buscarIdTermino(std::string termino){

    std::cout<<"comienzo busqueda ID de termino: "<<termino<<std::endl;

    int ini=0;
    int fin=contenedorOffsetDiccionario->size()-1;
    int medio = fin / 2;

    return buscarIdTerminoRec(termino,ini,fin,medio);

}

unsigned int* ParserQuery::buscarIdTerminoRec(std::string termino,int ini,int fin,int medio){

    std::cout<<"indice: "<<ini<<std::endl;

    std::string terminoEnArchivo="";
    unsigned int id=0;

    //condicion de corte
    if(ini==fin){
        diccionario.seekg(contenedorOffsetDiccionario->at(ini));
        diccionario>>terminoEnArchivo;
        diccionario>>id;

        if (terminoEnArchivo.compare(termino)==0){
        	return new unsigned int(id);
        }else{
        	return NULL;
        }

    }

    diccionario.seekg(contenedorOffsetDiccionario->at(medio));

    diccionario>>terminoEnArchivo;
    diccionario>>id;

    std::cout<<"termino leido: "<<terminoEnArchivo<<" termino buscado: "<<termino<<std::endl;

    if( terminoEnArchivo.compare(termino)==0){
         std::cout<<"fin busqueda"<<std::endl;
    	return new unsigned int(id);
    }else{

        if(termino.compare(terminoEnArchivo)==-1){
            fin= medio -1;
            medio= fin/2;
            return buscarIdTerminoRec(termino,ini,fin,medio);

            }else{
            ini= medio + 1;
            medio= (medio + fin)/2;
            return buscarIdTerminoRec(termino,ini,fin,medio);

        }
    }
}


void ParserQuery::obtenerOffsetDiccionario(){

	unsigned int nro=0;
    while(!offsetDiccionario.eof()){
    	offsetDiccionario>>nro;
        this->contenedorOffsetDiccionario->push_back(nro);
    }

}
