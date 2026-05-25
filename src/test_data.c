#include <stdio.h>

#include "TAD_upla.h"

int main() {
    printf("--- Iniciando prueba de carga de CSV ---\n");

    // Pasamos la ruta relativa desde la raíz del proyecto
    const char* ruta = "tests/Datos7.csv";

    tUpla contenido = cargarContenidoCSV(ruta);


    mostrarData(contenido);
    freeData(contenido);



    return 0;
}



