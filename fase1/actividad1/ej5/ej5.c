#define EDLIB_MAIN
#include "edlib.h"
#include "pila_d.h"

typedef enum {
    ATRAS=-1,
    ADELANTE=1,
} Direccion;

#define avanzar(ptr, dir) (ptr+=dir)
#define voltear(dir) (dir*=-1)

/*Algoritmo para desencriptar el mensaje alrevezzado por parentesis...
orig: ubicacion del mensaje original
dest: donde se guardara el mensaje desencriptado*/
void desencriptar(const char* orig, char* dest) {
    /*Pila para almacenar las direcciones a las que se va a regresar
    despues de procesar los contenidos de un parentesis entero*/
    Pila_D* pila_salto = pila_d_crear();
    size_t contador_parentesis;
    Direccion dir = ADELANTE;
    while(*orig!='\0') {
        /*Si estamos en un parentesis abierto y vamos hacia adelante
        recorremos hasta hasta el parentesis cerrado correspondiente
        y guardamos la posicion en la que termina. Volteamos la 
        direccion de lectura para leer en direccion contrarea. Si
        llegamos a un parentesis abierto en reversa significa que
        hemos recorrido un parentesis entero por lo tanto saltamos
        a la direccion alamacenada mas reciente*/
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
        /*Se hace lo mismo con el parentesis cerrado pero volteando
        las direcciones que le indican al algorimo cuando hacer
        cada cosa.*/
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
        /*Si la entrada no es un parentesis se anade a la salida*/
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