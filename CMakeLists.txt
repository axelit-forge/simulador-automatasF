cmake_minimum_required(VERSION 3.20)
project(simulador_automata C)

set(CMAKE_C_STANDARD 99)

add_executable(simulador_automata
    src/main.c
    src/TAD_automata.c
    src/TAD_upla.c
        src/TAD_data.c
    src/TAD_string.c
        src/test_data.c
)

target_include_directories(simulador_automata PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/includes
        ${CMAKE_CURRENT_SOURCE_DIR}/tests
)
