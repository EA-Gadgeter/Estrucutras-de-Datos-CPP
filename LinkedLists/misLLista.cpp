#include <iostream>
#include "LLista.hpp"

using namespace std;

int main(){

    

    LLista lLL = LLista();

    lLL.read("aaaa.txt");

    lLL.show();

    /*lLL.insert("Accion");
    lLL.insert("SciFi", "Dune");
    lLL.insert("SciFi", "Quinto Elemento");
    lLL.insert("Drama", "En busca de la felicidad");
    lLL.insert("SciFi", "The Matrix");
    lLL.insert("Drama", "Animales nocturnos");
    lLL.insert("Accion", "Men in Black");
    lLL.insert("Fantasia", "El senior de los anillos");
    lLL.show();
    lLL.write("aaaa.txt");
    */

    return 0;
}    