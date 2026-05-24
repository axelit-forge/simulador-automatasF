#include <stdio.h>

#include "TAD_data.h"

int main2() {

    tData hola = crearDesdeCadena("[[q0,0,{q0,q1}],[q0,1,{q0}],[q1,1,{q2}]]");
    tData soy = crearDesdeCadena("este si");

    mostrarData(soy);
    freeData(soy);

    mostrarData(hola);

    freeData(hola);


    return 0;
}
