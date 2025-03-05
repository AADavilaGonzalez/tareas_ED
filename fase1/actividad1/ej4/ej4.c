#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#define EDLIB_MAIN
#include "edlib.h"
#include "lista_s.h"

/*Funcion para generar la lista encadenada a partir de los
datos introducidos por el usuario*/
Lista_S* entrada_de_datos(void) {
    println("Sistema de antivirus de ACME S.R.L",
            "Introduzca la lista de contactos registrados");
    Lista_S* contactos = lista_s_crear();
    Contacto buffer;
    do{ endl;
        print("Nombre"); leer_string(buffer.nombre, MAX_STR);
        print("Numero"); buffer.numero = validar_uint_en_rango(1000000000, 9999999999);
        lista_s_insertar_fin(contactos, buffer);
        print("Continuar? 1:Si | 2:No");
    } while(validar_int_en_rango(1,2)!=2);
    println("***Fin de la captura de Contactos***"); endl;
    return contactos;
}

/*Funcion secilla para invertir una cadena
utilizando punteros*/
void invertir_cadena(char* cadena) {
    size_t longitud = strlen(cadena);
    if(longitud==0 || longitud==1) return;
    char tmp;
    char* ultimo = cadena+longitud-1;
    while(cadena < ultimo) {
        tmp = *cadena;
        *cadena=*ultimo;
        *ultimo=tmp;
        ++cadena; --ultimo;
    }
    return;
}

/*Implenta el algoritmo especificado en la redaccion
del problema*/
Lista_S* antivirus(Lista_S* lista, unsigned int dia) {
    Lista_S* correciones = lista_s_crear();
    Nodo_S* ptr=lista->cabeza;
    //Recorremos todos los emelentos de la lista con un indice
    for(size_t i=1; i<= lista->tamano; ptr=ptr->sig, ++i) {
        if(i%dia==0) {
            invertir_cadena(ptr->dato.nombre);
            lista_s_insertar_fin(correciones, ptr->dato);
        }
    }
    return correciones;
}

void print_contactos(Lista_S* lista) {
    Nodo_S* ptr=lista->cabeza;
    while(ptr!=NULL) {
        printf("Nombre: %s\n", ptr->dato.nombre);
        printf("Numero: %lu\n\n", ptr->dato.numero);
        ptr=ptr->sig;
    }
    return;
}

int main(void) {
    unsigned int dia;
    Lista_S* contactos = entrada_de_datos();
    print("Que dia del mes ocurrio el incidente?");
    dia=validar_uint_en_rango(1,30);
    Lista_S* correciones = antivirus(contactos, dia);
    println("Lista de contactos corregida:"); endl;
    print_contactos(contactos);
    println("Resumen de contactos corregidos:"); endl;
    print_contactos(correciones);
    lista_s_destruir(contactos);
    lista_s_destruir(correciones);
    println("Saliendo del programa exitosamente");
    flush();
    return 0;
}