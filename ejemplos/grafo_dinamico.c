#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <stddef.h>
#include <math.h>

#define EDLIB_MAIN
#include "edlib.h"

#define L_NOMBRE 32

typedef struct {
    char nombre[L_NOMBRE];
    size_t poblacion;
} Ciudad;

typedef struct {
    char nombre[L_NOMBRE];
    double longitud;
} Carretera;

#define STRUCT_VERTICE Ciudad
#define STRUCT_ARISTA Carretera
#define DATO_PESO double
#define PESO_NO_ARISTA HUGE_VAL
#include "grafo_d.h"

bool comparar_ciudades(const Ciudad*, const Ciudad*);
bool comparar_carreteras(const Carretera*, const Carretera*);
double calcular_distancia(const Grafo_D*, const Carretera*);

void imprimir_mapa(const Grafo_D*);
void agregar_ciudad(Grafo_D*);
void agregar_carretera(Grafo_D*);
void imprimir_matriz_ady(const Grafo_D*);
void realizar_dijktra(const Grafo_D*);
Grafo_D* cargar_ejemplo_estatico(void);

int main(void) {
    Grafo_D* tmp;
    Grafo_D* mapa = grafo_d_crear();
    if(!mapa) {
        perror("No se pudo reservar memoria suficiente");
        return EXIT_FAILURE;
    }
    grafo_d_set_cmp_vt(mapa, comparar_ciudades);
    grafo_d_set_cmp_ar(mapa, comparar_carreteras);
    grafo_d_set_calc_peso(mapa, calcular_distancia);
    while(true) {
        clear();
        println("Representacion Interactiva de un Mapa como un Grafo",
                "1. Imprimir",
                "2. Agregar Ciudad",
                "3. Agregar Carretera",
                "4. Imprimir Matriz de Adyacencia",
                "5. Realizar Algritmo de Dijktra",
                "6. Cargar Ejemplo Estatico",
                "7. Salir");
        switch(validar_int_en_rango(1,7)) {
        case 1:
            imprimir_mapa(mapa);
            break;
        case 2:
            agregar_ciudad(mapa);
            break;
        case 3:
            agregar_carretera(mapa);
            break;
        case 4:
            imprimir_matriz_ady(mapa);
            break;
        case 5:
            realizar_dijktra(mapa);
            break;
        case 6:
            tmp = cargar_ejemplo_estatico();
            if(tmp!=NULL) {
                grafo_d_destruir(mapa);
                mapa = tmp;
                println("Ejemplo cargado exitosamente");
            }
            else
                println("No se pudo cargar el ejemplo");
            flush();
            break;
        case 7:
            clear();
            return EXIT_SUCCESS;
        }
    }
}

bool comparar_ciudades(const Ciudad* c1, const Ciudad* c2) {
    if(strcmp(c1->nombre, c2->nombre)==0)
        return true;
    return false;
}

bool comparar_carreteras(const Carretera* c1, const Carretera* c2) {
    if(strcmp(c1->nombre, c2->nombre)==0)
        return true;
    return false;
}

double calcular_distancia(const Grafo_D* mapa, const Carretera* carretera) {
    return carretera->longitud;
}

void print_ciudad(Ciudad* ciudad, FILE* salida) {
    fprintf(salida,"%s", ciudad->nombre);
}

void print_longitud(peso_t peso, FILE* salida) {
    fprintf(salida, "%.2f", peso);
}

void imprimir_mapa(const Grafo_D* mapa) {
    static const char* nom_arch = "mapa.gv";
    clear();
    if(grafo_d_isempty(mapa)) {
        println("El mapa se encuentra vacio");
        flush();
        return;
    }
    println("Representacion como lista de Adyecencia:");
    grafo_d_print_lista_ady_pond(mapa, print_ciudad, print_longitud);
    endl;

    FILE* archivo = fopen(nom_arch, "w");
    if(!archivo) {
        println("Hubo un error al intentar salvar la representacion",
                "grafica del mapa en un archivo");
        flush();
        return;
    }
    grafo_d_generar_gv(mapa, print_ciudad, archivo);
    fclose(archivo);
    printf( "Se ha creado un archivo que contiene la representacion\n"
            "grafica del mapa en formato DOT en con el nombre %s\n"
            "en el directorio de trabajo actual\n", nom_arch);
    flush();
}

void agregar_ciudad(Grafo_D* mapa) {
    clear();
    Ciudad buffer;
    println("Introduzca el nombre de la ciudad a insertar");
    leer_string(buffer.nombre, L_NOMBRE);
    if(grafo_d_buscar_vertice(mapa, buffer)) {
        println("Ya existe una ciudad con ese nombre");
        flush();
        return;
    }
    println("Introduzca la poblacion de la ciudad a insertar");
    buffer.poblacion = (size_t)validar_uint();
    if(grafo_d_insertar_vertice(mapa, buffer))
        println("La ciudad se incorporo al mapa exitosamente");
    else
        println("Hubo un error al incorporar la ciudad al mapa");
    flush();
}

Ciudad* validar_ciudad_en_mapa(const Grafo_D* mapa) {
    Ciudad* ciudad;
    Ciudad buffer;
    leer_string(buffer.nombre, L_NOMBRE);
    ciudad = grafo_d_buscar_vertice(mapa, buffer);
    while(!ciudad) {
        println("La ciudad solicitada no existe");
        leer_string(buffer.nombre, L_NOMBRE);
        ciudad = grafo_d_buscar_vertice(mapa, buffer);
    }
    return ciudad;
}

void agregar_carretera(Grafo_D* mapa) {
    clear();
    Ciudad* c1;
    Ciudad* c2;
    Carretera carretera;
    println("Introduzca el nombre de la primera ciudad a conectar");
    c1 = validar_ciudad_en_mapa(mapa);
    println("Introduzca el nombre de la segunda ciudad a conectar");
    c2 = validar_ciudad_en_mapa(mapa);

    println("Introduzca el nombre de la carretera");
    leer_string(carretera.nombre, L_NOMBRE);
    if(grafo_d_buscar_arista_estricto(mapa, carretera, c1, c2)) {
        println("Ya existe una carretera con ese nombre",
                "entre esas dos ciudades");
        flush();
        return;
    }
    println("Introduzca la longitud de la carretera");
    edlib_set_msj_error("La longitud debe ser mayor a cero");
    carretera.longitud = validar_float_min(0.000001f);
    if(grafo_d_insertar_arcnj(mapa, carretera, c1, c2))
        println("La carretera se incorporo al mapa exitosamente");
    else
        println("Hubo un error al incorporar la carretera al mapa");
    flush();
}

void imprimir_matriz_ady(const Grafo_D* mapa) {
    clear();
    Vect_V* vect = grafo_d_get_vertices(mapa);
    MatrizAdy_P* matriz = grafo_d_generar_matriz_pesos(mapa);
    double* ptr=matriz->datos;
    printf("     | ");
    for(int i=0; i<matriz->orden; ++i)
        printf(" %-4.4s ", vect->vertices[i]->nombre);
    printf("|\n");
    for(int i=0; i<matriz->orden; ++i) {
        printf("%4.4s | ", vect->vertices[i]->nombre);
        for(int j=0; j<matriz->orden; ++j) {
            if(*ptr!=PESO_NO_ARISTA)
                printf("%5.1f ", *ptr);
            else
                printf(" INF  ");
            ++ptr;
        }
        printf("|\n");
    }
    free(matriz);
    free(vect);
    flush();
}

void print_camino(const Camino_D* camino) {
    if(camino_d_es_nulo(camino)) {
        println("No se encontro ningun camino entre las ciudades");
        return;
    }
    printf("Ciudad de Inicio: %s\n", camino->vts[0]->nombre);
    for(int i=0; i<camino->saltos; ++i) {
        printf("Tomar %s hacia %s\n",
            camino->ars[i]->nombre,
            camino->vts[i+1]->nombre
        );
    }
}

void realizar_dijktra(const Grafo_D* mapa) {
    clear();
    Ciudad* inicio;
    Ciudad* fin;
    println("Introduzca el nombre de la ciudad de inicio");
    inicio = validar_ciudad_en_mapa(mapa);
    println("Introduzca el nombre de la ciudad fin");
    fin = validar_ciudad_en_mapa(mapa);
    Camino_D* camino = grafo_d_dijkstra_unico(mapa, inicio, fin);
    endl;
    print_camino(camino);
    free(camino);
    flush();
}

Grafo_D* cargar_ejemplo_estatico(void) {
    Grafo_D* mapa = grafo_d_crear();
    if(!mapa) return NULL;

    Ciudad* monterrey = grafo_d_insertar_vertice(mapa, (Ciudad){"Monterrey", 5322177});
    Ciudad* saltillo = grafo_d_insertar_vertice(mapa, (Ciudad){"Saltillo", 879958});
    Ciudad* montemorelos = grafo_d_insertar_vertice(mapa, (Ciudad){"Montemorelos", 67428});
    Ciudad* linares = grafo_d_insertar_vertice(mapa, (Ciudad){"Linares", 84666});
    Ciudad* monclova = grafo_d_insertar_vertice(mapa, (Ciudad){"Monclova", 237951});
    Ciudad* nuevo_laredo = grafo_d_insertar_vertice(mapa, (Ciudad){"Nuevo Laredo", 425058});
    Ciudad* reynosa = grafo_d_insertar_vertice(mapa, (Ciudad){"Reynosa", 967627});
    Ciudad* cd_victoria = grafo_d_insertar_vertice(mapa, (Ciudad){"Ciudad Victoria", 967627});
    Ciudad* matehuala = grafo_d_insertar_vertice(mapa, (Ciudad){"Matehuala", 102199});
    Ciudad* san_luis = grafo_d_insertar_vertice(mapa, (Ciudad){"San Luis Potosi", 911908});

    grafo_d_insertar_arcnj(mapa, (Carretera){"Mx-85", 219.0f}, monterrey, nuevo_laredo);
    grafo_d_insertar_arcnj(mapa, (Carretera){"Mx-53", 194.0f}, monterrey, monclova);
    grafo_d_insertar_arcnj(mapa, (Carretera){"Fd-40", 85.7f}, monterrey, saltillo);
    grafo_d_insertar_arcnj(mapa, (Carretera){"Mx-85", 81.8f}, monterrey, montemorelos);
    grafo_d_insertar_arcnj(mapa, (Carretera){"Fd-40", 220.0f}, monterrey, reynosa);
    grafo_d_insertar_arcnj(mapa, (Carretera){"Mx-57", 194.0f}, saltillo, monclova);
    grafo_d_insertar_arcnj(mapa, (Carretera){"COAH-30", 246.0f}, monclova, nuevo_laredo);
    grafo_d_insertar_arcnj(mapa, (Carretera){"Mx-2", 255.0f}, nuevo_laredo, reynosa);
    grafo_d_insertar_arcnj(mapa, (Carretera){"Mx-97", 348.0f}, reynosa, cd_victoria);
    grafo_d_insertar_arcnj(mapa, (Carretera){"Mx-101", 330.0f}, cd_victoria, san_luis);
    grafo_d_insertar_arcnj(mapa, (Carretera){"Mx-57", 192.0f}, san_luis, matehuala);
    grafo_d_insertar_arcnj(mapa, (Carretera){"Mx-57", 258.0f}, matehuala, saltillo);
    grafo_d_insertar_arcnj(mapa, (Carretera){"Mx-85", 154.0}, cd_victoria, linares);
    grafo_d_insertar_arcnj(mapa, (Carretera){"Mx-85", 51.4f}, linares, montemorelos);

    grafo_d_set_cmp_vt(mapa, comparar_ciudades);
    grafo_d_set_cmp_ar(mapa, comparar_carreteras);
    grafo_d_set_calc_peso(mapa, calcular_distancia);

    if(mapa->orden!=10 || mapa->tamano!=28) {
        grafo_d_destruir(mapa);
        return NULL;
    }
    return mapa;
}