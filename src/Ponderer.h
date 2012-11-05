
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

	std::vector<TacumEntropia*>* contenedorParcialEntropia;
	unsigned int cantidadDocumentosEnLaColeccion;
	Persister* matrizFreqLoc;
	Persister* matrizPonderada;
	Trie* trie;

	std::string nombreIndice;
};

#endif /* PONDERER_H_ */
