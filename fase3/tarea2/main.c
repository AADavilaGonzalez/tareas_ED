#include <stdbool.h>

#define EDLIB_MAIN
#include "edlib.h"

#include "grafo_d.h"

peso_t calc_peso(Arista* arista) {return *arista;}
void print_vt(Vertice* vertice) {printf("%d", *vertice);}
void print_peso(peso_t peso) {printf("%d", peso);}

void agregar_vertice(Grafo_D* grafo) {
    print("Etiqueta del vertice");
    edlib_set_msj_error("La etiqueta debe ser un entero >= 0");
    int vt = validar_int_min(0);
    if(grafo_d_buscar_vertice(grafo, vt)) {
        println("El identificador ingresado ya existe");
        flush();
        return;
    }
    if(grafo_d_insertar_vertice(grafo, vt)) {
        println("El vertice fue agregado exitosamente");
    } else {
        println("Hubo un error al agregar el vertice");
    }
    flush();
    return;
}

void agregar_arista(Grafo_D* grafo) {
    print("Peso de la arista");
    edlib_set_msj_error("El peso debe ser un entero >= 0");
    int ar = validar_int_min(0);

    print("Etiqueta vertice de inicio");
    edlib_set_msj_error("La etiqueta debe ser un entero >= 0");
    int* v1 = grafo_d_buscar_vertice(grafo, validar_int_min(0));
    if(!v1) {
        println("El vertice solicitado no existe");
        flush();
        return;
    }

    print("Etiqueta vertice fin");
    edlib_set_msj_error("La etiqueta debe ser un entero >= 0");
    int* v2 = grafo_d_buscar_vertice(grafo, validar_int_min(0));
    if(!v2) {
        println("El vertice solicitado no exite");
        flush();
        return;
    }

    if(grafo_d_buscar_arista_entre_vert(grafo, v1, v2)) {
        printf("Ya existe una arista de %d a %d\n", *v1, *v2);
        flush();
        return;
    }

    if(grafo_d_insertar_arista(grafo, ar, v1, v2)) {
        println("La arista fue agregado exitosamente");
    } else {
        println("Hubo un error al agregar la arista");
    }
    flush();
    return;
}

void imprimir_matriz_ady(Grafo_D* grafo) {
    endl;
    if(grafo_d_isempty(grafo)) {
        println("El grafo se encuentra vacio");
        flush();
        return;
    }
    MatrizAdy_N* matriz = grafo_d_generar_matriz_ady(grafo);
    Nodo_V* vptr = grafo->lista_ady;
    print("  G  |");
    while(vptr!=NULL) {
        printf(" %3d |", vptr->vt);
        vptr=vptr->sig;
    }
    print("\n");
    vptr=grafo->lista_ady;
    for(int i=0; i<grafo->orden; ++i, vptr=vptr->sig) {
        printf(" %3d |", vptr->vt);
        for(int j=0; j<grafo->orden; ++j) {
            printf(" %3d |", GD_MATRIZ_INDEX(matriz, i, j));
        }
        print("\n");
    }
    free(matriz);
    flush();
    return;
}

void imprimir_matriz_pesos(Grafo_D* grafo) {
    endl;
    if(grafo_d_isempty(grafo)) {
        println("El grafo se encuentra vacio");
        flush();
        return;
    }
    MatrizAdy_P* matriz = grafo_d_generar_matriz_pesos(grafo);
    Nodo_V* vptr = grafo->lista_ady;
    print("  G  |");
    while(vptr!=NULL) {
        printf(" %3d |", vptr->vt);
        vptr=vptr->sig;
    }
    print("\n");
    vptr=grafo->lista_ady;
    for(int i=0; i<grafo->orden; ++i, vptr=vptr->sig) {
        printf(" %3d |", vptr->vt);
        for(int j=0; j<grafo->orden; ++j) {
            printf(" %3d |", GD_MATRIZ_INDEX(matriz, i, j));
        }
        print("\n");
    }
    free(matriz);
    flush();
    return;
}

int main(void) {
    Grafo_D* grafo = grafo_d_crear();
    if(!grafo) {
        println("Error al crear el grafo!",
                "Saliendo del programa...");
        flush();
        exit(EXIT_FAILURE);
    }
    grafo_d_set_calc_peso(grafo, calc_peso);
    while(true) {
        clear();
        println("Algorimos Basicos de Grafos");
        grafo_d_print_lista_ady_pond(grafo, print_vt, print_peso); endl;
        println("1-Agregar Vertice",
                "2-Agregar Arista",
                "3-Imprimir Matriz de Adyacencia",
                "4-Imprimir Matriz de Pesos",
                "5-Realizar Recorrido por Profundidad",
                "6-Realizar recorrido por Anchura",
                "7-Salir"); endl;
        switch(validar_int_en_rango(1,7)) {
        case 1:
            agregar_vertice(grafo);
            break;
        case 2:
            agregar_arista(grafo);
            break;
        case 3:
            imprimir_matriz_ady(grafo);
            break;
        case 4:
            imprimir_matriz_pesos(grafo);
            break;
        case 5:
            //recorrido_profundidad(grafo);
            break;
        case 6:
            //recorrido_anchura(grafo);
            break;
        case 7:
            grafo_d_destruir(grafo);
            clear();
            exit(EXIT_SUCCESS);
        }
    }
}