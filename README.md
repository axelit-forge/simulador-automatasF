# Simulador de Autómatas Finitos (DFA / NFA)

Un motor modular desarrollado en C para procesar y simular el comportamiento de Autómatas Finitos Deterministas y No Deterministas. El sistema está diseñado para ser completamente genérico, abstrayendo la lógica del autómata de los datos de entrada.

## Cómo funciona
* **Carga por archivo:** El simulador lee y parsea las tablas de transiciones desde archivos externos `.csv` guardados en la carpeta `tests/`.
* **Modularización por TADs:** Implementación basada en estructuras y contratos propios en C para gestionar de forma aislada los estados, las tuplas, las cadenas y los datos del autómata.
* **Procesamiento:** El motor recorre la cadena sobre el alfabeto definido y determina si es aceptada o rechazada por el autómata configurado.

## Estructura del proyecto
* `/src`: Archivos de código fuente (`.c`) con la lógica del motor de transiciones y el punto de entrada principal.
* `/include`: Cabeceras (`.h`) con las definiciones de las estructuras y firmas de los TADs.
* `/tests`: Casos de prueba y archivos `.csv` con las matrices de transición de los autómatas de ejemplo.

## Estado actual y próximos pasos
* [ ] **Depuración de memoria (Prioridad Máxima):** Corregir fugas de memoria y errores de segmentación (`Segmentation Fault` / `malloc corruption`) detectados al procesar cadenas largas en el entorno WSL2.
* [ ] **Optimización del parser:** Robustecer la lectura de los archivos `.csv` para manejar excepciones de formato de manera controlada.
* [ ] **Refactorizacion casi completa:** Revisar a detalle la estructura completa para garantizar el correcto funcionamiento utilizando Valgrind

## Entorno y compilación
* **Lenguaje:** C (C99 nativo)
* **OS/Compilador:** GCC sobre WSL2 (Ubuntu)
* **Herramienta de construcción:** Automatizado con CMake (compatible con CLion).

Para compilar y correr el proyecto de forma directa por terminal sin usar CMake, parate en la raíz del proyecto y ejecutá:

```bash
# Compilación enlazando todas las dependencias e incluyendo las cabeceras
gcc src/main.c src/TAD_automata.c src/TAD_upla.c src/Tad_data.c src/TAD_string.c -o simulador.out -Iinclude

# Ejecución del binario
./simulador.out
```

*Mantenido por [axelit-forge](https://github.com/axelit-forge)*
