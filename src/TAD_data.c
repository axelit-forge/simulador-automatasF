#include "TAD_data.h"

tData createData(int tipo){
	tData nvo;
	nvo = (tData) malloc (sizeof(TNodoData));
	
	if(tipo == STR){
		nvo->cad = NULL;
		nvo->tipoNodo = STR;
	}
	else {
		nvo->dato = NULL;
		nvo->sig = NULL;
		nvo->tipoNodo = tipo;
	}
	return nvo;
}
tData createList(){
	return createData(LIST);
}
tData createSet(){
	return createData(SET);
}	
tData createStr(){
	return createData(STR);
}

void mostrarData(tData nodo){
	
	if(!nodo) return;

	tData trav = NULL;

	switch(nodo->tipoNodo){
	case STR: 
		print(nodo->cad);
		break;
	case LIST:
		printf("[");

		trav= nodo;
		while(trav != NULL){
			mostrarData(trav->dato);
			if(trav->sig != NULL)
				printf(",");
			trav = trav->sig;
		}
		printf("]");
		
		break;
	case SET:
		printf("{");

		trav= nodo;
		while(trav != NULL){
			mostrarData(trav->dato);
			if(trav->sig != NULL)
				printf(",");
			trav = trav->sig;
		}
		printf("}");
		break;
		default:break;
	}
}

void agregarData(tData* cab, tData elem){

	if (!(*cab) || (*cab)->tipoNodo == STR || !elem) return;

	if ( (*cab)->dato == NULL) {
		(*cab)->dato = copiarData(elem);
		return;
	}
	tData aux;

	switch ((*cab)->tipoNodo) {
	case SET:
		aux = *cab;

		if(pertenece(aux, elem) == 0) {
			while (aux->sig)
				aux = aux->sig;
			aux->sig = createSet();
			aux = aux->sig;
			aux->dato = copiarData(elem);
		}
	break;
	case LIST:
		aux = *cab;

		while (aux->sig)
			aux = aux->sig;

		aux->sig = createList();
		aux = aux->sig;
		aux->dato = copiarData(elem);
	break;
	default: break;
	}

}	
	
//funciones nucleo	
tData copiarData (tData copiado){
	tData nvo = NULL;
	if (copiado == NULL) return nvo;
	
	switch (copiado->tipoNodo){
	case STR:
		nvo = createStr();
		nvo->cad = copyStr(copiado->cad);
		break;
	case LIST:
		nvo = createList();
		nvo->dato = copiarData( copiado->dato);
		nvo->sig = copiarData (copiado ->sig);
		break;
	case SET:
		nvo = createSet();
		nvo->dato = copiarData( copiado->dato);
		nvo->sig = copiarData (copiado ->sig);
		break;
	}
	
	return nvo;
}	
	
void freeData(tData descartado){
	
	if (descartado == NULL) return;
	
	switch (descartado->tipoNodo){
	case STR:
		freeString(descartado->cad);
		break;
	case LIST:
	case SET:
		freeData(descartado->dato);
		freeData(descartado->sig);
		break;
	}
	
	free(descartado);
}
	
int igualdad(tData A, tData B){
		
	if(!A && !B) return 0;
	if(!A || !B || (A->tipoNodo != B->tipoNodo)) return 1;

	tData trav1 = NULL, trav2 = NULL;
	switch(A->tipoNodo){
	case STR:
		return compStr(A->cad,B->cad);

	case SET:
		trav1 = A;
		while(trav1){
			if(pertenece(B, trav1->dato) == 0)
				return 1;
			trav1 = trav1->sig;
		}
		trav1 = B;
		while(trav1){
			if(pertenece(A, trav1->dato) == 0)
				return 1;
			trav1 = trav1->sig;
		}
		return 0;
	break;
	case LIST:
		trav1 = A;
		trav2 = B;

		while(trav1 && trav2){
			if(igualdad(trav1->dato, trav2->dato) != 0)
				return 1;
			trav1 = trav1->sig;
			trav2 = trav2->sig;
			}
			if(trav1 || trav2)
				return 1;

			return 0;
	break;
	default: break;
	}
	return 0;
}

tData Cargar (){
	tData nvo = NULL;
	
	nvo = crearArbol(0, 0);
	
	return nvo;
}	

void mostrarTipo(int tipo){
	switch(tipo){
	case 1: printf("string"); break;
	case 2: printf("list"); break;
	case 3: printf("set"); break;
	default: printf("Sin tipo");
	}
}
	
int retornaTipo(){
	int op;
	do{printf("\nQue desea agregar");
	printf("\nPresione 1 cadena");
	printf("\nPresione 2 lista");
	printf("\nPresione 3 conjunto");
	printf("\nIngrese su opcion: ");
	scanf("%d",&op);}while (op!= 1 && op != 2 && op != 3);
	return op;
}	
int continuar(int nivel){
	int op;
	
	do{
	printf("\nDesea seguir cargando en nivel %d", nivel);
	printf("\nPresione 1 Si");
	printf("\nPresione 0 No");
	printf("\nIngrese su opcion: ");
	scanf("%d",&op);}while (op != 1 && op != 0);
	return op;
}
	
tData crearArbol(int nivel, int tipo){
	int op;
	tData nva=NULL;
	
	printf("\n Se encuentra en el nivel : %d", nivel);
	printf("\n El tipo de dato en este nivel es : ");
	mostrarTipo(tipo);
	op=retornaTipo();

	if(op!=STR){
		nva = createData(op);
		do {
			tData hijo = crearArbol(nivel + 1, op);
			agregarData(&nva, hijo);
		} while (continuar(nivel+1) == 1);
	}
	else{
		nva=createStr();
		printf("Ingrese la cadena: ");
		nva->cad=load();
		return nva;
	}
	return nva;
}
//conjuntos
	
tData Union (tData A, tData B){
	if (A == NULL)
		return copiarData(B);
	if(B == NULL)
		return copiarData(A);	
	
	if (A->tipoNodo != SET || B->tipoNodo != SET)
		return NULL;

	tData C = createSet();
	while (A) {
		agregarData(&C, A->dato);
		A = A->sig;
	}
	while (B) {
		agregarData(&C, B->dato);
		B = B->sig;
	}
	return C; /*
	tData C_Cab = NULL, C_act = NULL;
	tData aux;
	
	while(A != NULL){
		
		aux= createSet();
		aux->dato = copiarData(A->dato);
		
		if(C_Cab == NULL) C_Cab = aux;
		else C_act->sig = aux;
		
		C_act= aux;
		
		A = A->sig;
	}
	while(B != NULL){
		
		if(pertenece(C_Cab, B->dato)){
			
			aux= createSet();
			aux->dato = copiarData(B->dato);
			
			if(C_Cab == NULL) C_Cab = aux;
			else C_act->sig = aux;
			
			C_act= aux;
			
		}
		B = B->sig;
	}
	
	return C_Cab;*/
}

tData Interseccion (tData A, tData B){
	if (A == NULL || B == NULL)
		return NULL;
	
	if (A->tipoNodo != SET || B->tipoNodo != SET)
		return NULL;
	tData C_Cab = NULL, C_act = NULL;
	tData aux;
	while(A != NULL){
		
		if(! pertenece(B, A->dato)){
			
			aux= createSet();
			aux->dato = copiarData(A->dato);
			
			if(C_Cab == NULL) C_Cab = aux;
			else C_act->sig = aux;
			
			C_act= aux;
			
		}
		A = A->sig;
	}
	return C_Cab;
}

tData Diferencia (tData A, tData B){
	if (A == NULL)
		return NULL;
	if (B == NULL)
		return copiarData(A);
	
	if (A->tipoNodo != SET || B->tipoNodo != SET)
		return NULL;
	
	tData C_Cab = NULL, C_act = NULL;
	tData aux;
	while(A != NULL){
		
		if( pertenece(B, A->dato)){
			
			aux= createSet();
			aux->dato = copiarData(A->dato);
			
			if(C_Cab == NULL) C_Cab = aux;
			else C_act->sig = aux;
			
			C_act= aux;
			
		}
		A = A->sig;
	}
	return C_Cab;
}

tData DifSimetrica (tData A, tData B){
	if (A->tipoNodo != SET || B->tipoNodo != SET)
		return NULL;
	
	tData D = Diferencia(A, B);
	tData E = Diferencia(B, A);
	
	tData F = NULL;
	F = Union (D, E);
	
	
	return F;
}

int pertenece(tData A, tData elem){
	if (!A || A->tipoNodo == STR) return 0;
	if (!elem) return 1;
		
	tData aux = A;
	while (aux != NULL) {
		if (igualdad(aux->dato, elem) == 0)
			return 1;
		aux = aux->sig;
	}
	
	return 0;
}

int contenido(tData A, tData B){

	while(A != NULL){
		if(pertenece(B, A->dato) == 0)
			return 0;
		A = A->sig;
	}
	return 1;
}

int cardinalidad (tData A){
	
	if (A == NULL || A->tipoNodo != SET)
		return 0;
	
	int c= 0;
	while(A!= NULL){
		c++;
		A = A->sig;
	}
	return c;
}

tData __procesadoCadena(str * origen) {
	if (!origen) return NULL;

	tData nuevo=NULL;
	switch ((*origen)->dato) {
		case '{':
			nuevo = createSet();
			*origen = (*origen)->sig;
			while ((*origen)->dato != '}') {
				tData elemento = __procesadoCadena(origen);
				agregarData(&nuevo, elemento);
				freeData(elemento);

				if ((*origen)->dato == ',') *origen = (*origen)->sig;

			}
			*origen = (*origen)->sig;

		break;
		case '[':
			nuevo = createList();
			*origen = (*origen)->sig;
			while ((*origen)->dato != ']') {
				tData elemento = __procesadoCadena(origen);
				agregarData(&nuevo, elemento);
				freeData(elemento);

				if ((*origen)->dato == ',') *origen = (*origen)->sig;
			}
			*origen = (*origen)->sig;

		break;
		default:
			nuevo = createStr();
			str head =NULL;
			str ultimo=NULL;

			while ((*origen) != NULL && (*origen)->dato != ',' && (*origen)->dato != '}' && (*origen)->dato != ']') {

				str nvo_caracter = create();
				nvo_caracter->dato = (*origen)->dato;

				if (!head)
					head = nvo_caracter;
				else
					ultimo->sig = nvo_caracter;

				ultimo = nvo_caracter;
				*origen = (*origen)->sig;
			}
			nuevo->cad = head;
		break;
	}
	return  nuevo;
}

int __llavesEqui (const char* revisar) {
	int i = 0;

	int simpilaCorchet = 0;
	int simpilaLLave = 0;
	if (revisar[0] != '{' && revisar[0] != '[')
		return 0;

	while (revisar[i]!= '\0') {
		if (revisar[i] == '{') simpilaLLave++;
		if (revisar[i] == '[') simpilaCorchet++;
		if (revisar[i] == '}') simpilaLLave--;
		if (revisar[i] == ']') simpilaCorchet--;
		if (simpilaCorchet<0 ||  simpilaLLave<0) return 0;

		i++;
	}
	return  (simpilaLLave == 0 && simpilaCorchet == 0);
}

tData crearDesdeCadena(const char *input) {
	tData resultado = NULL;
	int bienDefinido = __llavesEqui(input);
	if (bienDefinido){
		str cadenaInput = load2(input);
		str copia = cadenaInput;
		resultado = __procesadoCadena(&copia);
		freeString(cadenaInput);
	}
	else {
		resultado = createStr();
		resultado->cad = load2(input);
	}
	return resultado;
}


char simboloDeData(tData a){				//devuelve solo el primer cad
	if(!a || a->tipoNodo != STR)
		return '\0';
	else
		return a->cad->dato;
}
	
tData toString(tData H) {					//revisar para que funcione, de todas formas no es util en el programa
	tData nvo = createStr();

	str resultado = create(); 
	resultado->dato = '{';
	
	str actual = resultado;  
	
	while (H != NULL) {
		if (H->dato != NULL && H->dato->cad != NULL) {
			str copiado = copyStr(H->dato->cad);
			
			while (actual->sig != NULL) actual = actual->sig;
			actual->sig = copiado;
			
			while (actual->sig != NULL) actual = actual->sig;
			
			if (H->sig != NULL) {
				actual->sig = create();
				actual = actual->sig;
				actual->dato = ',';
			}
		}
		H = H->sig;
	}
		
	actual->sig = create();
	actual = actual->sig;
	actual->dato = '}';
	
	nvo->cad = resultado;
	return nvo;
}

tData obtenerElemento(tData lista, int pos) {
	for (int i = 0; i < pos && lista; i++) {
		lista = lista->sig;
	}
	return (lista) ? lista->dato : NULL;
}	
