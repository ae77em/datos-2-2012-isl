
#ifndef PONDERER_H_
#define PONDERER_H_

#include "Trie.h"
#include "Persister.h"
#include <vector>



class Ponderer {
public:
	Ponderer(Trie*);
	virtual ~Ponderer();
	void calcularEntropia(Persister*);

private:
	vector<TacumEntropia*>* contenedorParcialEntropia;
	unsigned int cantidadDocumentosEnLaColeccion;
};

#endif /* PONDERER_H_ */
