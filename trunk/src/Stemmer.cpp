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
}

Stemmer::~Stemmer(){}

/* esConsonante(i) es true <=> palabraEnProcesamiento[i] es una consonante. */
int Stemmer::esConsonante(int i){

	switch (palabraEnProcesamiento[i])
	{
		case 'a': case 'e': case 'i': case 'o': case 'u':
			return false;
		case 'y':
			return (i==posPrimeraLetra) ? true : !esConsonante(i-1);
		default:
			return true;
	}
}

/* m() mide la cantidad de secuencias de consonantes entre posPrimeraLetra y posUltimaLetra. Si c es
   una secuencia de consonantes y v una secuencia de vocales, y <..> indica
   valores arbitrarios. m se refiere a la medida de estas secuencias, bajo el
   siguiente criterio

      <c><v>       retorna 0
      <c>vc<v>     retorna 1
      <c>vcvc<v>   retorna 2
      <c>vcvcvc<v> retorna 3
      ....
*/
int Stemmer::m(){

	int n = 0;
	int i = posPrimeraLetra;

	while(true){
		if (i > posUltimaLetra)
			return n;
		if ( not esConsonante(i))
			break;
		i++;
	}
	i++;
	while(true){
		while(true){
			if (i > posUltimaLetra)
				return n;
			if (esConsonante(i))
				break;
			i++;
	  }
	  i++;
	  n++;
	  while(true){
		  if (i > posUltimaLetra)
			  return n;
		  if ( not esConsonante(i))
			  break;
		  i++;
	  }
	  i++;
	}
}

/* vocalEnStem() es true <=> posPrimeraLetra,...posUltimaLetra contiene una vocal */
int Stemmer::vocalEnStem(){

	int i;
	for (i = posPrimeraLetra; i <= posUltimaLetra; i++)
		if (! esConsonante(i))
			return true;

	return false;
}

/* dobleConsonante(posUltimaLetra) es true <=> posUltimaLetra,(posUltimaLetra-1) contiene una consonate doble. */
int Stemmer::dobleConsonante(int posUltimaLetra){

	if (posUltimaLetra < posPrimeraLetra+1)
		return false;

	if (palabraEnProcesamiento[posUltimaLetra] != palabraEnProcesamiento[posUltimaLetra-1])
		return false;

	return esConsonante(posUltimaLetra);
}

/* cvc(i) es true <=> i-2,i-1,i tiene la forma consonante - vocal - consonante
   y tambien si la segunda consonante no es w,x or y. Se usa cuando queremos
   restaurar una e al final de una palabra corta.
   Ej:

      cav(e), lov(e), hop(e), crim(e), but
      snow, box, tray.

*/
int Stemmer::cvc(int i){

	if (i < posPrimeraLetra+2 || !esConsonante(i) || esConsonante(i-1) || !esConsonante(i-2))
		return false;
	{
		int ch = palabraEnProcesamiento[i];
		if (ch == 'w' || ch == 'x' || ch == 'y')
			return false;
	}
	return true;
}

/* terminaCon( s) es true si el substring del intervalo <=> posPrimeraLetra,...tamanioFinal en palabraEnProcesamiento es s. */

int Stemmer::terminaCon( int length, std::string str){

	if (str[length-1] != palabraEnProcesamiento[tamanioFinal])
		return false;

	if (length > tamanioFinal-posPrimeraLetra+1)
		return false;

	if (str.compare(0,length,palabraEnProcesamiento,tamanioFinal-length+1,length) != 0)
		return false;

	posUltimaLetra = tamanioFinal-length;

	return true;
}

/* cambiarPor(s) cambia s en el rango (posUltimaLetra+1),...tamanioFinal por los pasados por parametro,
   ajustando tamanioFinal.
 */
void Stemmer::cambiarPor(int length,std::string str)
{
	/* reemplazo el string correspondiente */
	palabraEnProcesamiento.replace(posUltimaLetra+1,length,str);

	tamanioFinal = posUltimaLetra+length;
}

/* este metodo es llamado en los pasos 2 y 3 */
void Stemmer::r(int length, std::string s) {

	if (m() > 0)
		cambiarPor(length,s);
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

	if (palabraEnProcesamiento[tamanioFinal] == 's'){
		if ( terminaCon( 4, std::string("sses")))
			tamanioFinal -= 2;
		else
		if ( terminaCon( 3, std::string("ies")))
			cambiarPor(1, std::string("i"));
		else
		if (palabraEnProcesamiento[tamanioFinal-1] != 's')
			tamanioFinal--;
	}

	if ( terminaCon( 3, std::string("eed"))) {
		if (m() > 0)
			tamanioFinal--;
	}
	else
	if (vocalEnStem()){
		bool salir = true;
		/* elimino los sufijos que sobran */
		if( terminaCon( 2, std::string("ed"))){
			cambiarPor(1, std::string("\0"));
			salir=false;
		}
		else if( terminaCon( 3, std::string("ing"))){
			cambiarPor(1, std::string("\0"));
			salir=false;
		}

		if ( not salir ){
			tamanioFinal = posUltimaLetra;
			if ( terminaCon( 2, std::string("at")))
				cambiarPor(3, std::string("ate"));
			else
			if ( terminaCon( 2, std::string("bl")))
				cambiarPor(3, std::string("ble"));
			else
			if ( terminaCon( 2, std::string("iz")))
				cambiarPor(3, std::string("ize"));
			else
			if (dobleConsonante(tamanioFinal))
			{
				tamanioFinal--;
				{
					int ch = palabraEnProcesamiento[tamanioFinal];
					if (ch == 'l' || ch == 's' || ch == 'z')
						tamanioFinal++;
				}
			}
			else
			if (m() == 1 && cvc(tamanioFinal))
				cambiarPor(1, std::string("e"));
		}
	}
}

/* paso1c() cambia las y finales por i cuando está precedida de una vocal
 * por ej:
 * 		play -> plai
 */
void Stemmer::paso1c() {

	if ( terminaCon( 1, std::string("y")) && vocalEnStem())
		palabraEnProcesamiento[tamanioFinal] = 'i';
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

	switch (palabraEnProcesamiento[tamanioFinal-1])
	{
		case 'a': if ( terminaCon( 7, std::string("ational"))) {
					  r(3, std::string("ate"));
					  break;
				  }
				  if ( terminaCon( 6, std::string("tional"))) {
					  r(4, std::string("tion"));
					  break;
				  }
				  break;
		case 'c': if ( terminaCon( 4, std::string("enci"))) {
					  r(4, std::string("ence"));
					  break;
				  }
				  if ( terminaCon( 4, std::string("anci"))) {
					  r(4, std::string("ance"));
					  break;
				  }
				  break;
		case 'e': if ( terminaCon( 4, std::string("izer"))) {
					  r(3, std::string("ize"));
					  break;
				  }
				  break;
		case 'l': if ( terminaCon( 3, std::string("bli"))) {
					  r(3, std::string("ble"));
					  break;
				  }

				  if ( terminaCon( 4, std::string("alli"))) {
					  r(2, std::string("al"));
					  break;
				  }
				  if ( terminaCon( 5, std::string("entli"))) {
					  r(3, std::string("ent"));
					  break;
				  }
				  if ( terminaCon( 3, std::string("eli"))) {
					  r(1, std::string("e"));
					  break;
				  }
				  if ( terminaCon( 5, std::string("ousli"))) {
					  r(3, std::string("ous"));
					  break;
				  }
				  break;
		case 'o': if ( terminaCon( 7, std::string("ization"))) {
					  r(3, std::string("ize"));
					  break;
				  }
				  if ( terminaCon( 5, std::string("ation"))) {
					  r(3, std::string("ate"));
					  break;
				  }
				  if ( terminaCon( 4, std::string("ator"))) {
					  r(3, std::string("ate"));
					  break;
				  }
				  break;
		case 's': if ( terminaCon( 5, std::string("alism"))) {
					  r(2, std::string("al"));
					  break;
				  }
				  if ( terminaCon( 7, std::string("iveness"))) {
					  r(3, std::string("ive"));
					  break;
				  }
				  if ( terminaCon( 7, std::string("fulness"))) {
					  r(3, std::string("ful"));
					  break;
				  }
				  if ( terminaCon( 7, std::string("ousness"))) {
					  r(3, std::string("ous"));
					  break;
				  }
				  break;
		case 't': if ( terminaCon( 5, std::string("aliti"))) {
					  r(2, std::string("al"));
					  break;
				  }
				  if ( terminaCon( 5, std::string("iviti"))) {
					  r(3, std::string("ive"));
					  break;
				  }
				  if ( terminaCon( 6, std::string("biliti"))) {
					  r(3, std::string("ble"));
					  break;
				  }
				  break;
		case 'g': if ( terminaCon( 4, std::string("logi"))) {
					  r(3, std::string("log"));
					  break;
				  }
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

	switch (palabraEnProcesamiento[tamanioFinal])
	{
		case 'e': if ( terminaCon( 5, std::string("icate"))) {
					  r(2, std::string("ic"));
					  break;
				  }
				  if ( terminaCon( 5, std::string("ative"))) {
					  r(1, std::string("\0"));
					  break;
				  }
				  if ( terminaCon( 5, std::string("alize"))) {
					  r(2, std::string("al"));
					  break;
				  }
				  break;
		case 'i': if ( terminaCon( 5, std::string("iciti"))) {
					  r(2, std::string("ic"));
					  break;
				  }
				  break;
		case 'l': if ( terminaCon( 4, std::string("ical"))) {
					  r(2, std::string("ic"));
					  break;
				  }
				  if ( terminaCon( 3, std::string("ful"))) {
					  r(1, std::string("\0"));
					  break;
				  }
				  break;
		case 's': if ( terminaCon( 4, std::string("ness"))) {
					  r(1, std::string("\0"));
					  break;
				  }
				  break;
	}
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

	switch (palabraEnProcesamiento[tamanioFinal-1])
    {
		/* faltan procesar todos estos casos */
		case 'a': if ( terminaCon( 2, std::string("al"))) break;
				    return;
		case 'c': if ( terminaCon( 4, std::string("ance"))) break;
				  if ( terminaCon( 4, std::string("ence"))) break;
				  return;
		case 'e': if ( terminaCon( 2, std::string("er"))) break;
				  return;
		case 'i': if ( terminaCon( 2, std::string("ic"))) break;
				  return;
		case 'l': if ( terminaCon( 4, std::string("able"))) break;
				  if ( terminaCon( 4, std::string("ible"))) break;
				  return;
		case 'n': if ( terminaCon( 3, std::string("ant"))) break;
				  if ( terminaCon( 5, std::string("ement"))) break;
				  if ( terminaCon( 4, std::string("ment"))) break;
				  if ( terminaCon( 3, std::string("ent"))) break;
				  return;
		case 'o': if ( terminaCon( 3, std::string("ion")) && (palabraEnProcesamiento[posUltimaLetra] == 's' || palabraEnProcesamiento[posUltimaLetra] == 't'))
					break;
				  if ( terminaCon( 2, std::string("ou"))) break;
				  return;
				 /* takes care of -ous */
		case 's': if ( terminaCon( 3, std::string("ism"))) break;
				  return;
		case 't': if ( terminaCon( 3, std::string("ate"))) break;
				  if ( terminaCon( 3, std::string("iti"))) break;
				  return;
		case 'u': if ( terminaCon( 3, std::string("ous"))) break;
				  return;
		case 'v': if ( terminaCon( 3, std::string("ive"))) break;
				  return;
		case 'z': if ( terminaCon( 3, std::string("ize"))) break;
				  return;

		default: return;
    }
	/* si hubo algun resultado positivo, elimino el sufijo correspondiente */
    if (m() > 1)
    	tamanioFinal = posUltimaLetra;

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

	posUltimaLetra = tamanioFinal;
	int a = m();

	if (palabraEnProcesamiento[tamanioFinal] == 'e'){
		/* remuevo la e final */
		if (a > 1 || ( a == 1 && !cvc(tamanioFinal-1) ))
			tamanioFinal--;

	}
	if (palabraEnProcesamiento[tamanioFinal] == 'l' && dobleConsonante(tamanioFinal) && a > 1)
		tamanioFinal--;

}

/* Recibe los parametros y llama a los distintos pasos para procesar a las
 * palabras.
 *
 * @param p : puntero a char que apunta a la palabra a procesar.
 * @param i : es una variable que siempre vale 0. Indica la primera posicion de
 * 			  la palabra procesada.
 * @param posUltimaLetra : es el offset a la ultima letra de la palabra.
 *
   The stemmer modifica los caracteres p[i] ... p[posUltimaLetra] y devuelve el nuevo punto
   final de la palabra. El tamanio de la palabra procesada siempre sera menor o
   igual a p.

*/

int Stemmer::stem(std::string p, int i, int posUltimaLetra)
{
	palabraEnProcesamiento = p;
	tamanioFinal = posUltimaLetra;
	posPrimeraLetra = i;

	/* si la palabra tiene menos de 3 letras salimos */
	if (tamanioFinal <= posPrimeraLetra+1)
		return tamanioFinal;

	paso1ab();
	paso1c();
	paso2();
	paso3();
	paso4();
	paso5();

	s = palabraEnProcesamiento;
	return tamanioFinal;
}



void Stemmer::increase_s(){

	i_max += INC;

	s.resize(i_max+1);
}

/* aplica el algoritmo de stemming a la palabra pasada como parametro.
   retorna el string resultante.
*/
std::string Stemmer::stemPalabra(std::string w) {
	s = w;

	/* lo paso a minusculas */
	std::transform(s.begin(), s.end(), s.begin(), ::tolower);

	int nuevoTamanio = stem( s , 0 , s.size()-1 );
	s.resize(nuevoTamanio+1);
	return s;
}


