#include <stdio.h>
#include <stdlib.h>

typedef struct nodo{
    int dato;
    struct nodo *izq;
    struct nodo *der;
} Nodo;

void limpiar_pantalla();
Nodo* crear_nodo(int valor);
Nodo* insertar_elemento(Nodo* raiz, int valor);
void inorder(Nodo *raiz);
Nodo* buscar_elemento(Nodo *raiz, int valor);
void imprimir_arbol(Nodo* raiz, int nivel);

int main(void){
    int op1, val = 0, num, i, valor;
    Nodo *raiz = NULL;

    while(1){
        // Ciclo para validar el menu
        while(1){
            printf("Seleccione una opcion.\n"
                "1.- Crear un arbol binario\n"
                "2.- Buscar un elemento del arbol\n"
                "3.- Insertar un elemento en el arbol\n"
                "4.- Eliminar un elemento del arbol\n"
                "5.- Imprimir el arbol\n"
                "6.- Salir\n");
            if(scanf("%d", &op1) != 1 || op1 < 1 || op1 > 6){
                printf("Introduzca un número valido\n\n");
                while(getchar() != '\n');
                continue;
            }
            limpiar_pantalla();
            break;
        }
        switch (op1){
            case 1:
                if(val == 0){
                    while(1){
                        printf("Introduzca el numero de elementos a insertar: \n");
                        if(scanf("%d", &num) != 1 || num < 0){
                            printf("Introdzuca un número valido\n");
                            while(getchar() != '\n');
                            continue;
                        }
                        break;
                    }
                    for(i = 0; i < num; i++){
                        printf("Introduzca un entero\n");
                        if(scanf("%d", &valor) != 1){
                            printf("Introdzuca un número valido\n");
                            while(getchar() != '\n');
                            continue;
                        }
                        raiz = insertar_elemento(raiz, valor);
                    }
                    printf("\nArbol: \n");
                    imprimir_arbol(raiz, 0);
                    printf("\n\n");
                    val = 1;
                    break;
                }
                if(val == 1) printf("El arbol ya ha sido creado\n\n");
                break;
            case 2:
                break;
            case 3:
                if(val == 1){
                    printf("Introduzca un entero\n");
                    if(scanf("%d", &valor) != 1){
                        printf("Introduzca un número valido\n");
                        while(getchar() != '\n');
                        continue;
                    }
                    insertar_elemento(raiz, valor);
                    printf("Arbol: \n");
                    imprimir_arbol(raiz, 0);
                    
                    printf("\n\n");
                    break;
                }
                if(val == 0) printf("El arbol no a sido creado\n\n");
                break;
            case 4:
                break;
            case 5:
                if(val == 1 && raiz != NULL){
                    imprimir_arbol(raiz, 0);
                    printf("\n\n");
                    break;
                }
                if(val == 0) printf("El arbol no a sido creado\n\n");
                if(raiz == NULL) printf("El arbol esta vacio\n\n");
                break;
        }
        if(op1 == 6){
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

Nodo *crear_nodo(int valor){
    Nodo *nuevo = (Nodo *)malloc(sizeof(Nodo));
    if(nuevo == NULL){
        printf("Error al asignar la memoria\n");
        exit(1);
    }
    nuevo->dato = valor;
    nuevo->izq = nuevo->der = NULL;
    return nuevo;
}

Nodo *insertar_elemento(Nodo *raiz, int valor){
    // Si el arbol no tiene elementos
    if(raiz == NULL) return crear_nodo(valor);
    // Si el valor es menor que la raiz, se coloca en la izquierda
    if(valor < raiz->dato) raiz->izq = insertar_elemento(raiz->izq, valor);
    // Si el dato es mayor que la raiz, se coloca a la derecha
    else if(valor > raiz->dato) raiz->der = insertar_elemento(raiz->der, valor);
    // Si es igual, no se inserta (Evita duplicados)
    return raiz;
}

void inorder(Nodo *raiz){
    if(raiz != NULL){
        inorder(raiz->izq);
        printf("%d ", raiz->dato);
        inorder(raiz->der);
    }
}

void imprimir_arbol(Nodo* raiz, int nivel){
    if (raiz == NULL) return;
    // Rama derecha
    imprimir_arbol(raiz->der, nivel + 1);
    for (int i = 0; i < nivel; i++) printf("   ");
    printf("%d\n", raiz->dato);
    // Rama izquierda
    imprimir_arbol(raiz->izq, nivel + 1);
}

