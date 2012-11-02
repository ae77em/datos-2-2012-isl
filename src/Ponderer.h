
#ifndef PONDERER_H_
#define PONDERER_H_

#include "Trie.h"
#include "Persister.h"
#include <vector>


class Ponderer {
public:
	Ponderer();
	virtual ~Ponderer();
	void ponderar(Trie*,Persister*);

private:
	void dividirTodoPorLog();
	void calcularEntropia();
	void ponderarLocarPorGlobal();

	std::vector<TacumEntropia*>* contenedorParcialEntropia;
	unsigned int cantidadDocumentosEnLaColeccion;
	Persister* matrizFreqLoc;
	Persister* matrizPonderada;
	Trie* trie;
};

#endif /* PONDERER_H_ */
