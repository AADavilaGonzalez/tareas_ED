#ifndef _PILA_D_H
#define _PILA_D_H
#include<stdlib.h>

#define dato_t int

typedef struct nodo_s {
    struct nodo_s* sig;
    dato_t dato;
} Nodo_S;

typedef struct {
    Nodo_S* tope;
    size_t tamano;
} Pila_D;

static inline Pila_D* pila_d_crear(void) {
    Pila_D* pila = (Pila_D*)malloc(sizeof(Pila_D));
    if(!pila) return NULL;
    pila->tope=NULL;
    pila->tamano=0;
    return pila;
}

static inline Nodo_S* pila_d_insertar(Pila_D* pila, dato_t dato) {
    Nodo_S* nuevo = (Nodo_S*)malloc(sizeof(Nodo_S));
    if(!nuevo) return NULL;
    nuevo->dato=dato;
    nuevo->sig=pila->tope;
    pila->tope = nuevo;
    ++(pila->tamano);
    return nuevo;
}

static inline dato_t pila_d_pop(Pila_D* pila) {
    dato_t dato;
    if(pila->tope!=NULL) {
        Nodo_S* basura = pila->tope;
        dato = basura->dato;
        pila->tope = basura->sig;
        free(basura);
        --(pila->tamano);
    }
    return dato;
}

static inline dato_t pila_d_get(const Pila_D* pila) {
    return pila->tope->dato;
}

static inline void pila_d_destruir(Pila_D* pila) {
    while(pila->tope!=NULL)
        pila_dinamica_pop(pila);
    free(pila);
    return;
}

#endif