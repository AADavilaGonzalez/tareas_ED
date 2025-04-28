#ifndef LISTA_D_H
#define LISTA_D_H
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

#if defined(DATO_LISTA) && defined(STRUCT_LISTA)
#error "Defina exclusivamente DATO_LISTA o STRUCT_LISTA no ambos"
#endif

#ifdef DATO_LISTA
#define _elem DATO_LISTA
#endif

#ifdef STRUCT_LISTA
#define _elem STRUCT_LISTA
#endif

#ifndef _elem
#define _elem int
#endif

#ifndef STRUCT_LISTA
static bool _lista_d_cmp_elem_default(const _elem* a, const _elem* b) {return *a==*b;}
#define _cmp_elem_default _lista_d_cmp_elem_default
#else
#define _cmp_elem_default NULL
#endif

struct _nodo_lista {
    struct _nodo_lista* sig;
    struct _nodo_lista* prev;
    _elem elem;
};
#define _Nodo struct _nodo_lista 

typedef struct _lista_d{
    _Nodo* ini;
    _Nodo* fin;
    size_t tamano;
    bool (*cmp_elem)(const _elem*, const _elem*);
} Lista_D;

static Lista_D* lista_d_crear() {
    Lista_D* lista = (Lista_D*)malloc(sizeof(Lista_D));
    if(!lista) return NULL;
    lista->ini=NULL;
    lista->fin=NULL;
    lista->tamano=0;
    lista->cmp_elem=_cmp_elem_default;
    return lista;
}

static inline void lista_d_set_cmp_elem(Lista_D* lista,
    bool (*cmp_elem)(const _elem*, const _elem*)) {lista->cmp_elem=cmp_elem;}

static inline void lista_d_unset_cmp_elem(Lista_D* lista) {lista->cmp_elem=_cmp_elem_default;}

static inline bool lista_d_isempty(const Lista_D* lista) {
    return  lista->ini==NULL &&
            lista->fin==NULL &&
            lista->tamano==0;
}

static inline _elem lista_d_get_inicio(const Lista_D* lista) {
    return lista->ini->elem;
}

static inline _elem lista_d_get_fin(const Lista_D* lista) {
    return lista->fin->elem;
}

static bool lista_d_insertar_inicio(Lista_D* lista, _elem elem) { 
    _Nodo* nodo = (_Nodo*)malloc(sizeof(_Nodo));
    if(!nodo) return false;
    nodo->elem=elem;
    nodo->prev=NULL;
    if(lista_d_isempty(lista)) {
        nodo->sig=NULL;
        lista->fin=nodo;
    } else {
        lista->ini->prev=nodo;
        nodo->sig=lista->ini;
    }
    lista->ini=nodo;
    ++(lista->tamano);
    return true;
}

static bool lista_d_insertar_fin(Lista_D* lista, _elem elem) {
    _Nodo* nodo = (_Nodo*)malloc(sizeof(_Nodo));
    if(!nodo) return false;
    nodo->elem=elem;
    nodo->sig=NULL;
    if(lista_d_isempty(lista)) {
        nodo->prev=NULL;
        lista->ini=nodo;
    } else {
        lista->fin->sig=nodo;
        nodo->prev=lista->fin;
    }
    lista->fin=nodo;
    ++(lista->tamano);
    return true;
}

static void lista_d_eliminar_inicio(Lista_D* lista) {
    _Nodo* tmp = lista->ini;
    if(lista->ini==lista->fin) {
        lista->ini=NULL;
        lista->fin=NULL;
    } else {
        lista->ini=lista->ini->sig;
        lista->ini->prev=NULL;
    }
    free(tmp);
    --(lista->tamano);
}

static void lista_d_eliminar_fin(Lista_D* lista) {
    _Nodo* tmp = lista->fin;
    if(lista->ini==lista->fin) {
        lista->ini=NULL;
        lista->fin=NULL;
    } else {
        lista->fin=lista->fin->prev;
        lista->fin->sig=NULL;
    }
    free(tmp);
    --(lista->tamano);
}

static inline _elem lista_d_pop_inicio(Lista_D* lista) {
    _elem elem = lista_d_get_inicio(lista);
    lista_d_eliminar_inicio(lista);
    return elem;
}

static inline _elem lista_d_pop_fin(Lista_D* lista) {
    _elem elem = lista_d_get_fin(lista);
    lista_d_eliminar_fin(lista);
    return elem;
}

static bool lista_d_contiene_elem(Lista_D* lista, _elem ref) {
    _Nodo* nodo = lista->ini;
    while(nodo!=NULL) {
        if(lista->cmp_elem((const _elem*)&ref, (const _elem*)&nodo->elem))
            return true;
        nodo = nodo->sig;
    }
    return false;
}

static void lista_d_print(Lista_D* lista, void (*print_elem)(const _elem*)) {
    _Nodo* ptr=lista->ini;
    putchar('[');
    if(ptr!=NULL) {
        print_elem((const _elem*)&ptr->elem);
        ptr=ptr->sig;
    }
    while(ptr!=NULL) {
        fputs(", ", stdout);
        print_elem((const _elem*)&ptr->elem);
        ptr=ptr->sig;
    }
    putchar(']');
}

static void lista_d_destruir(Lista_D* lista) {
    _Nodo* nodo = lista->ini;
    _Nodo* tmp = NULL;
    while(nodo!=NULL) {
        tmp=nodo;
        nodo=nodo->sig;
        free(tmp);
    }
    free(lista);
}

#undef _elem
#undef _Nodo
#endif