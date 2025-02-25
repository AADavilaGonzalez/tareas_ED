#include <stdlib.h>
#include <stdio.h>

#define dato_t int

typedef struct {
    dato_t* base;
    size_t tamano;
    size_t capacidad;
} Pila_S;

Pila_S pila_estatica_init(dato_t* memoria, size_t capacidad) {
    return (Pila_S){.base=memoria, .tamano=0, .capacidad=capacidad};
}

int pila_estatica_insertar(Pila_S* pila, dato_t dato) {
    if(pila->tamano < pila->capacidad) {
        pila->base[pila->tamano]=dato;
        ++(pila->tamano);
        return 1;
    }
    return 0;
}

void pila_estatica_eliminar(Pila_S* pila) {
    if(pila->tamano > 0)
        --(pila->tamano);
    return;
}

dato_t pila_estatica_get(Pila_S* pila) {
    if(pila->tamano!=0)
        return pila->base[pila->tamano-1];
}

typedef struct nodo_s {
    struct nodo_s* sig;
    dato_t dato;
} Nodo_S;

typedef struct {
    Nodo_S* tope;
    size_t tamano;
} Pila_D;

Pila_D* pila_dinamica_init() {
    Pila_D* pila = (Pila_D*)malloc(sizeof(Pila_D));
    if(!pila) return NULL;
    pila->tope=NULL;
    pila->tamano=0;
    return pila;
}

Nodo_S* pila_dinamica_insertar(Pila_D* pila, dato_t dato) {
    Nodo_S* nuevo = (Nodo_S*)malloc(sizeof(Nodo_S));
    if(!nuevo) return NULL;
    nuevo->dato=dato;
    nuevo->sig=pila->tope;
    pila->tope = nuevo;
    return nuevo;
}

void pila_dinamica_pop(Pila_D* pila) {

}

#define EDLIB_MAIN
#include "edlib.h"

int main(void) {
    static const char* titulo =
    "TRANSFORMACION DE EXPRESIONES INFIJAS A POSFIJAS";
    static const char* menu_principal =
    "1) Inicializar pila estatica\n"
    "2) Inicializar pila dinamica\n"
    "3) Salir";
    for(;;) {
        println(titulo, menu_principal);
        switch(validar_int_en_rango(1,3)) {
        case 1: {
            print("Introduzca la capacidad de la pila"); 
            size_t capacidad = validar_uint_max(1<<16);
            int pila[capacidad];

            break;
        }
        case 2:
            print("2");
            break;
        case 3:
            exit(EXIT_SUCCESS);
        }
    }
}