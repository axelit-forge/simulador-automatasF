#ifndef TAD_AUTOMATA_H
#define TAD_AUTOMATA_H
#include "TAD_upla.h"


typedef struct{
	tUpla ConjE;
	tUpla Alfabeto;
	tUpla Delta;
	tUpla Inicial;
	tUpla ConjA;
}tAF;

void Mostrar_aut(tAF);
void MostrarUpla(tAF);
void Verifica_cad(tAF);

tAF Cargar_hard();
tAF Cargar_Consola();
tAF cargaCSV(const char*);

tAF ConversionAF(tAF A);
void renombramiento(tAF *A, int option);

void  freeAut(tAF A);


#endif
