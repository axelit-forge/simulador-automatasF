#include "TAD_upla.h"

//Upla 

void Mostrar_Upla(tUpla A){
	mostrarData(A);
}		
	
	
tData transicion(tData ini, tUpla transi, char c) {
	if (transi == NULL || transi->dato == NULL)
		return NULL;
		
	while (transi != NULL) {
		tData sublista = transi->dato;

		tData origen   = obtenerElemento(sublista, 0);
		tData simbolo  = obtenerElemento(sublista, 1);
		tData destino  = obtenerElemento(sublista, 2);

		if (origen != NULL && igualdad(origen, ini) == 0) {
			if (simbolo != NULL && simboloDeData(simbolo) == c) {
				return copiarData(destino);
			}
		}
		transi = transi->sig;
	}
	return NULL;
}	

int Verifica_alfabeto(str Cad, tUpla alfabeto){
	while (Cad != NULL){
		int pertenece = 0;
		tUpla aux = alfabeto;
		
		while(aux != NULL && pertenece == 0){
			char simbolo = simboloDeData(aux->dato);
			
			if (Cad->dato == simbolo){
				pertenece = 1;
			}
			aux = aux->sig;
		}
		
		if (pertenece == 0){
			return 0; 
		}
		Cad = Cad->sig;
	}
	return 1; 
}
	

int seguir(){
	int op;
	
	do{
		printf("\nDesea seguir cargando la upla?\n");
		printf("\nPresione 1 Si");
		printf("\nPresione 0 No");
		printf("\nIngrese su opcion: ");
		scanf("%d",&op);}while (op != 1 && op != 0);
	return op;
}
	
tUpla cargarEstados(){
	tUpla nuevo;
	tData nva;
	nuevo = createSet();
	int b=1;
	
	while (b==1){
	nva=createStr();
	
	printf("\nIngrese el estado: ");
	nva->cad=load();
	agregarData(&nuevo, nva);
	b=seguir();
	}
	
	return nuevo;
}

tUpla cargarAlfabeto(){
	tUpla nuevo;
	tData aux;
	nuevo = createSet();
	int b=1;
	
	while (b==1){
		aux=createStr();
		
		printf("\nIngrese el caracter: ");
		aux->cad=load();
		agregarData(&nuevo, aux);
		b=seguir();
	}
	
	return nuevo;
	
}

tUpla cargarInicial(tUpla Estado){
	tUpla nuevo;
	nuevo = createStr();
	do{
	nuevo->cad=load();
	if(pertenece(Estado,nuevo)==0)
		return nuevo;
	}while(pertenece(Estado,nuevo)==1);
	
return NULL;
}

tUpla cargarFinal(tUpla Estado){
	tUpla nuevo;
	tData aux;
	nuevo = createSet();
	
	int b=1;
	
	while (b==1){
		aux=createStr();
		
		printf("\nIngrese el estado final: ");
		do{
			aux->cad=load();
			if(pertenece(Estado,aux)==0){
				agregarData(&nuevo, aux);
				mostrarData(nuevo);
            }
		}while(pertenece(Estado,aux)==1);
		
		b=seguir();
	}
	return nuevo;
}

tUpla cargarTransicion(tUpla Alfa, tUpla Estado, int a){
	tUpla nuevo,nav, aux1;
	tData aux;
	nuevo = createList();
	nav=createList();
	aux1=Alfa;
	if(a==1){
		aux=createStr();
	}else
		{aux=createSet();}
	
	while(Estado!=NULL){
		Alfa=aux1;
		while(Alfa!=NULL){
			printf("ingrese el destino de:\n Delta(");
			mostrarData(Estado->dato);
			printf(",");
			mostrarData(Alfa->dato);
			printf(")-->");
			
			if(a==1){
				aux->cad=load();
				agregarData(&nav,Estado->dato);
				agregarData(&nav,Alfa->dato);
				agregarData(&nav,aux);
			}
			else
			   {
				aux=cargarEstados();
				agregarData(&nav,Estado->dato);
				agregarData(&nav,Alfa->dato);
				agregarData(&nav,aux);
				
			}
			agregarData(&nuevo, nav);
			
			nav=NULL;
			
			
			Alfa= Alfa->sig;
		} 
		Estado= Estado->sig;
	}
return nuevo;
}
	
tUpla cargarAlfabeto2() {
	tUpla nuevo;
	nuevo = createSet();
	int col=0;
	char linea[TAM];
	char*token;
	
	FILE* file = fopen("Datos.csv", "r");
	if (file == NULL)
		return NULL;

	fgets(linea, sizeof(linea), file);
	linea[strcspn(linea, "\n")] = 0;
	token = strtok(linea, ";");
	
	while (token) {
		if (col > 0) {  // Ignorar "Q/E"
			tData simbolo = createStr();
			simbolo->cad = load2(token);
			agregarData(&nuevo, simbolo);
		}
		token = strtok(NULL, ";");
		col++;
	}
	fclose(file);
	return nuevo;
} 
	
tUpla cargarEstado2() {
	tUpla nuevo = createSet();
	char linea[TAM];
	char *token;
	
	FILE *file = fopen("Datos.csv", "r");
	fgets(linea, sizeof(linea), file);  
	
	while (fgets(linea, sizeof(linea), file)) {
		linea[strcspn(linea, "\n")] = 0;
		token = strtok(linea, ";");
		
		if (token != NULL) {
			
			if (strncmp(token, "->*", 3) == 0) token += 3;
			else if (strncmp(token, "->", 2) == 0) token += 2;
			else if (token[0] == '*') token += 1;
			
			tData aux = createStr();
			aux->cad = load2(token);
			agregarData(&nuevo, aux);
		}
	}
	fclose(file);
	return nuevo;
}
	
tUpla cargarInicial2() {
	tData nuevo = createStr();
	char linea[TAM];
	char *token;
	
	int b = 0;
	
	FILE* file = fopen("Datos.csv", "r");
	
	fgets(linea, sizeof(linea), file); 
	
	while(fgets(linea, sizeof(linea), file) && b == 0){
		linea[strcspn(linea, "\n")] = 0;
		token = strtok(linea, ";");
		
		if (strncmp(token, "->*", 3) == 0){
			token += 3; 
			nuevo->cad = load2(token);
			b = 1;
		}
		else{
			if(strncmp(token, "->", 2) == 0){
				token +=2;
				nuevo->cad = load2(token);
				b =1;
			}
		}
		
	}
	
	fclose(file);
	return nuevo;
}
	
tUpla cargarFinal2() {	
	tUpla nuevo = createSet();
	char linea[TAM];
	char *token;
	
	FILE *file = fopen("Datos.csv", "r");
	fgets(linea, sizeof(linea), file); 
	
	while (fgets(linea, sizeof(linea), file)) {
		linea[strcspn(linea, "\n")] = 0;
		token = strtok(linea, ";");
	
		if (token != NULL) {
			if (strncmp(token, "*", 1) == 0) {
				tData aux = createStr();
				aux->cad = load2(token + 1);  /*salta '*'*/
				agregarData(&nuevo, aux);
			} else if (strncmp(token, "->*", 3) == 0) {
				tData aux = createStr();
				aux->cad = load2(token + 3);  /*salta '->*'*/
				agregarData(&nuevo, aux);
			}
		}
	}
	fclose(file);
	return nuevo;
}
	
	
tUpla cargarTransicion2(tUpla Alfa, tUpla Estados) {
	tUpla nuevo = createList();
	tUpla nav;
	char linea[TAM];
	char *token;
	int col;
	
	FILE* file = fopen("Datos.csv", "r");
	fgets(linea, sizeof(linea), file);  
	fgets(linea, sizeof(linea), file);  
	
	while (Estados != NULL && !feof(file)) {
		linea[strcspn(linea, "\n")] = 0;
		token = strtok(linea, ";");
		
		if (strncmp(token, "->*", 3) == 0) token += 3;
		else if (strncmp(token, "->", 2) == 0) token += 2;
		else if (token[0] == '*') token += 1;
		
		tData estadoOrigen = createStr();
		estadoOrigen->cad = load2(token);
		
		tUpla alfaActual = Alfa;
		col = 0;
		
		while (alfaActual != NULL) {
			token = strtok(NULL, ";");
			if (token == NULL) break;
			
/*			Solo agregamos la transici�n si el destino NO es "*"*/
			if (strcmp(token, "*") != 0) {
				tData simbolo = copiarData(alfaActual->dato);
				tData destino = NULL;
				destino = crearDesdeCadena(token);
				
/*				 Crear la transici�n*/
				nav = createList();
				agregarData(&nav, copiarData(estadoOrigen)); // origen
				agregarData(&nav, simbolo);                  // s�mbolo
				agregarData(&nav, destino);                  // destino
				
				agregarData(&nuevo, nav);
			}
			
			alfaActual = alfaActual->sig;
			col++;
		}
		
		fgets(linea, sizeof(linea), file);
	}
	
	fclose(file);
	return nuevo;
}


