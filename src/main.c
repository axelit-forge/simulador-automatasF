#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "TAD_automata.h"

int main() {
	char entrada[256];

	const char* rutaCSV = "tests/Datos.csv";
	tAF miAutomata = cargaCSV(rutaCSV);

	printf("\n--- Estructura del Autómata Cargado ---\n");
	Mostrar_aut(miAutomata);
	printf("\n----------------------------------------\n");

	while (1) {
		printf("\nIngrese una cadena para evaluar (o '-1' para salir): ");
		if (scanf("%255s", entrada) != 1) break;

		if (strcmp(entrada, "-1") == 0) {
			break;
		}

		str cad = load2(entrada);

		Verifica_cad(miAutomata, cad);

		freeString(cad);
	}

	freeAut(miAutomata);
	printf("\nPrograma finalizado correctamente.\n");
	return 0;
}
	
int mensaje(){
	int op;
	printf("Elija como cargar el automata:\n");
	printf("1-Por consola\n");
	printf("2-Pre-cargado\n");
	printf("3-Por archivo Excel\n");
	printf("Ingrese opcion:");
	scanf("%d",&op);
	return op;
}

	
void Menu(tAF *A){
	int op;

	op=mensaje();
	system("cls");
	switch(op){
	case 1:*A =Cargar_Consola();break;
	case 2:*A =Cargar_hard();break;
	case 3:*A =cargaCSV("tests/Datos4.csv");break;
	}
	
}
