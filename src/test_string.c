
#include <stdio.h>
#include "../includes/TAD_string.h"

int main() {
    str s1 = load2("Hola");
    str s2 = load2("Soy");
    str s3 = load2("Hola soy una cadena");


    int booleano = isin(s1,s3);
    printf("test 1: %d \n",booleano);

    int booleano2 = isin(s2,s3);
    printf("test 2: %d \n",booleano2);

    int booleano3 = isin(s3,s1);
    printf("test 2: %d \n",booleano3);


    freeString(s1);
    freeString(s2);
    freeString(s3);


    return 0;
}


//
// Created by PC on 24/05/2026.
//
