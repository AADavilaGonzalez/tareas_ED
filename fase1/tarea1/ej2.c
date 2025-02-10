/*
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


void imprimir_producto(Producto *productos, int num_productos);
void introducir_datos(Producto *productos);
void venta_producto(Producto *productos);
void restock_producto(Producto *productos);
void actualizar_precio_producto(Producto *productos);
void informe_productos(Producto *productos);

int main(void)
{
    Producto productos[MAX_PRODUCTOS];
    Producto *ptr_productos;
    int op1 = 0, i = 0;

    ptr_productos = productos;

    introducir_datos(ptr_productos);

    while(1){
        while (1)
        {
            printf("Introduzca una opcion:\n"
                "1.- Venta de un producto\n"
                "2.- Reabastecimiento de un producto\n"
                "3.- Actualizar el precio de un producto\n"
                "4.- Informar sobre un producto\n"
                "5.- Salir\n");
            if (scanf("%d", &op1) != 1)
            {
                printf("Introduzca un numero valido\n\n");
                while (getchar() != '\n')
                    ;
                continue;
            }
            if (op1 <= 0 || op1 > 6)
            {
                printf("Introduzca un numero positivo\n\n");
                continue;
            }
            break;
        }
        switch (op1){
        case 1:
            venta_producto(ptr_productos);
            break;
        case 2:
            restock_producto(ptr_productos);
            break;
        case 3:
            actualizar_precio_producto(ptr_productos);
            break;
        case 4:
            informe_productos(ptr_productos);
            break;
        }
        if(op1 == 5) break;
        for(i = 0; i<= 50; i++) printf("\n");
    }
    return 0;
}

void imprimir_producto(Producto *productos, int num_producto){
    printf("\n\n\n\t\tNumero de producto: %d\n", num_producto);
    printf("\t\tClave del producto: %d\n", productos->clave);
    printf("\t\tDescripcion del producto: %s\n", productos->descrip);
    printf("\t\tExistencia del producto: %d\n", productos->exist);
    printf("\t\tExistencia minima del producto: %d\n", productos->min_exist);
    printf("\t\tPrecio unitario del producto: %f\n\n\n", productos->precio_uni);
    return;
}

void introducir_datos(Producto *productos){
    int num_productos = 0, op1 = 0, op2 = 0, i = 0;

    while (num_productos < MAX_PRODUCTOS)
    {
        while (1)
        { // Ciclo para verificar si la informacion es correcta
            printf("Introduzca los datos solicitados\n");
            printf("Producto %d: \n", num_productos + 1);
            while (1){
                printf("Introduzca la clave del producto\n");
                if (scanf("%d", &productos[num_productos].clave) != 1){
                    printf("Introduzca un numero valido\n\n");
                    while (getchar() != '\n');
                    continue;
                }
                if (productos[num_productos].clave <= 0){
                    printf("Introduzca un numero positivo\n\n");
                    continue;
                }
                break;
            }
            printf("Introduzca la descripcion del producto\n");
            scanf("%s", productos[num_productos].descrip);
            while (1){
                printf("Introduzca la existencia del producto\n");
                if (scanf("%d", &productos[num_productos].exist) != 1){
                    printf("Introduzca un numero valido\n\n");
                    while (getchar() != '\n');
                    continue;
                }
                if (productos[num_productos].exist <= 0){
                    printf("Introduzca un numero positivo\n\n");
                    continue;
                }
                break;
            }
            while (1){
                printf("Introduzca la existencia minima del producto\n");
                if (scanf("%d", &productos[num_productos].min_exist) != 1){
                    printf("Introduzca un numero valido\n\n");
                    while (getchar() != '\n');
                    continue;
                }
                if (productos[num_productos].min_exist <= 0){
                    printf("Introduzca un numero positivo\n\n");
                    continue;
                }
                break;
            }
            while (1){
                printf("Introduzca el precio unitario del producto\n");
                if (scanf("%f", &productos[num_productos].precio_uni) != 1){
                    printf("Introduzca un numero valido\n\n");
                    while (getchar() != '\n')
                        ;
                    continue;
                }
                if (productos[num_productos].precio_uni <= 0){
                    printf("Introduzca un numero positivo\n\n");
                    continue;
                }
                break;
            }
            imprimir_producto(productos, num_productos+1);
            while (1){
                printf("¿La informacion introducida es correcta? (1.- Si | 2.- No)\n");
                if (scanf("%d", &op1) != 1){
                    printf("Introduzca un numero valido\n\n");
                    while (getchar() != '\n')
                        ;
                    continue;
                }
                if (op1 < 0 || op1 > 3){
                    printf("Introduzca un numero positivo\n\n");
                    continue;
                }
                break;
            }
            if (op1 == 1){
                break;
            }
        }
        while (1){
            printf("¿Desea agregar otro producto? (1.- Si | 2.- No)\n");
            if (scanf("%d", &op2) != 1){
                printf("Introduzca un numero valido\n");
                while (getchar() != '\n');
                continue;
            }
            if (op2 < 0 || op2 > 3){
                printf("Introduzca un numero positivo\n");
                continue;
            }
            break;
        }
        if (op2 == 2){
            for(i = 0; i<= 50; i++) printf("\n");
            break;
        }else{
            for(i = 0; i<= 50; i++) printf("\n");
            num_productos += 1;
        }
    }
}

void venta_producto(Producto *productos){

}

void restock_producto(Producto *productos){

}

void actualizar_precio_producto(Producto *productos){

}

void informe_productos(Producto *productos){

}
