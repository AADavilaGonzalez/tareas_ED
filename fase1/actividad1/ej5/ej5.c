#include "pila_d.h"

typedef enum {
    ATRAS=-1,
    ADELANTE=1,
} Direccion;

void desencriptar(char* dest, const char* orig) {
    Pila_D* pos = pila_d_crear();
    Direccion dir = ADELANTE;
    while(*orig!='\0') {
        if(*orig=='(') {

        }
        else if(*orig==')') {

        }
        else {
            *dest=*orig;
            ++dest;
            orig+=dir;
        }
    }
    pila_d_destruir(pos);
}