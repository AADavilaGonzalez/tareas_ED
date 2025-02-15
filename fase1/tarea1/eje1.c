#include <stdio.h>
#define EDLIB_MAIN
#include "edlib.h"


void registrar(int [4][3], int *);
int pedidos(int [4][3], int [100][2]);
void resultado(int [4][3], int [100][2], int, int *);

int main()
{
    int plazas[4][3], rechazados[100][2], contador, *ap = plazas[0];

    registrar(plazas, ap);
    contador = pedidos(plazas, rechazados);
    resultado(plazas, rechazados, contador, ap);


    return 0;
}

void registrar(int plazas[4][3], int *ap)
{
    int i, j;

    for(i = 0; i < 4; i++)
    {
        for(j = 0; j < 3; j++)
        {

            printf("Plazas disponibles para el destino %d, vuelo %d: ", i + 1, j + 1);
            *ap = validar_int_min(0);
            ap++;
        }
        printf("\n");

    }
}
int pedidos(int plazas[4][3], int rechazados[100][2])
{
    int pedido, destino, vuelo, pasajes, contador = 0;
    char respuesta;

    do
    {
        printf("Desea agregar un pedido? (s/n)\n");
        respuesta = leer_caracter();

    }while (respuesta != 'S' && respuesta != 's' && respuesta != 'N' && respuesta != 'n');


    while(respuesta == 's' || respuesta == 'S')
    {

        printf("Ingrese el numero de pedido: \n");
        pedido = validar_int_min(1);

        printf("Ingrese el numero de destino (1-4): \n");
        destino = validar_int_en_rango(1,4);

        printf("Ingrese el numero de vuelo (1-3): \n");
        vuelo = validar_int_en_rango(1,3);

        printf("Cuantos pasajes se requieren?: \n");
        pasajes = validar_int_min(0);

        int *plaza = &plazas[destino - 1][vuelo - 1];

        if(pasajes <= *plaza)
        {
            *plaza -= pasajes;
            printf("Plazas disponibles %d\n", *plaza);

        }

        else
        {
            printf("No hay suficientes plazas\n");

            if(contador < 100)
            {
                rechazados[contador][0]= pedido;
                rechazados[contador][1]= pasajes;
                contador++;
            }

        }

        do
        {
            printf("Desea agregar otro pedido? (s/n)\n");
            respuesta = leer_caracter();

        } while (respuesta != 'S' && respuesta != 's' && respuesta != 'N' && respuesta != 'n');
    }
    return contador;

}

void resultado(int plazas[4][3], int rechazados[100][2], int contador, int *ap)
{
    int i, j;

    printf("Pasajes sobrantes\n");
    for(i = 0; i < 4; i++)
    {
        for(j = 0; j < 3; j++)
        {
            printf("Destino %d, vuelo %d, quedan %d pasajes \n", i + 1, j + 1, plazas[i][j]);
        }
        printf("\n");

    }

    printf("Pedidos rechazados\n");

    if(contador == 0)
        printf("No se rechazaron pedidos\n");

    else
    {
        for(i = 0; i < contador; i++)
        {
            printf("Pedido num. %d fue rechazado, pedia %d pasajes\n", rechazados[i][0], rechazados[i][1]);
        }
    }

}
