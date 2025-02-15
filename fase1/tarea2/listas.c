#include <stdlib.h>
#include <stdio.h>

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

/*Lista Doblemente Encadenada*/
typedef struct nodo_d {
    struct nodo_d* sig;
    dato_t dato;
    struct nodo_d* prev;
} Nodo_D;

typedef Nodo_D* Lista_D;

/*Acepta lista vacia: si*/
Nodo_D* lista_doble_insertar_inicio(Lista_D* lista, dato_t dato) {
    Nodo_D* nuevo = (Nodo_D*)malloc(sizeof(Nodo_D));
    if(nuevo!=NULL){
        nuevo->dato=dato;
        nuevo->prev=NULL;
        nuevo->sig=*lista;
        if(*lista!=NULL) {
            (*lista)->prev=nuevo;
        }
        *lista = nuevo;
    }
    return nuevo;
}

/*Acepta lista vacia: si*/
Nodo_D* lista_doble_insertar_fin(Lista_D* lista, dato_t dato) {
    if(lista_isempty(lista)) 
        return lista_doble_insertar_inicio(lista, dato);
    Nodo_D* ultimo = *lista;
    while(ultimo->sig!=NULL) ultimo=ultimo->sig;
    Nodo_D* nuevo =  (Nodo_D*)malloc(sizeof(Nodo_D));
    if(nuevo!=NULL) {
        nuevo->dato=dato;
        nuevo->sig=NULL;
        nuevo->prev=ultimo;
        ultimo->sig=nuevo;
    }
    return nuevo;
}

/*Acepta list vacia: no, checar si *lista!=NULL*/
void lista_doble_eliminar_inicio(Lista_D* lista) {
    Nodo_D* primero=*lista;
    *lista=(*lista)->sig;
    if(*lista!=NULL) {
        (*lista)->prev = NULL;
    }
    free(primero);
    return;
}

/*Acepta lista vacia: no, checar si *lista!=NULL*/
void lista_doble_eliminar_fin(Lista_D* lista) {
    if((*lista)->sig!=NULL) {
        Nodo_D* ultimo=(*lista)->sig;
        while(ultimo->sig!=NULL) ultimo=ultimo->sig;
        ultimo->prev->sig=NULL;
        free(ultimo);
    } else {
        lista_doble_eliminar_inicio(lista);
    }
    return;
}

/*Lista Circular Simplemente Encadenada*/

/*Acepta lista vacia: si*/
Nodo_S* lista_simple_circ_insertar_inicio(Lista_S* lista, dato_t dato) {
    Nodo_S* nuevo = (Nodo_S*)malloc(sizeof(Nodo_S));
    if(nuevo!=NULL) {
        nuevo->dato=dato;
        if(!lista_isempty(lista)) {
            Nodo_S* ultimo = *lista;
            while(ultimo->sig!=*lista)
                ultimo=ultimo->sig;
            nuevo->sig=*lista;
            ultimo->sig=nuevo;
        } else {
            nuevo->sig=nuevo;
        }
        *lista=nuevo;
    }
    return nuevo;
}

/*Acepta lista vacia: si*/
Nodo_S* lista_simple_circ_insertar_fin(Lista_S* lista, dato_t dato) {
    Nodo_S* nuevo = (Nodo_S*)malloc(sizeof(Nodo_S));
    if(nuevo!=NULL) {
        nuevo->dato=dato;
        if(!lista_isempty(lista)) {
            Nodo_S* ultimo = *lista;
            while(ultimo->sig!=*lista)
                ultimo=ultimo->sig;
            nuevo->sig=*lista;
            ultimo->sig=nuevo;
        } else {
            nuevo->sig=nuevo;
            *lista=nuevo;
        }
    }
    return nuevo;
}

/*Acepta lista vacia: no, checar si *lista!=NULL*/
void lista_simple_circ_eliminar_inicio(Lista_S* lista) {
    if((*lista)->sig!=*lista) {
        Nodo_S* ultimo=*lista;
        while(ultimo->sig!=*lista) ultimo=ultimo->sig;
        ultimo->sig=(*lista)->sig;
        free(*lista);
        *lista=ultimo->sig;
    } else {
        free(*lista);
        *lista=NULL;
    }
    return;
}

/*Acepta lista vacia: no, checar si *lista!=NULL*/
void lista_simple_circ_eliminar_fin(Lista_S* lista) {
    if((*lista)->sig!=*lista) {
        Nodo_S* ultimo=(*lista)->sig, *penultimo=*lista;
        while(ultimo->sig!=*lista) {
            penultimo=ultimo;
            ultimo=ultimo->sig;
        }
        penultimo->sig=*lista;
        free(ultimo);
    } else {
        free(*lista);
        *lista=NULL;
    }
    return;
}

/*Lista Circular Doblemente Encadenada*/

/*Acepta lista vacia: si*/
Nodo_D* lista_doble_circ_insertar_inicio(Lista_D* lista, dato_t dato) {
    Nodo_D* nuevo = (Nodo_D*)malloc(sizeof(Nodo_D));
    if(nuevo!=NULL) {
        nuevo->dato=dato;
        if(!lista_isempty(lista)) {
            nuevo->sig=*lista;
            nuevo->prev=(*lista)->prev;
            (*lista)->prev->sig=nuevo;
            (*lista)->prev=nuevo;
        } else {
            nuevo->sig=nuevo;
            nuevo->prev=nuevo;
        }
        *lista=nuevo;
    }
    return nuevo;
}

/*Acepta lista vacia: si*/
Nodo_D* lista_doble_circ_insertar_fin(Lista_D* lista, dato_t dato) {
    Nodo_D* nuevo = (Nodo_D*)malloc(sizeof(Nodo_D));
    if(nuevo!=NULL) {
        nuevo->dato=dato;
        if(!lista_isempty(lista)) {
            nuevo->sig=*lista;
            nuevo->prev=(*lista)->prev;
            (*lista)->prev->sig=nuevo;
            (*lista)->prev=nuevo;
        } else {
            nuevo->sig=nuevo;
            nuevo->prev=nuevo;
            *lista=nuevo;
        }
    }
    return nuevo;
}

/*Acepta lista vacia: no, checar si *lista!=NULL*/
void lista_doble_circ_eliminar_inicio(Lista_D* lista) {
    if((*lista)->sig!=*lista) {
        Nodo_D* siguiente = (*lista)->sig;
        (*lista)->prev->sig=siguiente;
        siguiente->prev=(*lista)->prev;
        free(*lista);
        *lista=siguiente;
    } else {
        free(*lista);
        *lista=NULL;
    }
    return;
}

/*Acepta lista vacia: no, checar si *lista!=NULL*/
void lista_doble_circ_eliminar_fin(Lista_D* lista) {
    if((*lista)->sig!=*lista) {
        Nodo_D* ultimo = (*lista)->prev;
        (*lista)->prev=ultimo->prev;
        ultimo->prev->sig=(*lista);
        free(ultimo);
    } else {
        free(*lista);
        *lista=NULL;
    }
    return;
}

/*Acepta lista vacia: si*/
void print_lista(void* lista, void(*print_dato)(dato_t)) {
    Nodo_S* const inicio= *((Lista_S*)lista);
    if(inicio!=NULL) {
        fputc('[', stdout);
        Nodo_S* nodo = inicio;
        print_dato(nodo->dato);
        nodo=nodo->sig;
        while(nodo!=NULL) {
            fputs(", ", stdout);
            if(nodo==inicio) {
                fputs("...", stdout);
                break;
            }
            print_dato(nodo->dato);
            nodo=nodo->sig; 
        }
        fputc(']', stdout);
    } else {
        fputs("[]", stdout);
    }
    return;
}

/*Acepta lisa vacia: si*/
void lista_destruir(void* lista) {
    Nodo_S* const inicio = *((Lista_S*)lista);
    Nodo_S *ptr=inicio, *basura;
    while(ptr!=NULL && ptr!=inicio) {
        basura=ptr;
        ptr=ptr->sig;
        free(basura);
    }
}

void print_dato(dato_t dato) {
    printf("%d", dato);
    return;
}

#define EDLIB_MAIN
#include "edlib.h"

void submenu_lista_simple(void);
void submenu_lista_simple_circ(void);
void submenu_lista_doble(void);
void submenu_lista_doble_circ(void);

int main(void) {
    int opc;
    static const char menu_prinipal[] = 
    "Pueba de listas encadenadas:\n"
    "1) Lista Simple\n"
    "2) Lista Simple Circular\n"
    "3) Lista Doble\n"
    "4) Lista Doble Circular\n"
    "5) Salir\n\n";
    do {
        clear();
        fputs(menu_prinipal, stdout);
        opc=validar_int_en_rango(1,5);
        switch(opc) {
        case 1:
            submenu_lista_simple();
            break;
        case 2:
            submenu_lista_simple_circ();
            break;
        case 3:
            submenu_lista_doble();
            break;
        case 4:
            submenu_lista_doble_circ();
            break;
        }
    } while(opc!=5);
    clear();
    return 0;
}

void submenu_lista_simple(void) {
    Lista_S lista = NULL;
    int opc, i;
    static const char texto_submenu_ls[]=
    "LISTA SIMPLEMENTE ENCADENADA\n"
    "1) insertar inicio\n"
    "2) insertar fin\n"
    "3) eliminar inicio\n"
    "4) eliminar fin\n"
    "5) salir\n\n";
    do {
        clear();
        print_lista(&lista, print_dato); putchar('\n');
        fputs(texto_submenu_ls, stdout);
        fputs("Opcion", stdout); opc=validar_int_en_rango(1,5);
        switch(opc) {
        case 1:
            fputs("Valor Entero", stdout); i=validar_int();
            lista_simple_insertar_inicio(&lista, i);
            break;
        case 2:
            fputs("Valor Entero", stdout); i=validar_int();
            lista_simple_insertar_fin(&lista, i);
            break;
        case 3:
            if(lista!=NULL)
                lista_simple_eliminar_inicio(&lista);
            break;
        case 4:
            if(lista!=NULL)
                lista_simple_eliminar_fin(&lista);
            break;
        }
    } while(opc!=5);
    lista_destruir(&lista);
}

void submenu_lista_simple_circ(void) {
    Lista_S lista = NULL;
    int opc, i;
    static const char texto_submenu_lsc[]=
    "LISTA CIRCULAR SIMPLEMENTE ENCADENADA\n"
    "1) insertar inicio\n"
    "2) insertar fin\n"
    "3) eliminar inicio\n"
    "4) eliminar fin\n"
    "5) desplazar hacia delante\n"
    "6) salir\n\n";
    do {
        clear();
        print_lista(&lista, print_dato); putchar('\n');
        fputs(texto_submenu_lsc, stdout);
        fputs("Opcion", stdout);opc=validar_int_en_rango(1,6);
        switch(opc) {
        case 1:
            fputs("Valor Entero", stdout); i=validar_int();
            lista_simple_circ_insertar_inicio(&lista, i);
            break;
        case 2:
            fputs("Valor Entero", stdout); i=validar_int();
            lista_simple_circ_insertar_fin(&lista, i);
            break;
        case 3:
            if(lista!=NULL)
                lista_simple_circ_eliminar_inicio(&lista);
            break;
        case 4:
            if(lista!=NULL)
                lista_simple_circ_eliminar_fin(&lista);
            break;
        case 5:
            if(lista!=NULL) {
                lista=lista->sig;
            }
        }
    } while(opc!=6);
    lista_destruir(&lista);
}

void submenu_lista_doble(void) {
    Lista_D lista = NULL;
    int opc, i;
    static const char texto_submenu_ld[]=
    "LISTA DOBLEMENTE ENCADENADA\n"
    "1) insertar inicio\n"
    "2) insertar fin\n"
    "3) eliminar inicio\n"
    "4) eliminar fin\n"
    "5) salir\n\n";
    do {
        clear();
        print_lista(&lista, print_dato); putchar('\n');
        fputs(texto_submenu_ld, stdout);
        fputs("Opcion", stdout);opc=validar_int_en_rango(1,5);
        switch(opc) {
        case 1:
            fputs("Valor Entero", stdout); i=validar_int();
            lista_doble_insertar_inicio(&lista, i);
            break;
        case 2:
            fputs("Valor Entero", stdout); i=validar_int();
            lista_doble_insertar_fin(&lista, i);
            break;
        case 3:
            if(lista!=NULL)
                lista_doble_eliminar_inicio(&lista);
            break;
        case 4:
            if(lista!=NULL)
                lista_doble_eliminar_fin(&lista);
            break;
        }
    } while(opc!=5);
    lista_destruir(&lista);
}

void submenu_lista_doble_circ(void) {
    Lista_D lista = NULL;
    int opc, i;
    static const char texto_submenu_ldc[]=
    "LISTA CIRCULAR DOBLEMENTE ENCADENADA\n"
    "1) insertar inicio\n"
    "2) insertar fin\n"
    "3) eliminar inicio\n"
    "4) eliminar fin\n"
    "5) desplazar hacia delante\n"
    "6) desplazar hacia atras\n"
    "7) salir\n\n";
    do {
        clear();
        print_lista(&lista, print_dato); putchar('\n');
        fputs(texto_submenu_ldc, stdout);
        fputs("Opcion", stdout);opc=validar_int_en_rango(1,7);
        switch(opc) {
        case 1:
            fputs("Valor Entero", stdout); i=validar_int();
            lista_doble_circ_insertar_inicio(&lista, i);
            break;
        case 2:
            fputs("Valor Entero", stdout); i=validar_int();
            lista_doble_circ_insertar_fin(&lista, i);
            break;
        case 3:
            if(lista!=NULL)
                lista_doble_circ_eliminar_inicio(&lista);
            break;
        case 4:
            if(lista!=NULL)
                lista_doble_circ_eliminar_fin(&lista);
            break;
        case 5:
            if(lista!=NULL) {
                lista=lista->sig;
            }
            break;
        case 6:
            if(lista!=NULL) {
                lista=lista->prev;
            }
            break;
        }
    } while(opc!=7);
    lista_destruir(&lista);
}