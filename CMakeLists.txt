cmake_minimum_required(VERSION 3.20)
project(simulador_automata C)

set(CMAKE_C_STANDARD 99)

add_executable(simulador_automata
    src/main.c
    src/TAD_automata.c
    src/TAD_upla.c
    src/Tad_data.c
    src/TAD_string.c
)

target_include_directories(simulador_automata PRIVATE include)
