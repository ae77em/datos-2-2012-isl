#include "CalculosAlgebraicos.h"

CalculosAlgebraicos::CalculosAlgebraicos() {

}

CalculosAlgebraicos::~CalculosAlgebraicos() {

}

double CalculosAlgebraicos::metodoCoseno(std::vector<double>* v1, std::vector<double>* v2) {
    double numerador = productoInterno(v1, v2);

    //sacar estas normas, ya ya son versores los que se pasan por parametros, quita presicion, es redundante
    //double norma1 = norma(v1);
    //double norma2 = norma(v2);

    //return numerador / (norma1 * norma2);
    return numerador;
}

double CalculosAlgebraicos::productoInterno(std::vector<double>* v1, std::vector<double>* v2) {
    double producto=0;

    for (unsigned i = 0; i < v1->size(); i++){
        producto += (v1->at(i)) * (v2->at(i));
    }

    return producto;
}

double CalculosAlgebraicos::norma(std::vector<double>* v) {
    double norma = 0;

    for (unsigned i = 0; i < v->size(); i++){
        norma += (v->at(i)) * (v->at(i));
    }

    return sqrt(norma);
}

void CalculosAlgebraicos::normalizarVector(std::vector<double>* v) {
    double normaDelVector = norma(v);

    for (unsigned int i = 0; i < v->size(); i++){
        v->at(i) /= normaDelVector;
    }
}
