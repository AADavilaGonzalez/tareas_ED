//falta implementar apuntadores y checar que funcione el programa
#include <stdio.h>

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
            do
            {
                printf("Plazas disponibles para el destino %d, vuelo %d: ", i + 1, j + 1);
                scanf("%d", ap);

                if(*ap < 0)
                    printf("Las plazas no pueden ser menor a 0\n");

            }while(*ap < 0);

            ap++;
        }
    }

}

int pedidos(int plazas[4][3], int rechazados[100][2])
{
    int pedido, destino, vuelo, pasajes, contador = 0;
    char respuesta;

    do
    {
        printf("Desea agregar un pedido? (s/n)\n");
        fflush(stdin);
        scanf("%c", &respuesta);
    } while (respuesta != 'S' && respuesta != 's' && respuesta != 'N' && respuesta != 'n');

    while(respuesta == 's' || respuesta == 'S')
    {
        do
        {
            printf("Ingrese el numero de pedido: \n");
            scanf("%d", &pedido);

            if(pedido < 1)
                printf("El numero de pedido no puede ser menor a 1\n");

        }while(pedido < 1);

        do
        {
            printf("Ingrese el numero de destino (1-4): \n");
            scanf("%d", &destino);

            if(destino < 1 || destino > 4)
                printf("El numero de destino debe estar entre 1 y 4\n");

        }while(destino < 1 || destino > 4);

        do
        {
            printf("Ingrese el numero de vuelo (1-3): \n");
            scanf("%d", &vuelo);

            if(vuelo < 1 || vuelo > 3)
                printf("El numero de vuelo debe estar entre 1 y 3\n");

        }while(vuelo < 1 || vuelo > 3);

        do
        {
            printf("Cuantos pasajes se requieren?: \n");
            scanf("%d", &pasajes);

            if(pasajes < 0)
                printf("El numero de pasajes no debe ser menor a 0\n");
        }while(pasajes < 0);

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
            fflush(stdin);
            scanf("%c", &respuesta);
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
            printf("Destino %d, vuelo %d, quedan %d pasajes\n", i + 1, j + 1, plazas[i][j]);
        }

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
