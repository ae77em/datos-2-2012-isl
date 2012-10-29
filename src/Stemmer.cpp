/*
   Algoritmo de Porter.

   Porter, 1980, An algorithm for suffix stripping, Program, Vol. 14,
   no. 3, pp 130-137,

   Esta implementacion se baso en las explicaciones y ejemplos tomados de

   http://snowball.tartarus.org/algorithms/porter/stemmer.html

   y del codigo publicado en

   http://www.tartarus.org/~martin/PorterStemmer

*/

#include "Stemmer.h"

#include <cstring>
#include <cstdlib>
#include <cctype>
#include <algorithm>

#define INC 50           /* size units in which s is increased */
#define LETTER(ch) (isupper(ch) || islower(ch))
#define BUFF 16

/* Constructor y Destructor */
Stemmer::Stemmer(){
	i_max = INC;
	s.resize(i_max);
};

Stemmer::~Stemmer(){};

/* esConsonante(i) es true <=> b[i] es una consonante. */
int Stemmer::esConsonante(int i){

	switch (b[i])
	{
		case 'a': case 'e': case 'i': case 'o': case 'u':
			return false;
		case 'y':
			return (i==k0) ? true : !esConsonante(i-1);
		default:
			return true;
	}
}

/* m() mide la cantidad de secuencias de consonantes entre k0 y j. Si c es
   una secuencia de consonantes y v una secuencia de vocales, y <..> indica
   valores arbitrarios,

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
		if ( not esConsonante(i))
			break;
		i++;
	}
	i++;
	while(true){
		while(true){
			if (i > j)
				return n;
			if (esConsonante(i))
				break;
			i++;
	  }
	  i++;
	  n++;
	  while(true){
		  if (i > j)
			  return n;
		  if ( not esConsonante(i))
			  break;
		  i++;
	  }
	  i++;
	}
}

/* vocalEnStem() es true <=> k0,...j contiene una vocal */
int Stemmer::vocalEnStem(){

	int i;
	for (i = k0; i <= j; i++)
		if (! esConsonante(i))
			return true;

	return false;
}

/* dobleConsonante(j) es true <=> j,(j-1) contiene una consonate doble. */
int Stemmer::dobleConsonante(int j){

	if (j < k0+1)
		return false;

	if (b[j] != b[j-1])
		return false;

	return esConsonante(j);
}

/* cvc(i) es true <=> i-2,i-1,i tiene la forma consonante - vocal - consonante
   y tambien si la segunda consonante no es w,x or y. Se usa cuando queremos
   restaurar una e al final de una palabra corta.
   Ej:

      cav(e), lov(e), hop(e), crim(e), but
      snow, box, tray.

*/
int Stemmer::cvc(int i){

	if (i < k0+2 || !esConsonante(i) || esConsonante(i-1) || !esConsonante(i-2))
		return false;
	{
		int ch = b[i];
		if (ch == 'w' || ch == 'x' || ch == 'y')
			return false;
	}
	return true;
}

/* ends(s) es true si el substring del intervalo <=> k0,...k en b es s. */

int Stemmer::ends(char * str){

	int length = str[0];

	if (str[length] != b[k])
		return false;

	if (length > k-k0+1)
		return false;

	if (memcmp(b+k-length+1,str+1,length) != 0)
		return false;

	j = k-length;

	return true;
}

/* setto(s) cambia s en el rango (j+1),...k por los pasados por parametro,
   ajustando k.
 */

void Stemmer::setto(char * str)
{
	int length = str[0];

	/* reemplazo el string correspondiente */
	memmove(b+j+1,str+1,length);

	k = j+length;
}

/* este metodo es llamado en los pasos 2 y 3 */
void Stemmer::r(char * s) {

	if (m() > 0)
		setto(s);
}

/* paso1ab() quita los plurales y -ed e -ing.

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
void Stemmer::paso1ab(){

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
		if (m() > 0)
			k--;
	}
	else
	if (vocalEnStem()){
		bool exit = true;
		/* elimino los sufijos que sobran */
		if(ends((char*)("\02" "ed"))){
			setto((char*)("\01" "\0"));
			exit=false;
		}
		else if(ends((char*)("\03" "ing"))){
			setto((char*)("\01" "\0"));
			exit=false;
		}

		if ( not exit ){
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
			if (dobleConsonante(k))
			{
				k--;
				{
					int ch = b[k];
					if (ch == 'l' || ch == 's' || ch == 'z')
						k++;
				}
			}
			else
			if (m() == 1 && cvc(k))
				setto((char*)("\01" "e"));
		}
	}
}

/* paso1c() cambia las y finales por i cuando está precedida de una vocal
 * por ej:
 * 		play -> plai
 */
void Stemmer::paso1c() {

	if (ends((char*)("\01" "y")) && vocalEnStem())
		b[k] = 'i';
}


/* paso2() mapea los sufijos dobles a uno simple. Asi -ization ( = -ize mas
   -ation) cambia a -ize etc. m>0.
   Ej:

	(m>0) ATIONAL 	-> ATE		relational		-> 	relate
	(m>0) TIONAL	-> TION		conditional		-> 	condition
								rational		-> 	rational
	(m>0) ENCI		-> ENCE		valenci			-> 	valence
	(m>0) ANCI		-> ANCE		hesitanci		->	hesitance
	(m>0) IZER		-> IZE		digitizer		->	digitize
	(m>0) ABLI		-> ABLE		conformabli		->	conformable
	(m>0) ALLI		-> AL		radicalli		->	radical
	(m>0) ENTLI		-> ENT		differentli		->	different
	(m>0) ELI		-> E		vileli			->	vile
	(m>0) OUSLI		-> OUS		analogousli		->	analogous
	(m>0) IZATION	-> IZE		vietnamization	->	vietnamize
	(m>0) ATION		-> ATE		predication		->	predicate
	(m>0) ATOR		-> ATE		operator		->	operate
	(m>0) ALISM		-> AL		feudalism		->	feudal
	(m>0) IVENESS	-> IVE		decisiveness	->	decisive
	(m>0) FULNESS	-> FUL		hopefulness		->	hopeful
	(m>0) OUSNESS	-> OUS		callousness		->	callous
	(m>0) ALITI		-> AL		formaliti		->	formal
	(m>0) IVITI		-> IVE		sensitiviti		->	sensitive
	(m>0) BILITI	-> BLE		sensibiliti		->	sensible
*/
void Stemmer::paso2() {

	switch (b[k-1])
	{
		case 'a': if (ends((char*)("\07" "ational"))) {
					  r((char*)("\03" "ate"));
					  break;
				  }
				  if (ends((char*)("\06" "tional"))) {
					  r((char*)("\04" "tion"));
					  break;
				  }
				  break;
		case 'c': if (ends((char*)("\04" "enci"))) {
					  r((char*)("\04" "ence"));
					  break;
				  }
				  if (ends((char*)("\04" "anci"))) {
					  r((char*)("\04" "ance"));
					  break;
				  }
				  break;
		case 'e': if (ends((char*)("\04" "izer"))) {
					  r((char*)("\03" "ize"));
					  break;
				  }
				  break;
		case 'l': if (ends((char*)("\03" "bli"))) {
					  r((char*)("\03" "ble"));
					  break;
				  }

				  if (ends((char*)("\04" "alli"))) {
					  r((char*)("\02" "al"));
					  break;
				  }
				  if (ends((char*)("\05" "entli"))) {
					  r((char*)("\03" "ent"));
					  break;
				  }
				  if (ends((char*)("\03" "eli"))) {
					  r((char*)("\01" "e"));
					  break;
				  }
				  if (ends((char*)("\05" "ousli"))) {
					  r((char*)("\03" "ous"));
					  break;
				  }
				  break;
		case 'o': if (ends((char*)("\07" "ization"))) {
					  r((char*)("\03" "ize"));
					  break;
				  }
				  if (ends((char*)("\05" "ation"))) {
					  r((char*)("\03" "ate"));
					  break;
				  }
				  if (ends((char*)("\04" "ator"))) {
					  r((char*)("\03" "ate"));
					  break;
				  }
				  break;
		case 's': if (ends((char*)("\05" "alism"))) {
					  r((char*)("\02" "al"));
					  break;
				  }
				  if (ends((char*)("\07" "iveness"))) {
					  r((char*)("\03" "ive"));
					  break;
				  }
				  if (ends((char*)("\07" "fulness"))) {
					  r((char*)("\03" "ful"));
					  break;
				  }
				  if (ends((char*)("\07" "ousness"))) {
					  r((char*)("\03" "ous"));
					  break;
				  }
				  break;
		case 't': if (ends((char*)("\05" "aliti"))) {
					  r((char*)("\02" "al"));
					  break;
				  }
				  if (ends((char*)("\05" "iviti"))) {
					  r((char*)("\03" "ive"));
					  break;
				  }
				  if (ends((char*)("\06" "biliti"))) {
					  r((char*)("\03" "ble"));
					  break;
				  }
				  break;
		case 'g': if (ends((char*)("\04" "logi"))) {
					  r((char*)("\03" "log"));
					  break;
				  } /*-DEPARTURE-*/
				  break;

	}
}

/* paso3() procesa los -ic-, -full, -ness etc. La estrategia es similar al paso 2.
 * Ej:

	(m>0) ICATE	->	IC	triplicate	->	triplic
	(m>0) ATIVE	->		formative	->	form
	(m>0) ALIZE	->	AL	formalize	->	formal
	(m>0) ICITI	->	IC	electriciti	->	electric
	(m>0) ICAL	->	IC	electrical	->	electric
	(m>0) FUL	->		hopeful		->	hope
	(m>0) NESS	->		goodness	->	good
*/
void Stemmer::paso3() {

	switch (b[k])
	{
		case 'e': if (ends((char*)("\05" "icate"))) {
					  r((char*)("\02" "ic"));
					  break;
				  }
				  if (ends((char*)("\05" "ative"))) {
					  r((char*)("\01" "\0"));
					  break;
				  }
				  if (ends((char*)("\05" "alize"))) {
					  r((char*)("\02" "al"));
					  break;
				  }
				  break;
		case 'i': if (ends((char*)("\05" "iciti"))) {
					  r((char*)("\02" "ic"));
					  break;
				  }
				  break;
		case 'l': if (ends((char*)("\04" "ical"))) {
					  r((char*)("\02" "ic"));
					  break;
				  }
				  if (ends((char*)("\03" "ful"))) {
					  r((char*)("\01" "\0"));
					  break;
				  }
				  break;
		case 's': if (ends((char*)("\04" "ness"))) {
					  r((char*)("\01" "\0"));
					  break;
				  }
				  break;
	}
	//	std::cout << "s luego de paso3 -> "<< s << std::endl;
}

/* paso4() quita los -ant, -ence etc., en un contexto <c>vcvc<v>.
 *Ej:
	(m>1) AL				->	revival		->	reviv
	(m>1) ANCE				->	allowance	->	allow
	(m>1) ENCE				->	inference	->	infer
	(m>1) ER				->	airliner	->	airlin
	(m>1) IC				->	gyroscopic	->	gyroscop
	(m>1) ABLE				->	adjustable	->	adjust
	(m>1) IBLE				->	defensible	->	defens
	(m>1) ANT				->	irritant	->	irrit
	(m>1) EMENT				->	replacement	->	replac
	(m>1) MENT				->	adjustment	->	adjust
	(m>1) ENT				->	dependent	->	depend
	(m>1 and (*S or *T)) ION->	adoption	->	adopt
	(m>1) OU				->	homologou	->	homolog
	(m>1) ISM				->	communism	->	commun
	(m>1) ATE				->	activate	->	activ
	(m>1) ITI				->	angulariti	->	angular
	(m>1) OUS				->	homologous	->	homolog
	(m>1) IVE				->	effective	->	effect
	(m>1) IZE				->	bowdlerize	->	bowdler

 *
 * */

void Stemmer::paso4(){

	switch (b[k-1])
    {
		/* faltan procesar todos estos casos */
		case 'a': if (ends((char*)("\02" "al"))) break;
				    return;
		case 'c': if (ends((char*)("\04" "ance"))) break;
				  if (ends((char*)("\04" "ence"))) break;
				  return;
		case 'e': if (ends((char*)("\02" "er"))) break;
				  return;
		case 'i': if (ends((char*)("\02" "ic"))) break;
				  return;
		case 'l': if (ends((char*)("\04" "able"))) break;
				  if (ends((char*)("\04" "ible"))) break;
				  return;
		case 'n': if (ends((char*)("\03" "ant"))) break;
				  if (ends((char*)("\05" "ement"))) break;
				  if (ends((char*)("\04" "ment"))) break;
				  if (ends((char*)("\03" "ent"))) break;
				  return;
		case 'o': if (ends((char*)("\03" "ion")) && (b[j] == 's' || b[j] == 't'))
					break;
				  if (ends((char*)("\02" "ou"))) break;
				  return;
				 /* takes care of -ous */
		case 's': if (ends((char*)("\03" "ism"))) break;
				  return;
		case 't': if (ends((char*)("\03" "ate"))) break;
				  if (ends((char*)("\03" "iti"))) break;
				  return;
		case 'u': if (ends((char*)("\03" "ous"))) break;
				  return;
		case 'v': if (ends((char*)("\03" "ive"))) break;
				  return;
		case 'z': if (ends((char*)("\03" "ize"))) break;
				  return;

		default: return;
    }
	/* si hubo algun resultado positivo, elimino el sufijo correspondiente */
    if (m() > 1)
    	k = j;

}

/* paso5()
 * remueve las -e finales si m() > 1,
 * y cambia -ll por -l si m() > 1.
 * Ej:
  	(m>1) E					->	probate	->	probat
    							rate	->	rate
	(m=1 and not *o) E		->	cease	->	ceas

	(m > 1 and *d and *L)	->	single letter 	controll 	-> control
    		 	 	 	 	 					roll		->	roll
 *
 * */
void Stemmer::paso5(){

	j = k;
	int a = m();

	if (b[k] == 'e'){
		/* remuevo la e final */
		if (a > 1 || ( a == 1 && !cvc(k-1) )){
			k--;
			//setto((char*)("\01" "\0"));
		}
	}
	if (b[k] == 'l' && dobleConsonante(k) && a > 1){
		k--;
		//setto((char*)("\01" "\0"));
	}
   //  std::cout << "s luego de paso5 -> "<< s << std::endl;
}

/* Recibe los parametros y llama a los distintos pasos para procesar a las
 * palabras.
 *
 * @param p : puntero a char que apunta a la palabra a procesar.
 * @param i : es una variable que siempre vale 0. Indica la primera posicion de
 * 			  la palabra procesada.
 * @param j : es el offset a la ultima letra de la palabra.
 *
   The stemmer modifica los caracteres p[i] ... p[j] y devuelve el nuevo punto
   final de la palabra. El tamanio de la palabra procesada siempre sera menor o
   igual a p.

*/

int Stemmer::stem(char * p, int i, int j)
{
	b = p;
	k = j;
	k0 = i;

	/* si la palabra tiene menos de 3 letras salimos */
	if (k <= k0+1)
		return k;

	paso1ab();
	paso1c();
	paso2();
	paso3();
	paso4();
	paso5();
	return k;
}



void Stemmer::increase_s(){

	i_max += INC;

	s.resize(i_max+1);
}

/* aplica el algoritmo de stemmizacion a Archivo.
   Imprime el resultado.
*/
void Stemmer::stemArchivo(FILE * f){

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

				s[i] = ch;
				i++;
				ch = getc(f);
				if (!LETTER(ch)){
					ungetc(ch,f);
					break;
				}
			}
			stem((char*)s.c_str(),0,i-1);

			std::cout << s;
		}
		else putchar(ch);
	}
}

/* aplica el algoritmo de stemming a la palabra pasada como parametro.
   retorna el string resultante.
*/
std::string Stemmer::stemPalabra(std::string w){


	s = w;

	/* lo paso a minusculas */
	std::transform(s.begin(), s.end(), s.begin(), ::tolower);

	int nuevoTamanio = stem((char*)s.c_str(),0,s.size()-1);
	s.resize(nuevoTamanio+1);
	return s;
}


