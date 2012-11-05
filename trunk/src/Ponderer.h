
#ifndef PONDERER_H_
#define PONDERER_H_

#include "Trie.h"
#include "Persister.h"
#include <vector>


class Ponderer {
public:
	Ponderer();
	virtual ~Ponderer();
	std::string ponderar(Trie*,Persister*,std::string);

private:
	void dividirTodoPorLog();
	void calcularEntropia();
	std::string ponderarLocarPorGlobal();
	void inicializarPonderer();

	std::vector<TacumEntropia*>* contenedorParcialEntropia;
	unsigned int cantidadDocumentosEnLaColeccion;
	Persister* matrizFreqLoc;
	Persister* matrizPonderada;
	Trie* trie;

	std::string nombreMatrizFinal;
};

#endif /* PONDERER_H_ */
