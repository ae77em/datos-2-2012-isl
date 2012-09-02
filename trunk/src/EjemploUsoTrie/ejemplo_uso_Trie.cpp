#include <iostream>
#include <string>
#include "trie.h"
#include <fstream>

using namespace std;

int main(int argc, char *argv[])
{
     Trie arbolTrie;

     string fede="fede";
     int* direccion= new int;

     //meto barbie en el TRIE
     arbolTrie.insertarPalabraEnRaiz("barbie",direccion);
     string avion="avion";
     arbolTrie.insertarPalabraEnRaiz(avion,direccion);

     arbolTrie.insertarPalabraEnRaiz(fede,direccion);
     arbolTrie.insertarPalabraEnRaiz(fede,direccion);
     arbolTrie.insertarPalabraEnRaiz(fede,direccion);

     string federico="federico";
     arbolTrie.insertarPalabraEnRaiz(federico,direccion);


     arbolTrie.insertarPalabraEnRaiz("fedirico",direccion);
     string bardo="bardo";
     string barbie="barbie";
     string banco="banco";
     string baul="baul";
     string bazos="bazos";

     arbolTrie.insertarPalabraEnRaiz(bardo,direccion);

     arbolTrie.insertarPalabraEnRaiz(banco,direccion);

     arbolTrie.insertarPalabraEnRaiz(barbie,direccion);

     arbolTrie.insertarPalabraEnRaiz(bazos,direccion);
     arbolTrie.insertarPalabraEnRaiz(baul,direccion);
     arbolTrie.insertarPalabraEnRaiz("aviun",direccion);

     arbolTrie.insertarPalabraEnRaiz(barbie,direccion);


     string zapato="zapato";
     arbolTrie.insertarPalabraEnRaiz(zapato,direccion);

     string zanahoria="zanahoria";
     arbolTrie.insertarPalabraEnRaiz(zanahoria,direccion);

     string barca="barca";
     arbolTrie.insertarPalabraEnRaiz(barca,direccion);

    //hasta aca es la simulacion de un archivo qie contendria las palabras ingresadas
    //el sgte metodo controla y recopila informacion de las palabras ingresadas durante el parseo del archivo anterior
     cout<<"\ncomienza 1er recorrido en profundidad del arbol\n\n"<<endl;
     arbolTrie.buscarPalabrasDeLaParseada_INI();

        //aqui empezaria la apertura y parseo de un nuevo archivo
     arbolTrie.insertarPalabraEnRaiz(fede,direccion);
     arbolTrie.insertarPalabraEnRaiz("federico",direccion);
     arbolTrie.insertarPalabraEnRaiz("z",direccion);

    //segundo control
     cout<<"\ncomienza 2do recorrido en profundidad del arbol\n\n"<<endl;
     arbolTrie.buscarPalabrasDeLaParseada_INI();

     arbolTrie.insertarPalabraEnRaiz(fede,direccion);
     arbolTrie.insertarPalabraEnRaiz("federico",direccion);
     arbolTrie.insertarPalabraEnRaiz("yoyo",direccion);
     arbolTrie.insertarPalabraEnRaiz(fede,direccion);
     arbolTrie.insertarPalabraEnRaiz("federico",direccion);
     arbolTrie.insertarPalabraEnRaiz("z",direccion);

    //TERCER control
     cout<<"\ncomienza 3er recorrido en profundidad del arbol\n\n"<<endl;
     arbolTrie.buscarPalabrasDeLaParseada_INI();

     //archivo para exportar el contenido del arbol trie
     fstream salida;
     salida.open("listadoDePalabras.txt",fstream::out);

     arbolTrie.exportarPalabras_INI(&salida);

     salida.close();

     cout<<"\nDESTRUYENDO ARBOL"<<endl;

     arbolTrie.destruirArbol_INI();

     return 0;
}
