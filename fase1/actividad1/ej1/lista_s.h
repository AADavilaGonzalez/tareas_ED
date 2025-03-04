#ifndef _LISTA_S_H
#define _LISTA_S_H
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

#define dato_t double

typedef struct nodo_s {
    struct nodo_s* sig;
    dato_t dato;
} Nodo_S;

typedef struct lista_s {
    Nodo_S* cabeza;
    size_t tamano;
} Lista_S;

static Lista_S* lista_s_crear(void) {
    Lista_S* lista = (Lista_S*)malloc(sizeof(Lista_S));
    if(!lista) return NULL;
    lista->cabeza=NULL;
    lista->tamano=0;
    return lista;
}

static bool lista_s_isempty(Lista_S* lista) {
    return lista->cabeza==NULL && lista->tamano==0;
}

/*Acepta lista vacia: si.*/
static Nodo_S* lista_s_insertar_inicio(Lista_S* lista, dato_t dato) {
    Nodo_S* nuevo = (Nodo_S*)malloc(sizeof(Nodo_S));
    if(!nuevo) return NULL;
    nuevo->dato=dato;
    nuevo->sig=lista->cabeza;
    lista->cabeza = nuevo;
    ++(lista->tamano);
    return nuevo;
}

/*Acepta lista vacia: si*/
static Nodo_S* lista_s_insertar_fin(Lista_S* lista, dato_t dato) {
    if(lista_s_isempty(lista)) 
        return lista_s_insertar_inicio(lista, dato);
    Nodo_S* ultimo=lista->cabeza;
    while(ultimo->sig!=NULL) ultimo=ultimo->sig;
    Nodo_S* nuevo = (Nodo_S*)malloc(sizeof(Nodo_S));
    if(!nuevo) return NULL;
    nuevo->dato=dato;
    nuevo->sig=NULL;
    ultimo->sig=nuevo;
    ++(lista->tamano);
    return nuevo;
}

void lista_s_destruir(Lista_S* lista) {
    Nodo_S *ptr = lista->cabeza, *basura;
    while(ptr!=NULL) {
        basura=ptr;
        ptr=ptr->sig;
        free(basura);
    }
    free(lista);
    return;
}
#endif