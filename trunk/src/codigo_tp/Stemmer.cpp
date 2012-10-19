/*
   This is the Porter stemming algorithm, coded up in ANSI C by the
   author. It may be be regarded as canonical, in that it follows the
   algorithm presented in

   Porter, 1980, An algorithm for suffix stripping, Program, Vol. 14,
   no. 3, pp 130-137,

   only differing from it at the points maked --DEPARTURE-- below.

   See also http://www.tartarus.org/~martin/PorterStemmer

   The algorithm as described in the paper could be exactly replicated
   by adjusting the points of DEPARTURE, but this is barely necessary,
   because (a) the points of DEPARTURE are definitely improvements, and
   (b) no encoding of the Porter stemmer I have seen is anything like
   as exact as this version, even with the points of DEPARTURE!

   You can compile it on Unix with 'gcc -O3 -o stem stem.c' after which
   'stem' takes a list of inputs and sends the stemmed equivalent to
   stdout.

   The algorithm as encoded here is particularly fast.

   Release 1
*/


/* The main part of the stemming algorithm starts here. b is a buffer
   holding a word to be stemmed. The letters are in b[k0], b[k0+1] ...
   ending at b[k]. In fact k0 = 0 in this demo program. k is readjusted
   downwards as the stemming progresses. Zero termination is not in fact
   used in the algorithm.

   Note that only lower case sequences are stemmed. Forcing to lower case
   should be done before stem(...) is called.
*/

/*----------------------------------------------------------------------*/

#include "Stemmer.h"

static char * b;       		/* buffer for word to be stemmed */
static int 	k,k0,j;     	/* j is a general offset into the string */
static char * s;        	/* a char * (=string) pointer; passed into b above */
static int 	i_max = INC;	/* maximum offset in s */


/* cons(i) is true <=> b[i] is a consonant. */
int Stemmer::cons(int i){

	switch (b[i])
	{
		case 'a': case 'e': case 'i': case 'o': case 'u':
			return false;
		case 'y':
			return (i==k0) ? true : !cons(i-1);
		default:
			return true;
	}
}

/* m() measures the number of consonant sequences between k0 and j. if c is
   a consonant sequence and v a vowel sequence, and <..> indicates arbitrary
   presence,

      <c><v>       gives 0
      <c>vc<v>     gives 1
      <c>vcvc<v>   gives 2
      <c>vcvcvc<v> gives 3
      ....
*/
int Stemmer::m(){

	int n = 0;
	int i = k0;

	while(true){
		if (i > j)
			return n;
		if (! cons(i))
			break;
		i++;
	}
	i++;
	while(true)
	{
		while(true){
			if (i > j)
				return n;
			if (cons(i))
				break;
			i++;
	  }
	  i++;
	  n++;
	  while(true)
	  {
		  if (i > j)
			  return n;
		  if (! cons(i))
			  break;
		  i++;
	  }
	  i++;
	}
}

/* vowelinstem() is true <=> k0,...j contains a vowel */
int Stemmer::vowelinstem(){

	int i; for (i = k0; i <= j; i++) if (! cons(i)) return true;
	return false;
}

/* doublec(j) is true <=> j,(j-1) contain a double consonant. */
int Stemmer::doublec(int j){

	if (j < k0+1)
		return false;

	if (b[j] != b[j-1])
		return false;

	return cons(j);
}

/* cvc(i) is true <=> i-2,i-1,i has the form consonant - vowel - consonant
   and also if the second c is not w,x or y. this is used when trying to
   restore an e at the end of a short word. e.g.

      cav(e), lov(e), hop(e), crim(e), but
      snow, box, tray.

*/
int Stemmer::cvc(int i){

	if (i < k0+2 || !cons(i) || cons(i-1) || !cons(i-2))
		return false;
	{
		int ch = b[i];
		if (ch == 'w' || ch == 'x' || ch == 'y')
			return false;
	}
	return true;
}

/* ends(s) is true <=> k0,...k ends with the string s. */

int Stemmer::ends(char * s){

	int length = s[0];
	if (s[length] != b[k]) return false; /* tiny speed-up */
	if (length > k-k0+1) return false;
	if (memcmp(b+k-length+1,s+1,length) != 0) return false;
	j = k-length;
	return true;
}

/* setto(s) sets (j+1),...k to the characters in the string s, readjusting
   k. */

void Stemmer::setto(char * s)
{
	int length = s[0];
	memmove(b+j+1,s+1,length);
	k = j+length;
}

/* r(s) is used further down. */

void Stemmer::r(char * s) { if (m() > 0) setto(s); }

/* step1ab() gets rid of plurals and -ed or -ing. e.g.

       caresses  ->  caress
       ponies    ->  poni
       ties      ->  ti
       caress    ->  caress
       cats      ->  cat

       feed      ->  feed
       agreed    ->  agree
       disabled  ->  disable

       matting   ->  mat
       mating    ->  mate
       meeting   ->  meet
       milling   ->  mill
       messing   ->  mess

       meetings  ->  meet

*/

void Stemmer::step1ab(){

	if (b[k] == 's'){
		if (ends((char*)("\04" "sses")))
			k -= 2;
		else
		if (ends((char*)("\03" "ies")))
			setto((char*)("\01" "i"));
		else
		if (b[k-1] != 's')
			k--;
	}

	if (ends((char*)("\03" "eed"))) {
		if (m() > 0) k--;
	}
	else
	if ((ends((char*)("\02" "ed")) || ends((char*)("\03" "ing"))) && vowelinstem()){
		k = j;
		if (ends((char*)("\02" "at")))
			setto((char*)("\03" "ate"));
		else
		if (ends((char*)("\02" "bl")))
			setto((char*)("\03" "ble"));
		else
		if (ends((char*)("\02" "iz")))
			setto((char*)("\03" "ize"));
		else
		if (doublec(k))
		{
			k--;
			{
				int ch = b[k];
				if (ch == 'l' || ch == 's' || ch == 'z') k++;
			}
		}
		else
		if (m() == 1 && cvc(k))
			setto((char*)("\01" "e"));
	}
}

/* step1c() turns terminal y to i when there is another vowel in the stem. */

void Stemmer::step1c() {
	if (ends((char*)("\01" "y")) && vowelinstem()) b[k] = 'i';
}


/* step2() maps double suffices to single ones. so -ization ( = -ize plus
   -ation) maps to -ize etc. note that the string before the suffix must give
   m() > 0. */

void Stemmer::step2() {

	switch (b[k-1])
	{
		case 'a': if (ends((char*)("\07" "ational"))) { r((char*)("\03" "ate")); break; }
				  if (ends((char*)("\06" "tional"))) { r((char*)("\04" "tion")); break; }
				  break;
		case 'c': if (ends((char*)("\04" "enci"))) { r((char*)("\04" "ence")); break; }
				  if (ends((char*)("\04" "anci"))) { r((char*)("\04" "ance")); break; }
				  break;
		case 'e': if (ends((char*)("\04" "izer"))) { r((char*)("\03" "ize")); break; }
				  break;
		case 'l': if (ends((char*)("\03" "bli"))) { r((char*)("\03" "ble")); break; } /*-DEPARTURE-*/

	 /* To match the published algorithm, replace this line with
		case 'l': if (ends((char*)("\04" "abli")) { r("\04" "able"); break; } */

				  if (ends((char*)("\04" "alli"))) { r((char*)("\02" "al")); break; }
				  if (ends((char*)("\05" "entli"))) { r((char*)("\03" "ent")); break; }
				  if (ends((char*)("\03" "eli"))) { r((char*)("\01" "e")); break; }
				  if (ends((char*)("\05" "ousli"))) { r((char*)("\03" "ous")); break; }
				  break;
		case 'o': if (ends((char*)("\07" "ization"))) { r((char*)("\03" "ize")); break; }
				  if (ends((char*)("\05" "ation"))) { r((char*)("\03" "ate")); break; }
				  if (ends((char*)("\04" "ator"))) { r((char*)("\03" "ate")); break; }
				  break;
		case 's': if (ends((char*)("\05" "alism"))) { r((char*)("\02" "al")); break; }
				  if (ends((char*)("\07" "iveness"))) { r((char*)("\03" "ive")); break; }
				  if (ends((char*)("\07" "fulness"))) { r((char*)("\03" "ful")); break; }
				  if (ends((char*)("\07" "ousness"))) { r((char*)("\03" "ous")); break; }
				  break;
		case 't': if (ends((char*)("\05" "aliti"))) { r((char*)("\02" "al")); break; }
				  if (ends((char*)("\05" "iviti"))) { r((char*)("\03" "ive")); break; }
				  if (ends((char*)("\06" "biliti"))) { r((char*)("\03" "ble")); break; }
				  break;
		case 'g': if (ends((char*)("\04" "logi"))) { r((char*)("\03" "log")); break; } /*-DEPARTURE-*/
				  break;

	 /* To match the published algorithm, delete this line */
	}
}

/* step3() deals with -ic-, -full, -ness etc. similar strategy to step2. */

void Stemmer::step3() {

	switch (b[k])
	{
		case 'e': if (ends((char*)("\05" "icate"))) { r((char*)("\02" "ic")); break; }
				  if (ends((char*)("\05" "ative"))) { r((char*)("\00" "")); break; }
				  if (ends((char*)("\05" "alize"))) { r((char*)("\02" "al")); break; }
				  break;
		case 'i': if (ends((char*)("\05" "iciti"))) { r((char*)("\02" "ic")); break; }
				  break;
		case 'l': if (ends((char*)("\04" "ical"))) { r((char*)("\02" "ic")); break; }
				  if (ends((char*)("\03" "ful"))) { r((char*)("\00" "")); break; }
				  break;
		case 's': if (ends((char*)("\04" "ness"))) { r((char*)("\00" "")); break; }
				  break;
	}
}

/* step4() takes off -ant, -ence etc., in context <c>vcvc<v>. */

void Stemmer::step4(){

	switch (b[k-1])
    {
		case 'a': if (ends((char*)("\02" "al"))) break; return;
		case 'c': if (ends((char*)("\04" "ance"))) break;
				 if (ends((char*)("\04" "ence"))) break; return;
		case 'e': if (ends((char*)("\02" "er"))) break; return;
		case 'i': if (ends((char*)("\02" "ic"))) break; return;
		case 'l': if (ends((char*)("\04" "able"))) break;
				 if (ends((char*)("\04" "ible"))) break; return;
		case 'n': if (ends((char*)("\03" "ant"))) break;
				 if (ends((char*)("\05" "ement"))) break;
				 if (ends((char*)("\04" "ment"))) break;
				 if (ends((char*)("\03" "ent"))) break; return;
		case 'o': if (ends((char*)("\03" "ion")) && (b[j] == 's' || b[j] == 't')) break;
				 if (ends((char*)("\02" "ou"))) break; return;
				 /* takes care of -ous */
		case 's': if (ends((char*)("\03" "ism"))) break; return;
		case 't': if (ends((char*)("\03" "ate"))) break;
				 if (ends((char*)("\03" "iti"))) break; return;
		case 'u': if (ends((char*)("\03" "ous"))) break; return;
		case 'v': if (ends((char*)("\03" "ive"))) break; return;
		case 'z': if (ends((char*)("\03" "ize"))) break; return;
		default: return;
    }
    if (m() > 1)
    	k = j;
}

/* step5() removes a final -e if m() > 1, and changes -ll to -l if
   m() > 1. */
void Stemmer::step5(){

	j = k;

	if (b[k] == 'e'){
		int a = m();
		if (a > 1 || ( a == 1 && !cvc(k-1) ))
			k--;
   }
   if (b[k] == 'l' && doublec(k) && m() > 1)
	   k--;
}

/* In stem(p,i,j), p is a char pointer, and the string to be stemmed is from
   p[i] to p[j] inclusive. Typically i is zero and j is the offset to the last
   character of a string, (p[j+1] == '\0'). The stemmer adjusts the
   characters p[i] ... p[j] and returns the new end-point of the string, k.
   Stemming never increases word length, so i <= k <= j. To turn the stemmer
   into a module, declare 'stem' as extern, and delete the remainder of this
   file.
*/

int Stemmer::stem(char * p, int i, int j)
{  b = p; k = j; k0 = i; /* copy the parameters into statics */
   if (k <= k0+1) return k; /*-DEPARTURE-*/

   /* With this line, strings of length 1 or 2 don't go through the
      stemming process, although no mention is made of this in the
      published algorithm. Remove the line to match the published
      algorithm. */

   step1ab(); step1c(); step2(); step3(); step4(); step5();
   return k;
}

/*--------------------stemmer definition ends here------------------------*/


void Stemmer::increase_s(){

	i_max += INC;

	{
		char * new_s = (char *) malloc(i_max+1);
		{
			int i; for (i = 0; i < i_max; i++) new_s[i] = s[i];
		} /* copy across */
		free(s); s = new_s;
	}
}

/* applies the stem function over the parameter file.
   Prints on the console the result.
*/
void Stemmer::stemfile(FILE * f){

	while(true){

		int ch = getc(f);

		if (ch == EOF)
			return;

		if (LETTER(ch)){

			int i = 0;

			while(true){
				if (i == i_max)
					this->increase_s();

				ch = tolower(ch); /* forces lower case */

				s[i] = ch; i++;
				ch = getc(f);
				if (!LETTER(ch)){
					ungetc(ch,f);
					break;
				}
			}
			s[stem(s,0,i-1)+1] = 0;
			/* the previous line calls the stemmer and uses its result to
			   zero-terminate the string in s */
			printf("%s",s);
		}
		else putchar(ch);
	}
}


