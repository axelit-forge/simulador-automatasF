#ifndef TAD_UPLA_H
#define TAD_UPLA_H
#include <string.h>
#include "TAD_data.h"
#define TAM 100	
typedef tData tUpla;

tUpla Carga_Upla();
void Mostrar_Upla(tUpla);

//Analisis de cadena
tData transicion(tData,tUpla,char);
int Verifica_alfabeto(str, tUpla);

//Cargas de automata
tUpla cargarEstados();
tUpla cargarAlfabeto();
tUpla cargarInicial(tUpla);
tUpla cargarFinal(tUpla);
tUpla cargarTransicion(tUpla,tUpla,int);


tUpla cargarContenidoCSV(const char*);

#endif
