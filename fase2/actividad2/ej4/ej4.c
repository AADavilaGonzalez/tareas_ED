#include <stdio.h>
#include <stdlib.h>

#define EDLIB_MAIN
#include "edlib.h"

/* Compara los valores dentro del vector recursivamente 
desde el ultimo elemento hasta llegar al primero y devuelve
el mas grande de todos */
int valor_maximo(int *vector, int longitud)
{
    int max;
    // Caso base: Al llegar al primer elemento retornar el elemento
    if (longitud == 1)
        return vector[0];
    else
    {
        /* Se llama a si misma con una longitud menos para 
         ir comparando con el elemento que esta antes */
        max = valor_maximo(vector, longitud - 1);
        if (vector[longitud - 1] > max)
            return vector[longitud - 1];
        else
            return max;
    }
}

int main()
{
    int longitud, i, *vector, max_num;
    printf("Introduzca la longitud del vector: \n");
    longitud = validar_int_min(1);
    vector = (int*)malloc(sizeof(int) * longitud);

    // Pedir todos los datos del vector
    for (i = 0; i < longitud; i++)
    {
        printf("Introduzca el valor para la posicion %d del vector\n", i);
        vector[i] = validar_int();
    }

    max_num = valor_maximo(vector, longitud);
    printf("El valor maximo del vector es: %d\n", max_num);

    free(vector);
    return 0;
}