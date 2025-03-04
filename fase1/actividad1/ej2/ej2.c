#include <stdio.h>
#include <string.h>
#include <stdbool.h>

#include "lista_s.h"

typedef struct pila
{
    Nodo_S *frente;
    Nodo_S *final;
} Pila_S;

void inicializarPila(Pila_S *cola)
{
    cola->frente = NULL;
    cola->final = NULL;
}

void pilaInsertar(Pila_S *cola, char valor)
{
    Nodo_S *nuevo;

    nuevo = (Nodo_S*)malloc(sizeof(Nodo_S));
    if (nuevo == NULL)
    {
        printf("Error, no se pudo asignar memoria\n");
        return;
    }

    nuevo->dato = valor;
    nuevo->sig = NULL;

    if (cola->final == NULL)
    {
        cola->final = nuevo;
        cola->frente = nuevo;
    }
    else
    {
        nuevo->sig = cola->frente;
        cola->frente = nuevo;
    }
}

char pilaQuitar(Pila_S *cola)
{
    Nodo_S *temporal;
    int valor;

    temporal = cola->frente;
    valor = temporal->dato;
    cola->frente = cola->frente->sig;

    if (cola->frente == NULL)
        cola->final = NULL;

    free(temporal);
    return valor;
}

void imprimirPila(Pila_S *cola)
{
    Nodo_S *actual;

    if (cola -> frente == NULL)
    {
        printf("La cola esta vacia\n");
        return;
    }

    actual = cola->frente;
    while (actual != NULL)
    {
        printf("%d ", actual->dato);
        actual = actual->sig;
    }
    printf("\n\n");
}

int main()
{
    Lista_S *lista_caracteres;
    Pila_S pila_caracteres;
    int frase_longitud, i;
    char frase[40], caracter_pila, caracter_lista;
    bool palindroma = true;

    lista_caracteres = lista_s_crear();
    inicializarPila(&pila_caracteres);

    printf("Introduce una frase: ");
    fgets(frase, 40, stdin);
    frase[strcspn(frase, "\n")] = '\0';

    i = 0;
    while (frase[i] != '\0')
    {
        pilaInsertar(&pila_caracteres, frase[i]);
        lista_s_insertar_fin(lista_caracteres, frase[i]);
        i++;
    }
    frase_longitud = i;

    i = 0;
    while (i < frase_longitud && palindroma)
    {
        caracter_pila = pilaQuitar(&pila_caracteres);
        caracter_lista = lista_s_eliminar_inicio(lista_caracteres);
        if (caracter_pila != caracter_lista)
            palindroma = false;
        i++;
    }

    if (palindroma)
        printf("La frase '%s' es palindroma\n", frase);
    else
        printf("La frase '%s' NO es palindroma\n", frase);

    return 0;
}