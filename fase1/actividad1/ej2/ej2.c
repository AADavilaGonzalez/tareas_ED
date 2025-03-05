#include <stdio.h>
#include <string.h>
#include <stdbool.h>

#include "lista_s.h"

typedef struct pila
{
    Nodo_S *frente;
} Pila_S;

// Inicializa la pila estableciendo el puntero frente a NULL
void inicializarPila(Pila_S *pila)
{
    pila->frente = NULL;
}

// Inserta el elemento a la cima de la pila
void pilaInsertar(Pila_S *pila, char valor)
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
    nuevo->sig = pila->frente;
    pila->frente = nuevo;
}

// Quita y retorna el elemento que esta en la cima de la pila si no esta vacia
char pilaQuitar(Pila_S *pila)
{
    Nodo_S *temporal;
    char valor = 0;

    temporal = pila->frente;
    if (temporal == NULL)
        printf("Pila vacia, no se pueden quitar mas elementos\n");
    else
    {
        valor = temporal->dato;
        pila->frente = pila->frente->sig;
        free(temporal);
    }
    return valor;
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
    frase[strcspn(frase, "\n")] = '\0'; // Elimina el '\n' incluido por el fgets

    // Itera sobre la cadena y agrega caracter por caracter a la pila y a la lista
    i = 0;
    while (frase[i] != '\0')
    {
        pilaInsertar(&pila_caracteres, frase[i]);
        lista_s_insertar_fin(lista_caracteres, frase[i]);
        i++;
    }
    frase_longitud = i;

    // Si todos los caracteres extraidos de ambas son iguales al compararse entonces es palindroma
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