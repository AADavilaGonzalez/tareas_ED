#include <stdbool.h>

#define EDLIB_MAIN
#include "edlib.h"
#include "grafo_d.h"
#include "lista_s.h"

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
    if(grafo_d_isempty(grafo)) {
        println("El grafo se encuentra vacio");
        flush();
        return;
    }
    Vect_V* vts = grafo_d_get_vertices(grafo);
    MatrizAdy_N* matriz = grafo_d_generar_matriz_ady(grafo);
    print("   G |");
    for(int i=0; i<grafo->orden; ++i) {
        printf(" %3d |", *(vts->vertices[i]));
    }
    endl;
    for(int i=0; i<grafo->orden; ++i) {
        printf(" %3d |", *(vts->vertices[i]));
        for(int j=0; j<grafo->orden; ++j) {
            printf(" %3lu |", GD_MATRIZ_INDEX(matriz, i, j));
        }
        endl;
    }
    free(vts);
    free(matriz);
    flush();
    return;
}

void imprimir_matriz_pesos(Grafo_D* grafo) {
    if(grafo_d_isempty(grafo)) {
        println("El grafo se encuentra vacio");
        flush();
        return;
    }
    Vect_V* vts = grafo_d_get_vertices(grafo);
    MatrizAdy_P* matriz = grafo_d_generar_matriz_pesos(grafo);
    print("   G |");
    for(int i=0; i<grafo->orden; ++i) {
        printf(" %3d |", *(vts->vertices[i]));
    }
    endl;
    for(int i=0; i<grafo->orden; ++i) {
        printf(" %3d |", *(vts->vertices[i]));
        for(int j=0; j<grafo->orden; ++j) {
            if(GD_MATRIZ_INDEX(matriz, i, j)!=PESO_NO_ARISTA)
                printf(" %3d |", GD_MATRIZ_INDEX(matriz, i, j));
            else if(i==j) print("  0  |");
            else print(" INF |");
        }
        endl;
    }
    free(vts);
    free(matriz);
    flush();
    return;
}

Vertice* seleccionar_vertice(Grafo_D* grafo) {
    println("Ingrese el vertice que va a ser seleccionado como raiz");
    edlib_set_msj_error("La etiqueta debe ser un enter >= 0");
    Vertice* vert = grafo_d_buscar_vertice(grafo, validar_int_min(0));
    if(!vert) {
        println("El vertice solicitado no es parte del grafo");
        flush();
        return NULL;
    }
    return vert;
}

#define Pila Lista_S
#define pila_crear() (lista_s_crear())
#define pila_get(lista) (lista->cabeza->dato)
#define pila_isempty(lista) (lista_s_isempty(lista))
#define pila_insertar(lista, valor) (lista_s_insertar_inicio(lista, valor))
#define pila_eliminar(lista) (lista_s_eliminar_inicio(lista))
#define pila_destruir(lista) (lista_s_destruir(lista))

#define Cola Lista_S
#define cola_crear() (lista_s_crear())
#define cola_get(lista) (lista->cabeza->dato)
#define cola_isempty(lista) (lista_s_isempty(lista))
#define cola_encolar(lista, valor) (lista_s_insertar_fin(lista,valor))
#define cola_desencolar(lista) (lista_s_eliminar_inicio(lista))
#define cola_destruir(lista) (lista_s_destruir(lista))

int get_indice_vertice(const Vect_V* vect, Vertice* vt) {
    for(int i=0; i<vect->tamano; ++i) {
        if(vect->vertices[i]==vt) return i;
    }
    return -1;
}

void recorrido_profundidad(Grafo_D* grafo, Vertice* raiz) {
    Vect_V* vts = grafo_d_get_vertices(grafo);
    MatrizAdy_N* matriz = grafo_d_generar_matriz_ady(grafo);
    Lista_S* visitados = lista_s_crear();
    Pila* pila = pila_crear();
    pila_insertar(pila, get_indice_vertice(vts, raiz));
    print("Recorrido");
    while(!pila_isempty(pila)) {
        int i = pila_get(pila);
        pila_eliminar(pila);
        if(!lista_s_contiene(visitados, i)) {
            printf(" -> %d", *(vts->vertices[i]));
            lista_s_insertar_inicio(visitados, i);
            for(int j=grafo->orden-1; j>=0; --j) {
                if(GD_MATRIZ_INDEX(matriz, i, j)!=0) {
                    pila_insertar(pila, j);
                }
            } 
        }
    }
    free(vts);
    free(matriz);
    lista_s_destruir(visitados);
    pila_destruir(pila);
    flush();
    return;
}

void recorrido_anchura(Grafo_D* grafo, Vertice* raiz) {
    Vect_V* vts = grafo_d_get_vertices(grafo);
    MatrizAdy_N* matriz = grafo_d_generar_matriz_ady(grafo);
    Lista_S* visitados = lista_s_crear();
    Cola* cola = cola_crear();
    cola_encolar(cola, get_indice_vertice(vts, raiz));
    print("Recorrido");
    while(!cola_isempty(cola)) {
        int i = cola_get(cola);
        cola_desencolar(cola);
        if(!lista_s_contiene(visitados, i)) {
            printf(" -> %d", *(vts->vertices[i]));
            lista_s_insertar_inicio(visitados, i);
            for(int j=0; j<grafo->orden; ++j) {
                if(GD_MATRIZ_INDEX(matriz, i, j)!=0) {
                    cola_encolar(cola, j);
                }
            }   
        }
    }
    free(vts);
    free(matriz);
    lista_s_destruir(visitados);
    cola_destruir(cola);
    flush();
    return;
}

int main(void) {
    Grafo_D* grafo = grafo_d_crear();
    Vertice* vert;
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
            endl;
            imprimir_matriz_ady(grafo);
            break;
        case 4:
            endl;
            imprimir_matriz_pesos(grafo);
            break;
        case 5:
            vert = seleccionar_vertice(grafo);
            if(vert) recorrido_profundidad(grafo, vert);
            break;
        case 6:
            vert = seleccionar_vertice(grafo);
            if(vert) recorrido_anchura(grafo, vert);
            break;
        case 7:
            grafo_d_destruir(grafo);
            clear();
            exit(EXIT_SUCCESS);
        }
    }
}