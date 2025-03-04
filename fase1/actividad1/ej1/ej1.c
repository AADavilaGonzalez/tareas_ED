#include <stdio.h>
#include <time.h>
#include "lista_s.h"

void limpiar_pantalla();
void eliminar_nodos_mayores(Lista_S *lista, int num);
void mostrar_lista(Lista_S *lista);

int main(void){
    int op1, op2, i, aux = 0, tamano, dato, num;
    Lista_S *lista;

    srand(time(NULL));

    while(1){
        while(1){
            limpiar_pantalla();
            printf("Introduzca una de las opciones\n"
            "1.- Crear lista\n"
            "2.- Imprimir lista\n"
            "3.- Eliminar nodos dado un valor\n"
            "4.- Salir\n");
            if(scanf("%d", &op1) != 1 || op1 < 1 || op1 > 5){
                while(getchar() != '\n');
                continue;
            }
            break;
        }
        switch(op1){
            case 1:
                limpiar_pantalla();
                while(1){
                    printf("Introduzca un numero para el tamaño de la lista (1 para regresar al menu)\n");
                    if(scanf("%d", &tamano) != 1 || tamano < 0){
                        printf("Introduzca un numero valido\n");
                        while(getchar() != '\n');
                        continue;
                    }
                    break;
                }
                lista = lista_s_crear();
                for(i = 0; i < tamano; i++){
                    dato = (rand() % 100) + 1;
                    lista_s_insertar_fin(lista, dato);
                }
                printf("\n\n Lista creada \n\n");
                aux = 1;
                while(1){
                    if(scanf("%d", &op2) != 1 || op2 != 1){
                        printf("Introduzca un numero valido\n");
                        while(getchar() != '\n');
                        continue;
                    }
                    break;
                }
                if(op2 == 1)
                    break;
            case 2:
                limpiar_pantalla();
                printf("(1 para regresar al menu)\n");
                if(aux == 0){
                    lista = lista_s_crear();
                }
                mostrar_lista(lista);
                while(1){
                    if(scanf("%d", &op2) != 1 || op2 != 1){
                        printf("Introduzca un numero valido\n");
                        while(getchar() != '\n');
                        continue;
                    }
                    break;
                }
                if(op2 == 1)
                    break;
            case 3:
                limpiar_pantalla();
                mostrar_lista(lista);
                while(1){
                    printf("Introduzca un numero\n");
                    while(1){
                        if(scanf("%d", &num) != 1 || num < 0){
                            printf("Introduzca un valor valido\n");
                            while(getchar() != '\n');
                            continue;
                        }
                        break;
                    }
                    break;
                }
                eliminar_nodos_mayores(lista, num);
                mostrar_lista(lista);
                printf("(1 para regresar al menu)\n");

                while(1){
                    if(scanf("%d", &op2) != 1 || op2 != 1){
                        printf("Introduzca un numero valido\n");
                        while(getchar() != '\n');
                        continue;
                    }
                    break;
                }
                if(op2 == 1)
                    break;
            case 4:
                lista_s_destruir(lista);
                break;
        }
        if(op1 == 4){
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

void eliminar_nodos_mayores(Lista_S *lista, int num){
    Nodo_S *actual = lista->cabeza;
    Nodo_S *anterior = NULL;
    while(actual != NULL){
        if(actual->dato > num){
            if(anterior == NULL){
                lista->cabeza = actual->sig;
                free(actual);
                actual = lista->cabeza;
            }else{
                anterior->sig = actual->sig;
                free(actual);
                actual = anterior->sig;
                --(lista->tamano);
            }
        }else{
            anterior = actual;
            actual = actual->sig;
        }
    }
    return;
}

void mostrar_lista(Lista_S *lista){
    Nodo_S *actual = lista->cabeza;
    printf("Lista -> ");
    if(actual != NULL){
        while(actual != NULL){
            printf("%.2f -> ", actual->dato);
            actual = actual->sig;
        }
    }
    printf("NULL\n");
    return;
}