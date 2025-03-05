#define EDLIB_MAIN
#include "edlib.h"
#include "pila_d.h"

typedef enum {
    ATRAS=-1,
    ADELANTE=1,
} Direccion;

#define avanzar(ptr, dir) (ptr+=dir)
#define voltear(dir) (dir*=-1)

void desencriptar(const char* orig, char* dest) {
    Pila_D* pila_salto = pila_d_crear();
    size_t contador_parentesis;
    Direccion dir = ADELANTE;
    while(*orig!='\0') {
        if(*orig=='(') {
            if(dir==ADELANTE) {
                contador_parentesis=1;
                while(contador_parentesis!=0 && *orig!='\0') {
                    avanzar(orig, dir);
                    if(*orig=='(') ++contador_parentesis;
                    else if(*orig==')') --contador_parentesis;
                }
                pila_d_insertar(pila_salto, orig+dir);
                voltear(dir);
                avanzar(orig, dir);
            } else {
                voltear(dir);
                orig = pila_d_pop(pila_salto);
            }
        }
        else if(*orig==')') {
            if(dir==ATRAS) {
                contador_parentesis=1;
                while(contador_parentesis!=0 && *orig!='\0') {
                    avanzar(orig, dir);
                    if(*orig==')') ++contador_parentesis;
                    else if(*orig=='(') --contador_parentesis;
                }
                pila_d_insertar(pila_salto, orig+dir);
                voltear(dir);
                avanzar(orig, dir);
            } else {
                voltear(dir);
                orig = pila_d_pop(pila_salto);
            }
        }
        else {
            *dest=*orig;
            ++dest;
            avanzar(orig, dir);
        }
    }
    pila_d_destruir(pila_salto);
    return;
}

#define STR_MAX 64

int main(void) {
    char entrada[STR_MAX];
    char salida[STR_MAX];
    println("Desencriptacion de strings alrevezados con parentesis:");
    print("Entrada"); leer_string(entrada, STR_MAX);
    desencriptar(entrada, salida);
    print("Salida > "); println(salida);
    print("***FIN DEL PROGRAMA***");
    flush();
    return 0;
}