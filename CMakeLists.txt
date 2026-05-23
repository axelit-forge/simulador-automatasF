cmake_minimum_required(VERSION 3.20)
project(simulador_automata)

set(CMAKE_C_STANDARD 99)

add_executable(simulador-automata
        TAD_string.c
        Tad_data.c
        TAD_upla.c
        TAD_automata.c
        main.c
)