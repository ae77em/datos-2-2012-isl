#ifndef __STEMMER_H_
#define __STEMMER_H_

#include <cstring>  /* for memmove */
#include <cstdio>
#include <cstdlib>      /* for malloc, free */
#include <cctype>       /* for isupper, islower, tolower */

#define INC 50           /* size units in which s is increased */
#define LETTER(ch) (isupper(ch) || islower(ch))



class Stemmer {

private:
	static char * b;       /* buffer for word to be stemmed */
	static int k,k0,j;     /* j is a general offset into the string */
	static char * s;         /* a char * (=string) pointer; passed into b above */
	static int i_max = INC;  /* maximum offset in s */


public:
	Stemmer();
	static void stemfile(FILE * f);
	void increase_s();
	int stem(char * p, int i, int j);
	static void step5();
	static void step4();
	static void step3();
	static void step2();
	static void step1ab();
	static void step1c();
	static void r(char * s);
	static void setto(char * s);
	static int ends(char * s);
	static int cvc(int i);
	static int doublec(int j);
	static int vowelinstem();
	static int m();
	static int cons(int i);
	~Stemmer();
};

#endif
