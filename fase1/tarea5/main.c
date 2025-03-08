#include <stdio.h>
#include <stdlib.h>
#define EDLIB_MAIN
#include "edlib.h"

#define dato_t int

struct nodo_s {
    dato_t dato;
    int prioridad;
    struct nodo_s *siguiente;
};

typedef struct nodo_s *Nodo;

// Inserta un elemento a la cola basado en su prioridad
void colaInsertar(Nodo *cola, dato_t valor, int prioridad)
{
    Nodo actual, nuevo;
    nuevo = (Nodo)malloc(sizeof(struct nodo_s));
    nuevo->dato = valor;
    nuevo->prioridad = prioridad;
    nuevo->siguiente = NULL;

    if (*cola == NULL || prioridad > (*cola)->prioridad)
    {
        nuevo->siguiente = *cola;
        *cola = nuevo;
    }
    else
    {
        actual = *cola;
        while (actual->siguiente != NULL && actual->siguiente->prioridad >= prioridad)
            actual = actual->siguiente;
        nuevo->siguiente = actual->siguiente;
        actual->siguiente = nuevo;
    }
}

// Elimina el elemento al frente de la cola
void colaAtenderFrente(Nodo *cola)
{
    if (*cola == NULL)
        printf("La cola esta vacia\n");
    else
    {
        Nodo temporal = *cola;
        *cola = (*cola)->siguiente;
        free(temporal);
    }
}

// Busca el elemento dado en la cola y lo elimina si lo encuentra
void colaAbandono(Nodo *cola, dato_t valor)
{
    Nodo actual, previo;
    if (*cola == NULL)
    {
        printf("La cola esta vacia\n");
        return;
    }

    actual = *cola;
    previo = NULL;

    while (actual != NULL && actual->dato != valor)
    {
        previo = actual;
        actual = actual->siguiente;
    }

    if (actual == NULL)
    {
        printf("No se encontro el elemento en la cola\n");
        return;
    }

    if (previo == NULL) // Si el elemento es el primero en la cola
        *cola = actual->siguiente;
    else
        previo->siguiente = actual->siguiente;
    free(actual);
}

void colaImprimir(Nodo cola)
{
    Nodo actual = cola;
    int pos = 0;
    printf("\n");
    while (actual != NULL)
    {
        printf("[Posicion: %d, Valor: %d, Prioridad: %d]\n", pos, actual->dato, actual->prioridad);
        actual = actual->siguiente;
        pos++;
    }
    printf("\n");
}

int main()
{
    Nodo cola = NULL;
    int opcion, prioridad, dato;

    printf("¡Bienvenido!\n");

    while(1)
    {

        printf("\nElige una opcion para continuar:\n"
        "1. Insertar a la cola.\n"
        "2. Eliminar de la cola.\n"
        "3. Imprimir.\n"
        "4. Salir.\n");
        opcion = validar_int_en_rango(1, 4);

        switch (opcion)
        {
        case 1:
            printf("Ingrese el dato: \n");
            dato = validar_int();
            printf("Ingrese la prioridad que tendra el dato:\n ");
            prioridad = validar_int_min(0);
            colaInsertar(&cola, dato, prioridad);
            break;

        case 2:
            printf("Ingrese el dato a eliminar\n");
            dato = validar_int();
            colaAbandono(&cola, dato);
            break;

        case 3:
            printf("Imprimiendo cola\n");
            colaImprimir(cola);
            break;

        default:
            exit(1);
            break;
        }

    }

    return 0;
}
