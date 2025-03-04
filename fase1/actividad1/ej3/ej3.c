#include <stdio.h>
#include <stdlib.h>
#include <time.h>

typedef struct nodo
{
    int numero;
    struct nodo *siguiente;
} Nodo;

typedef struct cola
{
    Nodo *frente;
    Nodo *final;
} Cola;


void inicializar(Cola * cola_actual)
{
    cola_actual -> frente = NULL;
    cola_actual -> final = NULL;
}

void crearcola(Cola *colanumeros, int valor)
{
    Nodo *nuevo;

    nuevo = (Nodo*)malloc(sizeof(Nodo));
    if (nuevo == NULL)
    {
        printf("Error, no se pudo asignar memoria\n");
        exit(1);
    }

    nuevo -> numero = valor;
    nuevo -> siguiente = NULL;

    if(colanumeros -> frente == NULL)
    {
        colanumeros -> frente = nuevo;
        colanumeros -> final = nuevo;
    }

    else
    {
        colanumeros -> final -> siguiente = nuevo;
        colanumeros -> final = nuevo;
    }
}

int quitar(Cola *colanumeros)
{
    Nodo *temporal;
    int valor;

    temporal = colanumeros -> frente;
    valor = temporal -> numero;
    colanumeros -> frente = colanumeros -> frente -> siguiente;

    if(colanumeros -> frente == NULL)
        colanumeros -> final = NULL;

    free(temporal);
    return valor;
}

void imprimir(Cola *colausada)
{
    Nodo *actual;

    if(colausada -> frente == NULL)
    {
        printf("La cola esta vacia\n");
        exit(1);
    }

    actual = colausada -> frente;
    while (actual != NULL)
    {
        printf("%d ", actual -> numero);
        actual = actual -> siguiente;
    }
    printf("\n\n");
}

void negativos(Cola *colanumeros, Cola *colanegativa)
{
    Cola temporal;
    int valor;

    inicializar(&temporal);

    while (!(colanumeros -> frente == NULL))
    {
        valor = quitar(colanumeros);

        if(valor < 0)
            crearcola(colanegativa, valor);

        crearcola(&temporal, valor);

    }

    while(!(colanumeros -> frente == NULL))
        crearcola(colanumeros, quitar(&temporal));
}
int main()
{
    srand(time(NULL));

    Cola colanumeros, cola_negativa;
    int i, num, min = -25, max = 25, random;

    inicializar(&colanumeros);
    inicializar(&cola_negativa);

    for(i = 0; i < 100; i++)
    {
        num = min + rand() % (max - min + 1);
        crearcola(&colanumeros, num);
    }

    printf("Cola de numeros: \n");
    imprimir(&colanumeros);

    negativos(&colanumeros, &cola_negativa);

    printf("Cola con numeros negativos:\n");
    imprimir(&cola_negativa);

    return 0;

}
