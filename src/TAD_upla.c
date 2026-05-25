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
				return destino;
			}
		}
		transi = transi->sig;
	}
	return NULL;
}	

int Verifica_alfabeto(str Cad, tUpla alfabeto) {
	str auxCad = Cad;

	while (auxCad) {
		char charCadena = auxCad->dato;
		tUpla auxAlf = alfabeto;
		int encontrado = 0;

		while (auxAlf != NULL) {
			char charAlfabeto = simboloDeData(auxAlf->dato);

			if (charCadena == charAlfabeto) {
				encontrado = 1;
				break;
			}
			auxAlf = auxAlf->sig;
		}

		if (encontrado == 0) {
			printf("[ERROR] El símbolo '%c' no pertenece al alfabeto del autómata.\n", charCadena);
			return 0;
		}

		auxCad = auxCad->sig;
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
	freeData(nva);
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
		freeData(aux);
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
				freeData(aux);
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
			freeData(aux);
			agregarData(&nuevo, nav);
			
			freeData(nav);
			nav = NULL;
			
			Alfa= Alfa->sig;
		} 
		Estado= Estado->sig;
	}
return nuevo;
}

tUpla cargarContenidoCSV(const char* Ruta) {
	//salvese quien pueda :'v
	FILE* file = fopen(Ruta, "r");
	if (file == NULL) {
		printf("Error: No se pudo abrir %s\n", Ruta);
		return NULL;
	}
	tUpla Contenido = createList();

	tUpla Alfabeto=createSet(), Estados=createSet(), Finales=createSet(), inicial=NULL, Transiciones=createList();

	char linea[1024];
	int col = 0;
	int fila = 0;
	char* token;

	while (fgets(linea, sizeof(linea), file)) {
		linea[strcspn(linea, "\r\n")] = 0;
		token = strtok(linea, ";");

		col= 0;
		while (token) {

			if (fila==0 && col>0) {				//agregamos el alfabeto

				tData simbolo = crearDesdeCadena(token);
				agregarData(&Alfabeto, simbolo);
				freeData(simbolo);

			}
			if (col==0 && fila != 0) {			//agregamos los estados
				tData estado;
				if (strncmp(token, "->*", 3) == 0){				//es final e inicial
					token += 3;
					estado = crearDesdeCadena(token);
					agregarData(&Finales, estado);
					inicial = copiarData(estado);
				}

				else if (strncmp(token, "->", 2) == 0) {		//es inicial
					token += 2;
					estado = crearDesdeCadena(token);
					inicial = copiarData(estado);
				}
				else if (token[0] == '*') {								//es final
					token += 1;
					estado = crearDesdeCadena(token);
					agregarData(&Finales, estado);
				}
				else {													//es un estadocomun
					estado = crearDesdeCadena(token);
				}

				agregarData(&Estados, estado);
				freeData(estado);
			}
			if (col!=0 && fila !=0) {			//agregamos las transiciones

				if (strcmp(token, "*") != 0){
					tData transicionSingular = createList();
					tData origen = obtenerElemento(Estados,fila-1);
					tData simbolo = obtenerElemento(Alfabeto,col-1);
					tData destino = crearDesdeCadena(token);

					agregarData(&transicionSingular, origen);
					agregarData(&transicionSingular, simbolo);
					agregarData(&transicionSingular, destino);

					agregarData(&Transiciones, transicionSingular);
					freeData(destino);
					freeData(transicionSingular);
				}
			}

			token = strtok(NULL, ";");
			col++;
		}
		fila++;
	}

	agregarData(&Contenido, Estados);
	agregarData(&Contenido, Alfabeto);
	agregarData(&Contenido, Transiciones);
	agregarData(&Contenido, inicial);
	agregarData(&Contenido, Finales);

	freeData(Alfabeto);freeData(Estados);freeData(Finales);freeData(inicial);freeData(Transiciones);

	fclose(file);
	return Contenido;
}