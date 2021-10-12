#include <iostream>
#include "LLista.hpp"

using namespace std;

int main(){

    LLista lLL = LLista();

    lLL.insert("Accion");
    lLL.insert("SciFi", "Dune");
    lLL.insert("SciFi", "Quinto Elemento");
    lLL.insert("Drama", "En busca de la felicidad");
    lLL.insert("SciFi", "The Matrix");
    lLL.insert("Drama", "Animales nocturnos");
    lLL.insert("Accion", "Men in Black");
    lLL.insert("Fantasia", "El senior de los anillos");
    lLL.del("Drama", "Animales nocturnos", false);
    lLL.show();

    return 0;
}    