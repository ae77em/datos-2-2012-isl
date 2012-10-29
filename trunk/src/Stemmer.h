#ifndef __STEMMER_H_
#define __STEMMER_H_

#include <cstdio>

class Stemmer {

public:
	Stemmer();
	~Stemmer();
	void stemfile(FILE * f);

private:
	void increase_s();
	int stem(char * p, int i, int j);
	void step5();
	void step4();
	void step3();
	void step2();
	void step1ab();
	void step1c();
	void r(char * s);
	void setto(char * s);
	int ends(char * s);
	int cvc(int i);
	int doublec(int j);
	int vowelinstem();
	int m();
	int cons(int i);
};

#endif
