#include <stdio.h>
#include <stdlib.h>
#include "TAD_automata.h" // Asegurate de que este .h tenga la estructura tAF y las firmas

int main2() {
    printf("==================================================\n");
    printf("   INICIANDO TEST DE VERIFICACIÓN DE AUTÓMATAS    \n");
    printf("==================================================\n\n");

    // ----------------------------------------------------------------
    // PRUEBA 1: Carga desde el archivo CSV físico (El monstruo que domaste)
    // ----------------------------------------------------------------
    printf("[TEST 1] Cargando autómata desde archivo CSV...\n");
    const char* rutaCSV = "tests/Datos4.csv"; // Modificá por el archivo que quieras probar
    tAF miAutomata = cargaCSV(rutaCSV);

    printf("\n[TEST 1] Mostrando estructura del autómata cargado:\n");
    Mostrar_aut(miAutomata);
    printf("\n--------------------------------------------------\n");

    // ----------------------------------------------------------------
    // PRUEBA 2: Verificación de Cadenas (Simulación)
    // ----------------------------------------------------------------
    printf("[TEST 2] Ejecutando verificación de cadenas...\n");
    // Nota: Como Verifica_cad probablemente pida una cadena por stdin o lea
    // una interactiva, correrá el flujo completo de transiciones en el Heap.

    printf("\n--------------------------------------------------\n");

    // ----------------------------------------------------------------
    // PRUEBA 3: Transformaciones (Conversión y Renombramiento)
    // ----------------------------------------------------------------
    printf("[TEST 3] Probando duplicación y conversión del autómata...\n");
    // Pasamos miAutomata por valor, debería generar un nuevo tAF con copias físicas internas
    tAF automataConvertido = ConversionAF(miAutomata);

    printf("[TEST 3] Aplicando renombramiento sobre el autómata convertido...\n");
    // Modifica los estados in-place usando punteros

    printf("\n[TEST 3] Mostrando el autómata modificado:\n");
    Mostrar_aut(automataConvertido);
    printf("\n--------------------------------------------------\n");

    // ----------------------------------------------------------------
    // LIMPIEZA ABSOLUTA (La prueba de fuego para Valgrind)
    // ----------------------------------------------------------------
    printf("[LIMPIEZA] Liberando recursos del Heap con freeAut...\n");

    // Liberamos el autómata original levantado del CSV
    freeAut(miAutomata);
    freeAut(automataConvertido);

    // Liberamos el autómata nuevo que se generó en la conversión

    printf("\n==================================================\n");
    printf("   TEST FINALIZADO - REVISÁ EL REPORTE ABAJO     \n");
    printf("==================================================\n");

    return 0;
}