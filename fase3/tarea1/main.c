#include <stdio.h>
#include <stdlib.h>

void limpiar_pantalla();
void crear_arbol();
void buscar_elemento();
void insertar_elemento();
void eliminar_elemento();

typedef struct nodo{
    int dato;
    struct nodo *izq;
    struct nodo *der;
} Nodo;

int main(void){
    int op1;

    while(1){
        // Ciclo para validar el menu
        while(1){
            printf("Seleccione una opcion.\n"
                "1.- Crear un arbol binario\n"
                "2.- Buscar un elemento del arbol\n"
                "3.- Insertar un elemento en el arbol\n"
                "4.- Eliminar un elemento del arbol\n"
                "5.- Salir");
            if(scanf("%d", &op1) != 1 || op1 < 1 || op1 > 5){
                printf("Introduzca un número valido\n\n");
                while(getchar() != '\n');
                continue;
            }
            limpiar_pantalla();
            break;
        }
        switch (op1){
        case 1:
            Nodo *raiz = NULL;
            break;
        case 2:
            if(raiz != NULL){
                buscar_elemento();
                break;
            }
            if(raiz == NULL){
                printf("El arbol esta vacio\n");
            }else{
                printf("El arbol no esta creado\n");
            }
            break;
        case 3:
            insertar_elemento();
            break;
        case 4:
            if(raiz == NULL){
                printf("El arbol esta vacio\n");
                continue;
            }else{
                eliminar_elemento();
            }
            break;
        }
        if(op1 == 5){
            break;
        }
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

void crear_arbol(){

}

void buscar_elemento(){
}

void insertar_elemento(){

}

void eliminar_elemento(){

}