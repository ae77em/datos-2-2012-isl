
#ifndef PONDERER_H_
#define PONDERER_H_

#include "Trie.h"
#include "Persister.h"
#include <vector>


class Ponderer {
public:
	Ponderer();
	virtual ~Ponderer();
	void ponderar(Trie*,Persister*,std::string);

private:
	void dividirTodoPorLog();
	void calcularEntropia();
	void ponderarLocarPorGlobal();
	void inicializarPonderer();
	void normalizar();

	Persister* matrizFreqLoc; //puntero a matriz sobre la cual se calcula la entropia para luego ponderar
	Persister* matrizPonderada; // matriz con la entropia aplicada
	Persister* matrizPonderadaNormalizada; // matriz con la entropia aplicada

	Trie* trie;

	std::string pathMatrizPonderada;
	std::vector<TacumEntropia*>* contenedorParcialEntropia;
	unsigned int cantidadDocumentosEnLaColeccion;

};

#endif /* PONDERER_H_ */
