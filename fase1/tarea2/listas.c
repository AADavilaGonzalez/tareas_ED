#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

typedef int dato_t;

/*Lista Simplemente Encadenada*/
typedef struct nodo_s {
    struct nodo_s* sig;
    dato_t dato;
} Nodo_S;

typedef Nodo_S* Lista_S;

#define lista_isempty(lista) (*lista==NULL)

/*Acepta lista vacia: si.*/
Nodo_S* lista_simple_insertar_inicio(Lista_S* lista, dato_t dato) {
    Nodo_S* nuevo = (Nodo_S*)malloc(sizeof(Nodo_S));
    if(!nuevo) return NULL;
    nuevo->dato=dato;
    nuevo->sig=*lista;
    *lista = nuevo;
    return nuevo;
}

/*Acepta lista vacia: si*/
Nodo_S* lista_simple_insertar_fin(Lista_S* lista, dato_t dato) {
    if(lista_isempty(lista)) return lista_simple_insertar_inicio(lista, dato);
    Nodo_S *previo=*lista;
    while(previo->sig!=NULL) previo=previo->sig;
    previo->sig = nodo_simple_crear(dato, NULL);
    return previo->sig;
}

/*Acepta lista vacia: no, checar si *lista==NULL*/
void lista_simple_eliminar_inicio(Lista_S* lista) {
    Nodo_S* basura = *lista;
    *lista = (*lista)->sig;
    free(basura);
    return;
}

/*Acepta lista vacia:no, checar si *lista==NULL*/
void lista_simple_eliminar_fin(Lista_S* lista) {
    if((*lista)->sig!=NULL) {
        Nodo_S *previo=NULL, *basura=*lista;
        while(basura->sig!=NULL) {
            previo=basura;
            basura=basura->sig;
        }
        free(basura);
        return;
    }
    lista_simple_eliminar_inicio(lista);
    return;
}

/*Lista Doblemente Encadenada*/
typedef struct nodo_d {
    struct nodo_d* sig;
    struct nodo_d* prev;
    dato_t dato;
} Nodo_D;

typedef Nodo_D* Lista_D;

/*Nodo_D* nodo_doble_crear(dato_t dato, Nodo_D* previo, Nodo_D* siguiente) {
    Nodo_D* nodo = (Nodo_D*)malloc(sizeof(Nodo_D));
    if(!nodo) return NULL;
    nodo->dato = dato;
    nodo->prev = previo;
    nodo->sig  = siguiente;
    return nodo;
}*/ 

/*Acepta lista vacia: si*/
Nodo_D* lista_doble_insertar_inicio(Lista_D* lista, dato_t dato) {
    Nodo_D* nuevo = (Nodo_D*)malloc(sizeof(Nodo_D));
    if(!nuevo) return NULL;
    nuevo->dato=dato;
    nuevo->prev=NULL;
    nuevo->sig=*lista;
    if(*lista!=NULL) {
        (*lista)->prev=nuevo;
    }
    *lista = nuevo;
    return nuevo;
}

/*Acepta lista vacia: si*/
Nodo_D* lista_doble_insertar_final(Lista_D* lista, dato_t dato) {
    if(lista_isempty(lista)) return lista_doble_insertar_inicio(lista, dato);
    Nodo_D* previo = *lista;
    while(previo->sig!=NULL) previo=previo->sig;
    Nodo_D* nuevo =  (Nodo_D*)malloc(sizeof(Nodo_D));
    if(!nuevo) return NULL;
    nuevo->dato=dato;
    nuevo->sig=NULL;
    nuevo->prev=previo;
    previo->sig=nuevo;
    return nuevo;
}

void lista_doble_eliminar_inicio(Lista_D* lista) {
    Nodo_D* basura=*lista;
    *lista=(*lista)->sig;
    (*lista)->prev = NULL;
    free(basura);
    return *lista;
}

void lista_doble_eliminar_fin(Lista_D* lista) {
    if((*lista)->sig!=NULL) {
        Nodo_D* basura=*lista, *previo;
        while(basura->sig!=NULL) basura=basura->sig;
        previo=basura->prev;
        previo->sig=NULL;
        free(basura);
        return;
    }
    lista_doble_eliminar_inicio(lista);
    return;
}

/*Lista Circular Simplemente Encadenada*/

Nodo_S* lista_simple_circ_insertar_inicio(Lista_D* lista, dato_t dato) {
    if(!lista_isempty(lista)) {
        Nodo_S* ultimo = *lista;
        while(ultimo->sig!=*lista) ultimo=ultimo->sig;
        Nodo_S* nuevo = nodo_simple_crear(dato, *lista);
        if(!nuevo) return NULL;
        ultimo->sig=nuevo;
        *lista=nuevo;
        return nuevo;
    }
    Nodo_S* nuevo = (Nodo_S*)malloc(sizeof(Nodo_S));
    if(!nuevo) return NULL;
    


}

Nodo_S* lista_simple_circ_insertar_fin(Lista_D* lista, dato_t dato) {
    Nodo_S* ultimo = *lista;
    while(ultimo->sig!=*lista) ultimo=ultimo->sig;
    Nodo_S* nuevo = nodo_simple_crear(dato, *lista);
    if(!nuevo) return NULL;
    ultimo->sig=nuevo;
    return nuevo;
}

void lista_simple_circ_eliminar_inicio(Lista_D* lista) {

}

void lista_simple_circ_eliminar_final(Lista_D* lista) {

}

/*Lista Circular Doblemente Encadenada*/

int main(void) {
    Nodo_S* lista = NULL;

}