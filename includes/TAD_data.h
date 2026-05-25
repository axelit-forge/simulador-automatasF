#ifndef TAD_DATA_H
#define TAD_DATA_H

#include "TAD_string.h"
#define STR 1
#define LIST 2
#define SET 3


typedef struct nodo_data{
	int tipoNodo;
	union{
		str cad;
		struct{
			struct nodo_data * dato;
			struct nodo_data * sig;
		};
	};
}TNodoData;

typedef TNodoData * tData;


tData createData(int);
tData createList();
tData createSet();
tData createStr();

//funciones nucleo
int igualdad(tData, tData);
tData copiarData(tData);
void mostrarData(tData);
void agregarData(tData*, tData);
void freeData(tData);
tData cargar();
tData crearArbol(int, int);
tData __conjuntoAString(tData);

//operaciones de conjunto
tData Union (tData, tData);
tData Interseccion (tData, tData);
tData Diferencia (tData, tData);
tData DifSimetrica (tData, tData);
int pertenece(tData,tData);
int cardinalidad (tData);
int contenido (tData, tData);


//funcion de cargar por cadena
tData crearDesdeCadena(const char*);

//funciones auxiliares de AF
char simboloDeData(tData);
tData obtenerElemento(tData, int);

#endif
