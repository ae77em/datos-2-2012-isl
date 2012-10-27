
#ifndef PONDERER_H_
#define PONDERER_H_

#include "Trie.h"
#include "Persister.h"
#include <vector>



class Ponderer {
public:
	Ponderer(Trie*,Persister*);
	virtual ~Ponderer();
	void ponderar();

private:
	void dividirTodoPorLog();
	void calcularEntropia();
	void ponderarLocarPorGlobal();

	vector<TacumEntropia*>* contenedorParcialEntropia;
	unsigned int cantidadDocumentosEnLaColeccion;
	Persister* matrizFreqLoc;
	Persister* matrizPonderada;
	Trie* trie;
};

#endif /* PONDERER_H_ */
