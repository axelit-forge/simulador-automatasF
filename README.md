# Simulador de Autómatas Finitos (DFA / NFA)

Un motor modular desarrollado en C para procesar y simular el comportamiento de Autómatas Finitos Deterministas y No Deterministas. El sistema está diseñado para ser completamente genérico, abstrayendo la lógica del autómata de los datos de entrada.

## Cómo funciona
* **Carga por archivo:** El simulador lee y parsea las tablas de transiciones desde archivos externos `.csv` guardados en la carpeta `tests/`.
* **Modularización por TADs:** Implementación basada en estructuras y contratos propios en C para gestionar de forma aislada los estados, las tuplas, las cadenas y los datos del autómata.
* **Procesamiento:** El motor recorre la cadena sobre el alfabeto definido y determina si es aceptada o rechazada por el autómata configurado.
* **Gestión de Memoria Segura:** Código testeado a bajo nivel, garantizando la ausencia de fugas de memoria (*0 leaks*).

## Formato del Archivo CSV

El parser del simulador espera una matriz de transición clásica. La estructura debe respetar el orden de filas y columnas, utilizando prefijos específicos para identificar los estados iniciales y finales:

###  Diseño de la Matriz (Ejemplo)
* **Primera fila:** Contiene únicamente los símbolos del alfabeto.
* **Primera columna:** Contiene los nombres de los estados. Se usa el prefijo `->` para el estado inicial y `*` para los estados finales (de aceptación).
* **Celdas:** Indican el estado destino.

| Estados | 0 | 1 |
| :--- | :---: | :---: |
| **->q0** | q1 | q0 |
| ***q1** | q0 | q1 |

---

### 📄 Representación en el Archivo Plano (`Datos.csv`)

Al trasladar la matriz al archivo físico, **no se deben incluir espacios en blanco, comillas ni encabezados extras**. La celda de la esquina superior izquierda se omite, arrancando la primera línea directamente con los símbolos del alfabeto:

```csv
Q\E:0;1
->q0;q1;q0
*q1;q0;q1
```

## Estructura del proyecto
* `/src`: Archivos de código fuente (`.c`) con la lógica del motor de transiciones y el punto de entrada principal.
* `/include`: Cabeceras (`.h`) con las definiciones de las estructuras y firmas de los TADs.
* `/tests`: Casos de prueba y archivos `.csv` con las matrices de transición de los autómatas de ejemplo.

## Estado actual y próximos pasos
* [x] Depuración de memoria: Fugas de memoria e inseguridades de punteros corregidas por completo. El ciclo de vida de los TADs está blindado bajo entornos de prueba rigurosos en Valgrind (0 bytes in use at exit).
* [x] Construcción Automatizada: Migración exitosa al flujo de compilación nativo con CMake.
* [ ] Revisar la opcion de renombramiento 1.

## Entorno y compilación
* **Lenguaje:** C (C99 nativo)
* **OS/Compilador:** GCC sobre WSL2 (Ubuntu)
* **Herramienta de construcción:** Automatizado con CMake (compatible con CLion).

Para compilar y correr el proyecto de forma directa por terminal sin usar CMake, parate en la raíz del proyecto y ejecutá:

```bash
# Compilación enlazando todas las dependencias e incluyendo las cabeceras
gcc src/main.c src/TAD_automata.c src/TAD_upla.c src/Tad_data.c src/TAD_string.c -o simulador.out -Iinclude
# O bien, con CMake
# Crear y entrar al directorio de compilación
mkdir build && cd build

# Generar los archivos de construcción y compilar
cmake ..
make

# Ejecución del binario
./simulador.out
```
## Verificacion de memoria
* Para verificar que el Heap se mantiene limpio durante el procesamiento interactivo de cadenas, puedes ejecutar:
```bash
valgrind --leak-check=full --show-leak-kinds=all ./simulador
```

*Mantenido por [axelit-forge](https://github.com/axelit-forge)*
