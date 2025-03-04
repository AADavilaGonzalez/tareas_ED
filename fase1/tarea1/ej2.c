#include <stdio.h>
#include <stdlib.h>

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

void limpiar_pantalla();
int obtener_clave();
void imprimir_producto(Producto *productos, int num_productos);
void introducir_datos(Producto *productos, int* num_productos);
void venta_producto(Producto *productos, int *num_productos);
void restock_producto(Producto *productos, int *num_productos);
void actualizar_precio_producto(Producto *productos, int *num_productos);
void informe_productos(Producto *productos, int *num_productos);

int main(void)
{
    Producto productos[MAX_PRODUCTOS];
    Producto *ptr_productos;
    int op1 = 0, i = 0;
    int num_productos = 0;
    int *ptr_num_productos;

    ptr_productos = productos;
    ptr_num_productos = &num_productos;

    introducir_datos(ptr_productos, ptr_num_productos);

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
                while (getchar() != '\n');
                continue;
            }
            if (op1 < 0 || op1 > 6)
            {
                printf("Introduzca un numero positivo\n\n");
                continue;
            }
            break;
        }
        switch (op1){
        case 1:
            limpiar_pantalla();
            venta_producto(ptr_productos, ptr_num_productos);
            break;
        case 2:
            limpiar_pantalla();
            restock_producto(ptr_productos, ptr_num_productos);
            break;
        case 3:
            limpiar_pantalla();
            actualizar_precio_producto(ptr_productos, ptr_num_productos);
            break;
        case 4:
            limpiar_pantalla();
            informe_productos(ptr_productos, ptr_num_productos);
            break;
        }
        if(op1 == 5) break;
        limpiar_pantalla();
    }
    return 0;
}

void limpiar_pantalla(){
    #ifdef _WIN32
        system("cls");
    #else
        system("clear");
    #endif
}

int obtener_clave()
{
    int clave;
    while (1){
        printf("Introduzca la clave del producto (\"-1\" para Salir)\n");
        if (scanf("%d", &clave) != 1 || (clave < -1)){
            printf("Introduzca un numero valido\n\n");
            while (getchar() != '\n');
            continue;
        }
        break;
    }
    return clave;
}

void imprimir_producto(Producto *productos, int indice)
{
    printf("\n\n\n\t\tNumero de producto: %d\n", indice+1);
    printf("\t\tClave del producto: %d\n", productos[indice].clave);
    printf("\t\tDescripcion del producto: %s\n", productos[indice].descrip);
    printf("\t\tExistencia del producto: %d\n", productos[indice].exist);
    printf("\t\tExistencia minima del producto: %d\n", productos[indice].min_exist);
    printf("\t\tPrecio unitario del producto: %f\n\n\n", productos[indice].precio_uni);
    return;
}

void introducir_datos(Producto *productos, int *num_productos)
{
    int op1 = 0, op2 = 0, i = 0;
    while (*num_productos < MAX_PRODUCTOS){
        while (1){// Ciclo para verificar si la informacion es correcta
            printf("Introduzca los datos solicitados\n");
            printf("Producto %d: \n", *num_productos + 1);
            while (1){
                printf("Introduzca la clave del producto\n");
                if (scanf("%d", &productos[*num_productos].clave) != 1){
                    printf("Introduzca un numero valido\n\n");
                    while (getchar() != '\n');
                    continue;
                }
                if (productos[*num_productos].clave <= 0){
                    printf("Introduzca un numero positivo\n\n");
                    continue;
                }
                break;
            }
            printf("Introduzca la descripcion del producto\n");
            scanf("%s", productos[*num_productos].descrip);
            while (1){
                printf("Introduzca la existencia del producto\n");
                if (scanf("%d", &productos[*num_productos].exist) != 1){
                    printf("Introduzca un numero valido\n\n");
                    while (getchar() != '\n');
                    continue;
                }
                if (productos[*num_productos].exist <= 0){
                    printf("Introduzca un numero positivo\n\n");
                    continue;
                }
                break;
            }
            while (1){
                printf("Introduzca la existencia minima del producto\n");
                if (scanf("%d", &productos[*num_productos].min_exist) != 1){
                    printf("Introduzca un numero valido\n\n");
                    while (getchar() != '\n');
                    continue;
                }
                if (productos[*num_productos].min_exist <= 0){
                    printf("Introduzca un numero positivo\n\n");
                    continue;
                }
                break;
            }
            while (1){
                printf("Introduzca el precio unitario del producto\n");
                if (scanf("%f", &productos[*num_productos].precio_uni) != 1){
                    printf("Introduzca un numero valido\n\n");
                    while (getchar() != '\n')
                        ;
                    continue;
                }
                if (productos[*num_productos].precio_uni <= 0){
                    printf("Introduzca un numero positivo\n\n");
                    continue;
                }
                break;
            }
            imprimir_producto(productos, *num_productos);
            while (1){
                printf("¿La informacion introducida es correcta? (1.- Si | 2.- No)\n");
                if (scanf("%d", &op1) != 1 || (op1 != 1 && op1 != 2)){
                    printf("Introduzca un numero valido\n\n");
                    while (getchar() != '\n');
                    continue;
                }
                break;
            }
            if (op1 == 1){
                (*num_productos)++;
                break;
            }
        }
        while (1){
            printf("¿Desea agregar otro producto? (1.- Si | 2.- No)\n");
            if (scanf("%d", &op2) != 1 || (op2 != 1 && op2 != 2))
            {
                printf("Introduzca un numero valido\n");
                while (getchar() != '\n');
                continue;
            }
            break;
        }
        if (op2 == 2){
            limpiar_pantalla();
            break;
        }
        limpiar_pantalla();
    }
}

void venta_producto(Producto *productos, int *num_productos)
{
    int clave, venta, nueva_exist = 0;
    int i = 0, aux = 0, pos = 0, op1;
    while(1){
        aux = 1;
        clave = obtener_clave();
        if(clave == -1){
            break;
        }
        for (i = 0; i < *num_productos; i++) {
            if (productos[i].clave == clave) {
                aux = 0;
                pos = i;
                break;
            }
        }
        if(aux == 1){
            printf("No existe el producto\n\n\n");
            continue;
        }
        while (1){
            printf("Introduzca la cantidad vendida\n");
            if (scanf("%d", &venta) != 1 || (venta < 0)){
                printf("Introduzca un numero valido\n\n");
                while (getchar() != '\n');
                continue;
            }
            break;
        }
        nueva_exist = productos[pos].exist - venta;
        if(nueva_exist < productos[pos].min_exist){
            printf("La nueva existencia esta por debajo del minimo\n\n\n");
            continue;
        }else{
            productos[pos].exist = nueva_exist;
            imprimir_producto(productos, pos);
            printf("Se realizo la venta correctamente\n");
        }
        while (1){
            printf("¿Desea realizar otra venta?(1.- Si 2.- No)\n");
            if (scanf("%d", &op1) != 1 || (op1 < 0)){
                printf("Introduzca un numero valido\n\n\n");
                while (getchar() != '\n');
                continue;
            }
            break;
        }
        if(op1 == 2){
            limpiar_pantalla();
            break;
        }
    }
}

void restock_producto(Producto *productos, int *num_productos)
{
    int clave, compra, i, aux, pos, op1;
    while(1){
        aux = 1;
        clave = obtener_clave();
        if(clave == -1){
            break;
        }
        for (i = 0; i < *num_productos; i++) {
            if (productos[i].clave == clave) {
                aux = 0;
                pos = i;
                break;
            }
        }
        if(aux == 1){
            printf("No existe el producto\n\n\n");
            continue;
        }
        while (1){
            printf("Introduzca la cantidad comprada\n");
            if (scanf("%d", &compra) != 1 || (compra < 0)){
                printf("Introduzca un numero valido\n\n\n");
                while (getchar() != '\n');
                continue;
            }
            break;
        }
        productos[pos].exist += compra;
        printf("\n\nCompra realizada correctamente\n\n");
        imprimir_producto(productos, pos);
        while (1){
            printf("¿Desea realizar otra compra?(1.- Si 2.- No)\n");
            if (scanf("%d", &op1) != 1 || (op1 < 0)){
                printf("Introduzca un numero valido\n\n");
                while (getchar() != '\n');
                continue;
            }
            break;
        }
        if(op1 == 2){
            limpiar_pantalla();
            break;
        }
    }
}

void actualizar_precio_producto(Producto *productos, int *num_productos)
{
    int clave, aux, i, pos, aumento, op1;
    float actual = 0;
    while(1){
        aux = 1;
        clave = obtener_clave();
        if(clave == -1){
            break;
        }
        for (i = 0; i < *num_productos; i++) {
            if (productos[i].clave == clave) {
                aux = 0;
                pos = i;
                break;
            }
        }
        if(aux == 1){
            printf("No existe el producto\n\n\n");
            continue;
        }
        while (1){
            printf("Introduzca el porcentaje de aumento\n");
            if (scanf("%d", &aumento) != 1 || (aumento < 0)){
                printf("Introduzca un numero valido\n\n");
                while (getchar() != '\n');
                continue;
            }
            break;
        }
        actual = productos[pos].precio_uni * (1 + (aumento/100.0));
        productos[pos].precio_uni = actual;
        imprimir_producto(productos, pos);
        printf("\n\nAumento realizado correctamente\n\n");
        printf("Nuevo precio: %f\n", productos[pos].precio_uni);
        while (1){
            printf("¿Desea realizar otro aumento?(1.- Si 2.- No)\n");
            if (scanf("%d", &op1) != 1 || (op1 < 0)){
                printf("Introduzca un numero valido\n\n");
                while (getchar() != '\n');
                continue;
            }
            break;
        }
        if(op1 == 2){
            limpiar_pantalla();
            break;
        }
    }
}

void informe_productos(Producto *productos, int *num_productos)
{
    int i = 0, op1;
    while(1){
        for (i = 0; i < *num_productos; i++){
            imprimir_producto(productos, i);
        }
        while (1){
            printf("\"-1\" para Salir\n");   
            if (scanf("%d", &op1) != 1 || (op1 < -1)){
                printf("Introduzca un numero valido\n\n");
                while (getchar() != '\n');
                continue;
            }
            break;
        }
        if(op1 == -1){
            break;
        }
    }
}
