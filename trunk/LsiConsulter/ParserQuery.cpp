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

    while(!offsetDiccionario.eof() && (offsetDiccionario>>offset) ){
        contenedorOffsetDiccionario->push_back(offset);
    }

 }

ParserQuery::~ParserQuery() {
	// TODO Auto-generated destructor stub
}

std::vector<unsigned int>* ParserQuery::parsearConsulta(std::list<std::string>* terminosConsulta) {
	palabras = terminosConsulta;
	stemezarPalabras();

	return recuperarIds();
}

void ParserQuery::stemezarPalabras(){

	std::list<std::string>::iterator b = palabras->begin();
	std::list<std::string>::iterator e = palabras->end();

	while(b!=e){
		palabrasStemezadas->push_back(stemmer->stemPalabra( *(b) ) );
		b++;
	}

}

std::vector<unsigned int>* ParserQuery::recuperarIds(){

	std::vector<unsigned int>* ids = new std::vector<unsigned int>;

	std::list<std::string>::iterator b = palabrasStemezadas->begin();
	std::list<std::string>::iterator e = palabrasStemezadas->end();

	while(b!=e){


		unsigned int id = buscarIdTermino( *(b) );

		//if(id != -1){
			ids->push_back( id );
	//	}

		b++;
	}

	return ids;
}

unsigned int ParserQuery::buscarIdTermino(std::string termino){

    int ini=0;
    int fin=contenedorOffsetDiccionario->size()-1;
    int medio = fin / 2;

    return buscarIdTerminoRec(termino,ini,fin,medio);

}

unsigned int ParserQuery::buscarIdTerminoRec(std::string termino,int ini,int fin,int medio){


    std::string terminoEnArchivo="";
    unsigned int id=0;

    //condicion de corte
    if(ini==fin){
        diccionario.seekg(contenedorOffsetDiccionario->at(ini));
        diccionario>>terminoEnArchivo;
        diccionario>>id;

        std::cout<<"termnin: "<<termino<<" ternArchivo; "<<terminoEnArchivo<<std::endl;

        if (terminoEnArchivo.compare(termino)==0){
        	return id;
        }else{
        	return -1;
        }

    }

    diccionario.seekg(contenedorOffsetDiccionario->at(medio));

    diccionario>>terminoEnArchivo;
    diccionario>>id;
    std::cout<<"termnin: "<<termino<<" ternArchivo; "<<terminoEnArchivo<<std::endl;
    if( terminoEnArchivo.compare(termino)==0){
    	return id;
    }else{

        if(termino.compare(terminoEnArchivo)<0){
            fin= medio -1;
            medio= (ini + fin)/2;
            return buscarIdTerminoRec(termino,ini,fin,medio);

            }else{
            ini= medio + 1;
            medio= (ini + fin)/2;
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
