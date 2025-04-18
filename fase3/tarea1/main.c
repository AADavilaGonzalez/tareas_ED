#include <stdio.h>
#include <stdlib.h>

#define EDLIB_MAIN
#include "edlib.h"

typedef struct nodo {
    int dato;
    struct nodo *izq;
    struct nodo *der;
} Nodo;

void limpiar_pantalla();
Nodo* crear_nodo(int valor);
Nodo* insertar_elemento(Nodo* raiz, int valor);
Nodo* buscar_elemento(Nodo *raiz, int valor);
Nodo* eliminar_elemento(Nodo **raiz, int valor);
void imprimir_arbol(Nodo* raiz, int nivel);

int main(void) {
    int op1, val = 0, num, i, valor;
    Nodo *raiz = NULL, *elemento = NULL;

    while (1) {
        // Ciclo para validar el menu
        while (1) {
            printf("Seleccione una opcion.\n"
                "1.- Crear un arbol binario\n"
                "2.- Buscar un elemento del arbol\n"
                "3.- Insertar un elemento en el arbol\n"
                "4.- Eliminar un elemento del arbol\n"
                "5.- Imprimir el arbol\n"
                "6.- Salir\n");
            if (scanf("%d", &op1) != 1 || op1 < 1 || op1 > 6) {
                printf("Introduzca un número valido\n\n");
                while (getchar() != '\n');
                continue;
            }
            limpiar_pantalla();
            break;
        }
        switch (op1) {
            case 1:
                if (val == 0 || raiz == NULL) {
                    while (1) {
                        printf("Introduzca el numero de elementos a insertar: \n");
                        if (scanf("%d", &num) != 1 || num < 0) {
                            printf("Introdzuca un número valido\n");
                            while (getchar() != '\n');
                            continue;
                        }
                        break;
                    }
                    for (i = 0; i < num; i++) {
                        printf("Introduzca un entero\n");
                        if (scanf("%d", &valor) != 1) {
                            printf("Introdzuca un número valido\n");
                            while (getchar() != '\n');
                            continue;
                        }
                        raiz = insertar_elemento(raiz, valor);
                    }
                    printf("\nArbol: \n");
                    imprimir_arbol(raiz, 0);
                    printf("\n\n");
                    val = 1;
                    break;
                }
                if (val == 1 && raiz != NULL) printf("El arbol ya ha sido creado\n\n");
                break;
            case 2:
                if (val == 1 && raiz != NULL) {
                    while (1)
                    {
                        printf("Introduzca el elemento a buscar: (-1 para salir)\n");
                        valor = validar_int_min(-1);

                        if(valor == -1)
                            break;
                
                        elemento = buscar_elemento(raiz, valor);
                        if (elemento != NULL)
                        {
                            printf("Elemento encontrado: %d\n", elemento);
                            printf("\nArbol: \n");
                            imprimir_arbol(raiz, 0);
                            printf("\n\n");
                        }
                        else
                            printf("Elemento no encontrado\n");
                    }
                }
                if (val == 0) printf("El arbol no a sido creado\n\n");
                else if (raiz == NULL) printf("El arbol esta vacio\n\n");
                break;
                break;
            case 3:
                if (val == 1 && raiz != NULL) {
                    printf("Introduzca un entero\n");
                    if (scanf("%d", &valor) != 1) {
                        printf("Introduzca un número valido\n");
                        while (getchar() != '\n');
                        continue;
                    }
                    insertar_elemento(raiz, valor);
                    printf("Arbol: \n");
                    imprimir_arbol(raiz, 0);

                    printf("\n\n");
                    break;
                }
                if (val == 0) printf("El arbol no ha sido creado\n\n");
                if (raiz == NULL) printf("El arbol esta vacio\n\n");
                break;
            case 4:
                if (val == 1 && raiz != NULL) {
                    printf("Introduzca el numero entero a eliminar\n");
                    if (scanf("%d", &valor) != 1) {
                        printf("Introduzca un número valido\n");
                        while (getchar() != '\n');
                        continue;
                    }
                    eliminar_elemento(&raiz, valor);
                    printf("Arbol: \n");
                    imprimir_arbol(raiz, 0);

                    printf("\n\n");
                    break;
                }
                if (val == 0) printf("El arbol no ha sido creado\n\n");
                if (raiz == NULL) printf("El arbol esta vacio\n\n");
                break;
            case 5:
                if (val == 1 && raiz != NULL) {
                    imprimir_arbol(raiz, 0);
                    printf("\n\n");
                    break;
                }
                if (val == 0) printf("El arbol no ha sido creado\n\n");
                if (raiz == NULL) printf("El arbol esta vacio\n\n");
                break;
        }
        if (op1 == 6) {
            break;
        }
    }
    return 0;
}

void limpiar_pantalla() {
    #ifdef _WIN32
        system("cls");
    #else
        system("clear");
    #endif
}

Nodo *crear_nodo(int valor) {
    Nodo *nuevo = (Nodo *)malloc(sizeof(Nodo));
    if (nuevo == NULL) {
        printf("Error al asignar la memoria\n");
        exit(1);
    }
    nuevo->dato = valor;
    nuevo->izq = nuevo->der = NULL;
    return nuevo;
}

Nodo *insertar_elemento(Nodo *raiz, int valor) {
    // Si el arbol no tiene elementos
    if (raiz == NULL) return crear_nodo(valor);
    // Si el valor es menor que la raiz, se coloca en la izquierda
    if (valor < raiz->dato) raiz->izq = insertar_elemento(raiz->izq, valor);
    // Si el dato es mayor que la raiz, se coloca a la derecha
    else if (valor > raiz->dato) raiz->der = insertar_elemento(raiz->der, valor);
    // Si es igual, no se inserta (Evita duplicados)
    return raiz;
}

void imprimir_arbol(Nodo* raiz, int nivel) {
    if (raiz == NULL) return;
    // Rama derecha
    imprimir_arbol(raiz->der, nivel + 1);
    for (int i = 0; i < nivel; i++) printf("   ");
    printf("%d\n", raiz->dato);
    // Rama izquierda
    imprimir_arbol(raiz->izq, nivel + 1);
}

Nodo* buscar_elemento(Nodo *raiz, int valor)
{
    if(raiz == NULL)//regresa null por si no encontro el elemento
        return NULL;
        
    if(raiz->dato == valor) // si el valor pedido es el mismo que el dato en el nodo se regresa el valor
        return raiz;

    if(valor < raiz->dato)//si el valor es menor que el dato del nodo se va a para la izquierda
        return buscar_elemento(raiz->izq, valor);
    else
        return buscar_elemento(raiz->der, valor);//por el contrario se va a la derecha si es mayor
    
}

Nodo* eliminar_elemento(Nodo **raiz, int valor) {
    Nodo *actual = *raiz, *anterior = NULL, *buscar, *buscar_anterior;
    // Buscar el nodo a eliminar
    while (actual != NULL && actual->dato != valor)
    {
        anterior = actual;
        if (valor > actual->dato)
            actual = actual->der;
        else
            actual = actual->izq;
    }
    // Si el nodo se encontro en el arbol
    if (actual == NULL)
        printf("El valor no existe en el arbol\n");
    else
    {
        // Si el nodo a eliminar tiene hijo por la izquierda buscar el nodo mas grande del sub arbol izquierdo
        if (actual->izq != NULL)
        {
            buscar_anterior = actual;
            buscar = actual->izq;
            // Buscar el nodo mas a la derecha del sub arbol izquierdo
            while (buscar->der != NULL)
            {
                buscar_anterior = buscar;
                buscar = buscar->der;
            }
            actual->dato = buscar->dato;
            // Si tiene un hijo a la izquierda sustituir las referencias al nodo que se va a intercambiar por el nodo izquierdo
            if (buscar->izq != NULL)
            {
                if (buscar_anterior == actual)
                    buscar_anterior->izq = buscar->izq;
                else
                    buscar_anterior->der = buscar->izq;
            }
            else
            {
                if (buscar_anterior == actual)
                    buscar_anterior->izq = NULL;
                else
                    buscar_anterior->der = NULL;
            }
            free(buscar);
        }
        // Si el nodo a eliminar tiene hijo por la derecha y no por la izquierda, buscar el nodo mas grande del sub arbol derecho
        else if (actual->der != NULL)
        {
            buscar_anterior = actual;
            buscar = actual->der;
            // Buscar el nodo mas a la izquierda del sub arbol derecho
            while (buscar->izq != NULL)
            {
                buscar_anterior = buscar;
                buscar = buscar->izq;
            }
            actual->dato = buscar->dato;
            // Si tiene un hijo a la derecha sustituir las referencias al nodo que se va a intercambiar por el nodo derecho
            if (buscar->der != NULL)
            {
                if (buscar_anterior == actual)
                    buscar_anterior->der = buscar->der;
                else
                    buscar_anterior->izq = buscar->der;
            }
            else
            {
                if (buscar_anterior == actual)
                    buscar_anterior->der = NULL;
                else
                    buscar_anterior->izq = NULL;
            }
            free(buscar);
        }
        // Si no tiene hijos liberar el nodo y eliminar las referencias al mismo
        else
        {
            if (anterior != NULL)
            {
                if (actual->dato < anterior->dato)
                    anterior->izq = NULL;
                else
                    anterior->der = NULL;
            }
            else
                *raiz = NULL;
            free(actual);
        }
    }
}