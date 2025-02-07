/*
a) Venta de un producto: se debe actualizar los campos que
correspondan, y verificar que la nueva existencia no esté por debajo
del mínimo. (Datos: clave, cantidad vendida).

b) Reabastecimiento de un producto: se deben actualizar los campos
que correspondan. (Datos: clave, cantidad comprada).

c) Actualizar el precio de un producto. (Datos: clave, porcentaje de
aumento).

d) Informar sobre un producto: se deben proporcionar todos los datos
relacionados a un producto. (Datos: clave).
*/

#include <stdio.h>

#define MAX_CHAR 51
#define MAX_PRODUCTOS 20

typedef struct
{
    int clave;
    char descrip[MAX_CHAR];
    int exist;
    int min_exist;
    float precio_uni;
} Producto;

void introducir_datos(Producto *productos);

int main(void)
{
    Producto productos[MAX_PRODUCTOS];
    Producto *ptr_productos;

    ptr_productos = productos;

    introducir_datos(ptr_productos);
    

    return 0;
}

void introducir_datos(Producto *productos){
    int num_productos = 0, op1 = 0, op2 = 0;

    while (num_productos < MAX_PRODUCTOS)
    {
        while (1)
        { // Ciclo para verificar si la informacion es correcta
            printf("Introduzca los datos solicitados\n");
            printf("Producto %d: \n", num_productos + 1);
            while (1)
            {
                printf("Introduzca la clave del producto\n");
                if (scanf("%d", &productos[num_productos].clave) != 1)
                {
                    printf("Introduzca un numero valido\n\n");
                    while (getchar() != '\n');
                    continue;
                }
                if (productos[num_productos].clave <= 0)
                {
                    printf("Introduzca un numero positivo\n\n");
                    continue;
                }
                break;
            }
            printf("Introduzca la descripcion del producto\n");
            scanf("%s", productos[num_productos].descrip);
            while (1)
            {
                printf("Introduzca la existencia del producto\n");
                if (scanf("%d", &productos[num_productos].exist) != 1)
                {
                    printf("Introduzca un numero valido\n\n");
                    while (getchar() != '\n');
                    continue;
                }
                if (productos[num_productos].exist <= 0)
                {
                    printf("Introduzca un numero positivo\n\n");
                    continue;
                }
                break;
            }
            while (1)
            {
                printf("Introduzca la existencia minima del producto\n");
                if (scanf("%d", &productos[num_productos].min_exist) != 1)
                {
                    printf("Introduzca un numero valido\n\n");
                    while (getchar() != '\n');
                    continue;
                }
                if (productos[num_productos].min_exist <= 0)
                {
                    printf("Introduzca un numero positivo\n\n");
                    continue;
                }
                break;
            }
            while (1)
            {
                printf("Introduzca el precio unitario del producto\n");
                if (scanf("%f", &productos[num_productos].precio_uni) != 1)
                {
                    printf("Introduzca un numero valido\n\n");
                    while (getchar() != '\n')
                        ;
                    continue;
                }
                if (productos[num_productos].precio_uni <= 0)
                {
                    printf("Introduzca un numero positivo\n\n");
                    continue;
                }
                break;
            }
            while (1)
            {
                printf("¿La informacion introducida es correcta? (1.- Si | 2.- No)\n");
                if (scanf("%d", &op1) != 1)
                {
                    printf("Introduzca un numero valido\n\n");
                    while (getchar() != '\n')
                        ;
                    continue;
                }
                if (op1 < 0 || op1 > 3)
                {
                    printf("Introduzca un numero positivo\n\n");
                    continue;
                }
                break;
            }
            if (op1 == 1)
            {
                break;
            }
        }
        while (1)
        {
            printf("¿Desea agregar otro producto? (1.- Si | 2.- No)\n");
            if (scanf("%d", &op2) != 1)
            {
                printf("Introduzca un numero valido\n");
                while (getchar() != '\n')
                    ;
                continue;
            }
            if (op2 < 0 || op2 > 3)
            {
                printf("Introduzca un numero positivo\n");
                continue;
            }
            break;
        }
        if (op2 == 2)
        {
            break;
        }
        else
        {
            num_productos += 1;
        }
    }
}