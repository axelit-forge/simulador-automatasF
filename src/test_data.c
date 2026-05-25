#include <stdio.h>

#include "TAD_data.h"

int main() {

    tData hola = crearDesdeCadena("{a,b,c}");
    tData soy = crearDesdeCadena("{b,c,d}");
    tData uniOn = Union(hola, soy);
    tData uniOn2 = Interseccion(hola, soy);
    tData uniOn3 = Diferencia(hola, soy);
    tData uniOn4 = DifSimetrica(hola, soy);

    mostrarData(soy);
    freeData(soy);

    mostrarData(hola);

    freeData(hola);

    mostrarData(uniOn);
    mostrarData(uniOn2);
    mostrarData(uniOn3);
    mostrarData(uniOn4);

    freeData(uniOn);
    freeData(uniOn2);
    freeData(uniOn3);
    freeData(uniOn4);
    return 0;
}
