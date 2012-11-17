#include "Consulter.h"

Consulter::Consulter()
{
    //ctor
}

Consulter::~Consulter()
{
    //dtor
}

double Consulter::metodoCoseno(std::vector<double>* v1,std::vector<double>* v2){

    double numerador = productoInterno(v1,v2);
    double norma1 = norma(v1);
    double norma2 = norma(v2);

    return ( numerador / (norma1 * norma2) ) ;
}

int Consulter::buscarIdTermino(std::string termino,std::vector<int>* offsetLexico,std::fstream* lexico){

    int ini=0;
    int fin=offsetLexico->size()-1;
    int medio = fin / 2;

    return buscarIdTerminoRec(termino,offsetLexico,ini,fin,medio,lexico);

}


std::vector<int>* Consulter::obtenerOffsetLexico(std::string path){

//levanto offset del lexico
    std::fstream offsetLexico;
    std::vector<int>* offset = new std::vector<int>;
    offsetLexico.open("offsetLexico.txt",std::fstream::in);
    int nro=0;
    while(!offsetLexico.eof()){
        offsetLexico>>nro;
        offset->push_back(nro);
    }
    offsetLexico.close();

    return offset;

}


double Consulter::productoInterno(std::vector<double>* v1,std::vector<double>* v2){

    double producto=0;

    for(unsigned i=0; i<v1->size();i++){
        producto += (v1->at(i)*v2->at(i));
    }

    return producto;

}

double Consulter::norma(std::vector<double>* v){

    double norma =0;

    for(unsigned i=0; i<v->size();i++){
        norma += (v->at(i)*v->at(i));
    }

    return sqrt(norma);

}

int Consulter::buscarIdTerminoRec(std::string termino,std::vector<int>* offsetLexico,int ini,int fin,int medio,std::fstream* lexico){

    std::string terminoEnArchivo="";
    int id=0;

    //condicion de corte
    if(ini==fin){
        lexico->seekg(offsetLexico->at(ini));
        *lexico>>terminoEnArchivo;
        *lexico>>id;
        return (terminoEnArchivo.compare(termino)==0)?id:-1;
    }

    lexico->seekg(offsetLexico->at(medio));
    *lexico>>terminoEnArchivo;
    *lexico>>id;
    if( terminoEnArchivo.compare(termino)==0){
        return id;
    }else{

        if(termino.compare(terminoEnArchivo)==-1){
            fin= medio -1;
            medio= fin/2;
            return buscarIdTerminoRec(termino,offsetLexico,ini,fin,medio,lexico);

            }else{
            ini= medio + 1;
            medio= (medio + fin)/2;
            return buscarIdTerminoRec(termino,offsetLexico,ini,fin,medio,lexico);

        }
    }

}
