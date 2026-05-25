#include "TAD_automata.h"

int Delta_ND(str Cad, tAF A) {
	tData act = createSet();
	agregarData(&act, A.Inicial);

	while (Cad && act) {
		tData nuevos = createSet();
		tData trav = act;

		while (trav) {
			tData trans = transicion(trav->dato, A.Delta, Cad->dato);

			if (trans != NULL) {
				tData unionTmp = Union(nuevos, trans);
				if (nuevos) freeData(nuevos);
				nuevos = unionTmp;
			}
			trav = trav->sig;
		}
		freeData(act);
		act = nuevos;
		Cad = Cad->sig;
	}
	if (act == NULL) return 0;
	tData Resultado = Interseccion(A.ConjA, act);
	int esAceptada = 0;

	if (Resultado != NULL) {
		if (Resultado->dato != NULL) {
			esAceptada = 1;
		}
		freeData(Resultado);
	}
	freeData(act);
	return esAceptada;
}

int Delta_D(str Cad, tAF A){
	tData act = A.Inicial;
	
	while(Cad!=NULL ){
		act = transicion(act, A.Delta, Cad->dato);
		if (!act) return 0;
		Cad=Cad->sig;
	}
	return pertenece(A.ConjA, act);
}
	
int esDet(tAF A) {
	if (A.Delta == NULL) return 1;

	tData trav = A.Delta;

	while (trav) {

		tData tripla = trav->dato;
		if (tripla) {
			tData destino = obtenerElemento(tripla, 2);
			if (destino != NULL && destino->tipoNodo == SET) {
				return 0;
			}
		}
		trav = trav->sig;
	}
	return 1;
}

void Mostrar_aut(tAF B){
	printf("A =( ");
	Mostrar_Upla(B.ConjE);
	printf("\n");
	Mostrar_Upla(B.Alfabeto);
	printf("\n");
	Mostrar_Upla(B.Delta);
	printf("\n");
	Mostrar_Upla(B.Inicial);
	printf("\n");
	Mostrar_Upla(B.ConjA);
	printf(")\n");
}	
	
	
void Verifica_cad(tAF B){
	if (B.Delta == NULL) return;

	printf("\nIngrese cadena: ");
	str cad = load();

	if (Verifica_alfabeto(cad, B.Alfabeto)) {
		int aceptada = 0;

		if (esDet(B) == 1)
			aceptada = Delta_D(cad, B);
		else
			aceptada = Delta_ND(cad, B);


		if (aceptada)
			printf("\nLa cadena ingresada es aceptada\n");
		else
			printf("\nLa cadena ingresada no es aceptada\n");
	}

	freeString(cad);
}
tAF Cargar_hard(){
	tAF nue;
	tData arbol, aux;
	int c;
	printf("Seleccione estados DT O NDT(0 o 1):");
	scanf("%d",&c);
	if(c==0){
		arbol=crearDesdeCadena("[{q0,q1},{0,1},[[q0,0,q1],[q0,1,q0],[q1,0,q0],[q1,1,q1]],q0,{q1}]");
	}
	else{
		arbol=crearDesdeCadena("[{q0,q1,q2},{0,1},[[q0,0,{q0,q1}],[q0,1,{q0}],[q1,1,{q2}]],q0,{q2}]");
	}
	nue.ConjE= arbol->dato;
	aux = arbol;
	arbol = arbol->sig;
	free(aux);
	
	nue.Alfabeto=arbol->dato;
	aux= arbol;
	arbol=arbol->sig;
	free(aux);
	
	nue.Delta=arbol->dato;
	free(arbol);
	arbol=arbol->sig;
	free(aux);
	
	nue.Inicial=arbol->dato;
	aux= arbol;
	arbol=arbol->sig;
	free(aux);
	
	nue.ConjA=arbol->dato;
	free(arbol);
	

return nue;
}

tAF Cargar_Consola(){
	tAF nuevo;
	int b;
	
	printf("Estados:");
	nuevo.ConjE= cargarEstados();
	printf("\nAlfabeto:");
	nuevo.Alfabeto=cargarAlfabeto();
	printf("\nEstado inicial:");
	nuevo.Inicial=cargarInicial(nuevo.ConjE);
	printf("\nEstados finales:");
	nuevo.ConjA=cargarFinal(nuevo.ConjE);
	printf("\nTransiciones:");
	printf("Desea cargar 1- AFD 2-AFND :");scanf("%d",&b);
	nuevo.Delta=cargarTransicion(nuevo.Alfabeto,nuevo.ConjE,b);
	return nuevo;
}


void MostrarUpla(tAF B){
	int op;
	do{
	
	printf("\nIngrese que Upla desea ver:\n");
	printf("1-Alfabeto\n");
	printf("2-Estados\n");
	printf("3-Estados finales\n");
	printf("4-Estado inicial\n");
	printf("5-Transiciones\n");
	printf("6-Salir\n");
	printf("Ingrese opcion:");
	scanf("%d",&op);
	
	switch(op){
	case 1:Mostrar_Upla(B.Alfabeto);break;
	case 2:Mostrar_Upla(B.ConjE);break;
	case 3:Mostrar_Upla(B.ConjA);break;
	case 4:Mostrar_Upla(B.Inicial);break;
	case 5:Mostrar_Upla(B.Delta);break;
	case 6:printf("Volviendo al menu...\n");break;
	default:printf("Error de ingreso");break;
	}
	}while(op!=6);
}


tAF cargaCSV(const char* rutaCSV) {
	tAF Aut;

	tUpla contenido = cargarContenidoCSV(rutaCSV);

	if (contenido) {
		Aut.ConjE    = copiarData(obtenerElemento(contenido, 0));
		Aut.Alfabeto = copiarData(obtenerElemento(contenido, 1));
		Aut.Delta    = copiarData(obtenerElemento(contenido, 2));
		Aut.Inicial  = copiarData(obtenerElemento(contenido, 3));
		Aut.ConjA    = copiarData(obtenerElemento(contenido, 4));

		freeData(contenido);
	}
	else
		Aut.ConjE = Aut.Alfabeto = Aut.Inicial = Aut.ConjA = Aut.Delta = NULL;

	return Aut;
}
void freeAut(tAF A) {
	freeData(A.Alfabeto);
	freeData(A.Inicial);
	freeData(A.Delta);
	freeData(A.ConjE);
	freeData(A.ConjA);
}

tData creaResidual(){
	tData nvo = createSet();
	nvo->dato= createStr();
	nvo->dato->cad = load2("-R");
	return nvo;
}


tData BuscameT(tUpla Est,tUpla delta,tUpla alf){
	char c = simboloDeData(alf->dato);
	
	while(Est!=NULL){
		tData temp;
		temp = transicion(Est->dato, delta, c);
		
		if(temp == NULL){
			return Est->dato;
		}
		Est = Est->sig;
	}
	
	return NULL;
}

tData RetornaEstado(tData nvoE,tUpla Delta,char a){
	tData aux = NULL;
	tData nuevos = NULL;
	while(nvoE!=NULL){
		aux=nvoE->dato;
		
		tData trans = transicion(aux,Delta,a);
		tData unionTmp = Union(nuevos, trans);
		freeData(nuevos);  
		nuevos = unionTmp;
		
		
		nvoE = nvoE->sig;
		
	}
	return nuevos;
}	
	

tAF ConversionAF(tAF A){
	if (esDet(A) == 1) return A;
	
	tData nvoE,auxAlf;
	
	tData origen, caracter , destino , transicion;
	
	tAF B;
	
	B.Alfabeto= copiarData(A.Alfabeto);
	
	B.Inicial = createSet();
	B.Inicial->dato = copiarData(A.Inicial);
	B.ConjE = createSet();
	B.Delta = createList();
	B.ConjA = createSet();
	
	agregarData(&B.ConjE,B.Inicial);
	
	while(BuscameT(B.ConjE,B.Delta,B.Alfabeto)){
		
		nvoE = BuscameT(B.ConjE,B.Delta,B.Alfabeto);
		auxAlf = B.Alfabeto;
		while(auxAlf!=NULL){
			
			char car = simboloDeData(auxAlf->dato);
			destino = RetornaEstado(nvoE,A.Delta,car);
			
			origen = copiarData(nvoE);
			caracter = createStr();
			caracter->cad->dato= car;
			
			transicion= createList();
			
			if(destino == NULL){
				destino = creaResidual();
			}
			
			agregarData(&transicion, origen);
			agregarData(&transicion, caracter);
			agregarData(&transicion, destino);
			
			agregarData(&B.Delta, transicion);
			auxAlf = auxAlf->sig;
			
			
			agregarData(&B.ConjE, destino);
			
			freeData(origen);
			freeData(caracter);
			freeData(destino);
			freeData(transicion);
		}
		
	}
	
	tData finales = B.ConjE;
	
	while(finales != NULL){
		tData temp = Interseccion(finales->dato, A.ConjA);
		if( temp != NULL){
			agregarData(&B.ConjA, finales->dato);
			freeData(temp);
		}
		finales = finales->sig;
	}
	
	renombramiento(&B, 1);
	
	
	return B;
}
	
tData buscarRenombre(tData original, tUpla listaCambios) {
	while (listaCambios != NULL) {
		tData par = listaCambios->dato;
		tData viejo = obtenerElemento(par, 0);
		tData nuevo = obtenerElemento(par, 1);
		
		if (viejo != NULL && igualdad(viejo, original) == 0) {
			return nuevo;
		}
		listaCambios = listaCambios->sig;
	}
	return copiarData(original);
}	
	
tUpla renombrarTransiciones(tUpla Delta, tUpla listaCambios) {
	tUpla nuevoDelta = createList();
	while (Delta != NULL) {
		tData trans = Delta->dato;
		tData origen = buscarRenombre(trans->dato, listaCambios);
		tData simbolo = copiarData(trans->sig->dato);
		tData destino = buscarRenombre(trans->sig->sig->dato, listaCambios);
		
		tData nuevaTrans = createList();
		agregarData(&nuevaTrans, copiarData(origen));
		agregarData(&nuevaTrans, simbolo);
		agregarData(&nuevaTrans, copiarData(destino));
		
		agregarData(&nuevoDelta, nuevaTrans);
		Delta = Delta->sig;
	}
	return nuevoDelta;
}
tUpla renombrarConjunto(tUpla conjuntoOriginal, tUpla listaCambios) {
	tUpla nuevo = createSet();
	while (conjuntoOriginal != NULL) {
		tData nuevoElem = buscarRenombre(conjuntoOriginal->dato, listaCambios);
		agregarData(&nuevo, copiarData(nuevoElem));
		conjuntoOriginal = conjuntoOriginal->sig;
	}
	return nuevo;
}	

tData crearP(int p) {
	tData nvo = createStr();
	char buffer[10];
	sprintf(buffer, "P%d", p);
	
	nvo->cad = load2(buffer);
	return nvo;
}
	
void renombramiento(tAF *A, int option){
	tData listaCambios = createList();
	
	tUpla conjuntos = A->ConjE;
	int p = 0;
	
	while(conjuntos != NULL){
		tData Cambio = createList();
		
		agregarData(&Cambio, conjuntos->dato);
		if(option == 1){
			agregarData(&Cambio, toString(conjuntos->dato));
		}
		else{
		   agregarData(&Cambio, crearP(p));
		   p++;
		}
		
		agregarData(&listaCambios, Cambio);
		
		conjuntos = conjuntos->sig;
	}
	
	A->ConjE = renombrarConjunto(A->ConjE, listaCambios);
	A->ConjA = renombrarConjunto(A->ConjA, listaCambios);
	A->Inicial = copiarData(A->ConjE->dato);
	
	
	A->Delta = renombrarTransiciones(A->Delta, listaCambios);
	
	freeData(listaCambios);
}

	
	
