#include <stdlib.h>
#include <stdio.h>

typedef int dato_t;

typedef struct nodo_s {
    struct nodo_s* sig;
    dato_t dato;
} Nodo_S;

typedef Nodo_S* Lista_S;

#define lista_isempty(lista) (*lista==NULL)

/*Acepta lista vacia: si.*/
Nodo_S* lista_simple_insertar_inicio(Lista_S* lista, dato_t dato) {
    Nodo_S* nuevo = (Nodo_S*)malloc(sizeof(Nodo_S));
    if(nuevo!=NULL) {
        nuevo->dato=dato;
        nuevo->sig=*lista;
        *lista = nuevo;
    };
    return nuevo;
}

/*Acepta lista vacia: si*/
Nodo_S* lista_simple_insertar_fin(Lista_S* lista, dato_t dato) {
    if(lista_isempty(lista)) 
        return lista_simple_insertar_inicio(lista, dato);
    Nodo_S* ultimo=*lista;
    while(ultimo->sig!=NULL) ultimo=ultimo->sig;
    Nodo_S* nuevo = (Nodo_S*)malloc(sizeof(Nodo_S));
    if(nuevo!=NULL) {
        nuevo->dato=dato;
        nuevo->sig=NULL;
        ultimo->sig=nuevo;
    }
    return ultimo->sig;
}

/*Acepta lista vacia: no, checar si *lista==NULL*/
void lista_simple_eliminar_inicio(Lista_S* lista) {
    Nodo_S* primero = *lista;
    *lista = (*lista)->sig;
    free(primero);
    return;
}

/*Acepta lista vacia:no, checar si *lista==NULL*/
void lista_simple_eliminar_fin(Lista_S* lista) {
    if((*lista)->sig!=NULL) {
        Nodo_S *previo=*lista, *ultimo=(*lista)->sig;
        while(ultimo->sig!=NULL) {
            previo=ultimo;
            ultimo=ultimo->sig;
        }
        previo->sig=NULL;
        free(ultimo);
    } else {
        lista_simple_eliminar_inicio(lista);
    }
    return;
}

void lista_simple_print(Lista_S* lista, void (*print_elem)(dato_t)) {
    fputc('[', stdout);
    Nodo_S* ptr = *lista;
    if(ptr!=NULL) {
        print_elem(ptr->dato);
        ptr=ptr->sig;
    }
    while(ptr!=NULL) {
        fputs(", ", stdout);
        print_elem(ptr->dato);
        ptr=ptr->sig;
    }
    fputc(']', stdout);
    return;
}

void print_elemento(dato_t dato) {
    printf("%d", dato);
    return;
}

Nodo_S *obtener_final(Nodo_S *actual){
    while(actual != NULL && actual->sig != NULL){
        actual = actual->sig;
    }
    return actual;
}

Nodo_S *particion(Nodo_S *lista, Nodo_S *final, Nodo_S **nuevalista, Nodo_S **nuevofinal){
    Nodo_S *pivote = final;
    Nodo_S *anterior = NULL;
    Nodo_S *actual = lista;
    Nodo_S *cola = pivote;

    while (actual != pivote){
        if(actual->dato < pivote->dato){
            if(*nuevalista == NULL){
                *nuevalista = actual;
            }
            anterior = actual;
            actual = actual->sig;
        }else{
            if (anterior){
                anterior->sig = actual->sig;
            }
            Nodo_S *temporal = actual->sig;
            actual->sig = NULL;
            cola->sig = actual;
            cola = actual;
            actual = temporal;
        }
    }
    if(*nuevalista == NULL){
        *nuevalista = pivote;
    }
    *nuevofinal = cola;
    return pivote;
}

Nodo_S *quickSortRecursivo(Nodo_S *lista, Nodo_S *final){
    if(!lista || lista == final){
        return lista;
    }
    Nodo_S *nuevalista = NULL, *nuevofinal = NULL;
    Nodo_S *pivote = particion(lista, final, &nuevalista, &nuevofinal);

    if(nuevalista != pivote){
        Nodo_S *temporal = nuevalista;
        while(temporal->sig != pivote){
            temporal = temporal->sig;
        }
        temporal->sig = NULL;
        nuevalista = quickSortRecursivo(nuevalista, temporal);
        temporal = obtener_final(nuevalista);
        temporal->sig = pivote;
    }

    pivote->sig = quickSortRecursivo(pivote->sig, nuevofinal);
    return nuevalista;
}


void quickSort_ascendente(Lista_S *lista){
    *lista = quickSortRecursivo(*lista, obtener_final(*lista));
}

Nodo_S *invertir_lista (Nodo_S *lista){
    Nodo_S *anterior = NULL;
    Nodo_S *actual = lista;
    Nodo_S *siguiente = NULL;
    while(actual != NULL){
        siguiente = actual->sig;
        actual->sig = anterior;
        anterior = actual;
        actual = siguiente;
    }
    return anterior;
}



#define EDLIB_MAIN
#include "edlib.h"

int main(void) {
    static const char* titulo = "ALGORITMOS DE LISTAS ENCADENADAS\n";
    static const char* menu =
    "1) Insertar por el principio\n"
    "2) Insertar por el fin\n"
    "3) Eliminar por el principio\n"
    "4) Eliminar por el fin\n"
    "5) Ordenar de forma acendente\n"
    "6) Ordenar de forma decendente\n"
    "7) Salir\n";
    Lista_S lista = NULL;
    int opc, val;
    for(;;) {
        clear();
        fputs(titulo, stdout);
        printf("Lista: "); lista_simple_print(&lista, print_elemento);
        fputs("\n\n", stdout); fputs(menu, stdout);
        opc = validar_uint_en_rango(1, 7);
        switch(opc) {
        case 1:
            fputs("Valor Entero", stdout); val =  validar_int(); 
            lista_simple_insertar_inicio(&lista, val);
            break;
        case 2:
            fputs("Valor Entero", stdout); val =  validar_int(); 
            lista_simple_insertar_fin(&lista, val);
            break;
        case 3:
            if(lista!=NULL) {
                lista_simple_eliminar_inicio(&lista);
            } else {
                fputs("No es posible eliminar un elemento"
                    " de la lista vacia\n", stdout);
                flush();
            }
            break;
        case 4:
            if(lista!=NULL) {
                lista_simple_eliminar_fin(&lista);
            } else {
                fputs("No es posible eliminar un elemento"
                    " de la lista vacia\n", stdout);
                flush();
            }
            break;
        case 5:
            quickSort_ascendente(&lista);
            fputs("Lista ordenada de forma ascendente", stdout);
            flush();
            break;
        case 6:
            quickSort_ascendente(&lista);
            lista = invertir_lista(lista);
            fputs("Lista ordenada de forma descendente", stdout);
            flush();
            break;
        case 7:
            exit(EXIT_SUCCESS);
            break;
        }
    }
}