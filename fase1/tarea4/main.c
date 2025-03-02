#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>
#define EDLIB_MAIN
#include "edlib.h"
#include "dstring.h"

typedef char dato_t;

typedef struct {
    dato_t* base;
    size_t tamano;
    size_t capacidad;
} Pila_S;

static inline Pila_S pila_estatica_init(dato_t* memoria, size_t capacidad) {
    return (Pila_S){.base=memoria, .tamano=0, .capacidad=capacidad};
}

static inline int pila_estatica_insertar(Pila_S* pila, dato_t dato) {
    if(pila->tamano < pila->capacidad) {
        pila->base[pila->tamano]=dato;
        ++(pila->tamano);
        return 1;
    }
    return 0;
}

static inline dato_t pila_estatica_pop(Pila_S* pila) {
    if(pila->tamano > 0)
        --(pila->tamano);
    return pila->base[pila->tamano];
}

static inline dato_t pila_estatica_get(const Pila_S* pila) {
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

static inline Pila_D* pila_dinamica_crear(void) {
    Pila_D* pila = (Pila_D*)malloc(sizeof(Pila_D));
    if(!pila) return NULL;
    pila->tope=NULL;
    pila->tamano=0;
    return pila;
}

static inline Nodo_S* pila_dinamica_insertar(Pila_D* pila, dato_t dato) {
    Nodo_S* nuevo = (Nodo_S*)malloc(sizeof(Nodo_S));
    if(!nuevo) return NULL;
    nuevo->dato=dato;
    nuevo->sig=pila->tope;
    pila->tope = nuevo;
    ++(pila->tamano);
    return nuevo;
}

static inline dato_t pila_dinamica_pop(Pila_D* pila) {
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

static inline dato_t pila_dinamica_get(const Pila_D* pila) {
    return pila->tope->dato;
}

static inline void pila_dinamica_destruir(Pila_D* pila) {
    while(pila->tope!=NULL)
        pila_dinamica_pop(pila);
    free(pila);
    return;
}


typedef enum {
    OPERANDO,
    OP_GENERICO,
    OP_IGUAL,
    OP_PAREN,
    OP_SUM_RES,
    OP_MULT_DIV,
    OP_EXP,
} op_t;

op_t asociar_operacion(char c) {
    if(c=='+' || c=='-') return OP_SUM_RES;
    if(c=='*' || c=='/') return OP_MULT_DIV;
    if(c=='^')           return OP_EXP;
    if(c=='(' || c==')') return OP_PAREN;
    if(c=='=')           return OP_IGUAL;
    return OPERANDO;
}

void infijo_a_posfijo_estatico(Pila_S* pila) {
    char entrada[pila->capacidad];
    char salida[pila->capacidad];
    static const char * msg_error =
    "La expresion debe ser de menor longitud\n"
    "que la capacidad asignada para la pila";
    for(;;) {
        clear();
        print("Continuar(1) : Salir(2)");
        if(validar_int_en_rango(1,2)==2) break;
        println("Introduzca una expresion infija:");
        edlib_set_msj_error(msg_error);
        leer_string(entrada, pila->capacidad);
        op_t op_actual, op_previo=OP_GENERICO;
        const char* e = entrada;
        char* s = salida;
        while(*e!='\0') {
            op_actual=asociar_operacion(*e);
            if(op_actual==OPERANDO) {
                if(!isspace(*e)) {*s = *e; ++s;}
            }
            else if(op_actual!=OP_PAREN) {
                //Detectar opradores seguidos
                if(op_previo!=OPERANDO) break;
                while(pila->tamano!=0 && asociar_operacion(pila_estatica_get(pila)) >= op_actual) {
                    *s = pila_estatica_pop(pila); ++s;                 
                }
                pila_estatica_insertar(pila, *e);
            }
            else if(*e=='(')
                pila_estatica_insertar(pila, *e);
            else {
                while(pila->tamano!=0 && pila_estatica_get(pila)!='(') {
                    *s = pila_estatica_pop(pila); ++s;
                }
                //Detectar parentesis invalidos
                if(pila->tamano==0) break;
                pila_estatica_pop(pila);
            }
            op_previo=op_actual;
            ++e;
        }
        while(pila->tamano!=0) {*s = pila_estatica_pop(pila); ++s;}
        //Mostrar mensaje de error si la cadena no es valida
        if(*e!='\0' || entrada[0]=='\0' ||
            (op_previo!=OPERANDO && op_previo!=OP_PAREN)) {
            println("Introduzca una expresion valida!");
            flush();
            continue;
        }
        *s='\0';
        print("Expresion Posfija: ", salida);
        flush();
    }
    return;
}

void infijo_a_posfijo_dinamico(Pila_D* pila) {
    Dstring* entrada = dstring_crear(NULL, 64);
    Dstring* salida = dstring_crear(NULL, 64);
    for(;;) {
        clear();
        print("Continuar(1) : Salir(2)");
        if(validar_int_en_rango(1,2)==2) break;
        println("Introduzca una expresion infija:");
        edlib_prompt; dstring_fset(entrada, stdin, '\n');
        dstring_set(salida, "");
        op_t op_actual, op_previo=OP_GENERICO;
        const char* e = dstring_a_ptr(entrada);
        while(*e!='\0') {
            op_actual=asociar_operacion(*e);
            if(op_actual==OPERANDO) {
                if(!isspace(*e)) dstring_append_char(salida,*e);
            }
            else if(op_actual!=OP_PAREN) {
                //Detectar operadores seguidos
                if(op_previo!=OPERANDO) break;
                while(pila->tamano!=0 && asociar_operacion(pila_dinamica_get(pila)) >= op_actual) {
                    dstring_append_char(salida, pila_dinamica_pop(pila));              
                }
                pila_dinamica_insertar(pila, *e);
            }
            else if(*e=='(')
                pila_dinamica_insertar(pila,*e);
            else {
                while(pila->tamano!=0 && pila_dinamica_get(pila)!='(') {
                    dstring_append_char(salida, pila_dinamica_pop(pila));
                }
                //Detectar parentesis invalidos
                if(pila->tamano==0) break;
                pila_dinamica_pop(pila);
            }
            op_previo=op_actual;
            ++e;
        }
        while(pila->tamano!=0)
            dstring_append_char(salida, pila_dinamica_pop(pila));
        if(*e!='\0' || dstring_isempty(entrada) ||
            (op_previo!=OPERANDO && op_previo!=OP_PAREN)) {
            println("Introduzca una expresion valida!");
            flush();
            continue;
        }
        print("Expresion Posfija: ", dstring_a_ptr(salida));
        flush();
    }
    dstring_destruir(entrada);
    dstring_destruir(salida);
    return;
}

int main(void) {
    static const char* titulo =
    "TRANSFORMACION DE EXPRESIONES INFIJAS A POSFIJAS";
    static const char* menu_principal =
    "1) Inicializar pila estatica\n"
    "2) Inicializar pila dinamica\n"
    "3) Salir";
    for(;;) {
        clear();
        println(titulo, menu_principal);
        switch(validar_int_en_rango(1,3)) {
        case 1: {
            print("Introduzca la capacidad de la pila"); 
            size_t capacidad = validar_uint_en_rango(1 ,1<<16);
            char arr[capacidad];
            Pila_S pila = pila_estatica_init(arr, capacidad);
            infijo_a_posfijo_estatico(&pila);
            break;
        }
        case 2:
            Pila_D* pila = pila_dinamica_crear();
            infijo_a_posfijo_dinamico(pila);
            pila_dinamica_destruir(pila);
            break;
        case 3:
            exit(EXIT_SUCCESS);
        }
    }
}