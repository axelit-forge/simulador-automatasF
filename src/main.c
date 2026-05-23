#include "TAD_automata.h"
void Menu();
	
int main(){

	tAF A = Cargar_hard();
	Mostrar_aut(A);
	Verifica_cad(A);
	
	
	tAF B = ConversionAF(A);
	
	
	Mostrar_aut(B);
	Verifica_cad(B);
	
	
	renombramiento(&B, 2);
	Mostrar_aut(B);
	
	Verifica_cad(B);
	
	
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
	case 3:*A =Cargar_desde_excel();break;
	}
	
}
