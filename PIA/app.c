#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <math.h>

#define L_NOMBRE 32

#define PROMPT_OPC  "? "
#define PROMPT_DATO "> "

typedef struct {
    char nombre[L_NOMBRE];
} Ciudad;

typedef struct {
    char nombre[L_NOMBRE];
    float longitud;
    float cuota;
} Carretera;

typedef struct {
    float peso;             //Ton
    float carga_max;        //Ton
    float combustible_max;  //L
    float rendimiento;      //Km/L
} ParamVehiculo;

typedef struct {
    float carga;            //Ton
    float combustible;      //L
    float presupuesto;      //PesosMx
} ParamViaje;

typedef struct {
    ParamVehiculo vehiculo;
    ParamViaje viaje;
} Contexto;

#define EDLIB_MAIN
#include "edlib.h"
#define STRUCT_VERTICE Ciudad
#define STRUCT_ARISTA Carretera
#define STRUCT_METADATA Contexto
#define DATO_PESO float
#define PESO_NO_ARISTA INFINITY
#include "grafo_d.h"
#define DATO_LISTA Ciudad*
#include "lista_d.h"

/*  Funcion de interpolacion logaritmica por distancia del origen
    valores cerca de 0 regresan valores cercanos a 1
    valores < R cerca de R regresan valores cercanos a 0
    *Rango: [0-L]
    *val elemento de R+ U {0}
    *R elemento de R+
*/
float logerp(float val, float R) {
    return log(R+1-val)/log(R+1);
}

/*  Define el rendimineto actual del vehiculo como una interpolacion entre el
    rendimineto base(m) y una fraccion del rendimiento base (RENDIMINTO_MIN*m) con
    respecto a una relacion logaritmica entre la carga actual y el peso de carga maximo
    del vehiculo establecido.
*/
#define RENDIMIENTO_MIN 0.2f
float calcular_rendimiento_actual(Contexto* contexto) {
    float rm = RENDIMIENTO_MIN*contexto->vehiculo.rendimiento;
    return  logerp(contexto->viaje.carga, contexto->vehiculo.carga_max)*
            (contexto->vehiculo.rendimiento-rm)+(rm);
}

bool comparar_ciudad_por_nombre(const Ciudad* c1, const Ciudad* c2) {
    if(strcmp(c1->nombre,c2->nombre)==0) 
        return true;
    return false;
}

float calcular_peso_por_costo(const Grafo_D* grafo, const Carretera* ar) {
    return 1;
}

float calcular_peso_por_tiempo(const Grafo_D* grafo, const Carretera* ar) {
    return 1;
}

float calcular_peso_por_distancia(const Grafo_D* grafo, const Carretera* ar) {
    if(ar->cuota <= grafo->contexto->viaje.presupuesto)
        return ar->longitud;
    return INFINITY;
}

Grafo_D* incializar_mapa(void) {
    Grafo_D* mapa = grafo_d_crear();
    if(!mapa) return NULL;
    
    Vertice* monterrey = grafo_d_insertar_vertice(mapa, (Ciudad){"Area Metropolitana"});
    Vertice* piedras_negras = grafo_d_insertar_vertice(mapa, (Ciudad){"Piedras Negras"});
    Vertice* sabinas = grafo_d_insertar_vertice(mapa, (Ciudad){"Sabinas"});
    Vertice* nuevo_laredo = grafo_d_insertar_vertice(mapa, (Ciudad){"Nuevo Laredo"});
    Vertice* monclova = grafo_d_insertar_vertice(mapa, (Ciudad){"Monclova"});
    Vertice* reynosa = grafo_d_insertar_vertice(mapa, (Ciudad){"Reynosa"});
    Vertice* matamoros = grafo_d_insertar_vertice(mapa, (Ciudad){"Matamoros"});
    Vertice* china = grafo_d_insertar_vertice(mapa, (Ciudad){"China"});
    Vertice* saltillo = grafo_d_insertar_vertice(mapa, (Ciudad){"Saltillo"});
    Vertice* montemorelos = grafo_d_insertar_vertice(mapa, (Ciudad){"Montemorelos"});
    Vertice* san_fernando = grafo_d_insertar_vertice(mapa, (Ciudad){"San Fernando"});
    Vertice* san_roberto = grafo_d_insertar_vertice(mapa, (Ciudad){"San Roberto"});
    Vertice* galeana = grafo_d_insertar_vertice(mapa, (Ciudad){"Galeana"});
    Vertice* linares = grafo_d_insertar_vertice(mapa, (Ciudad){"Linares"});
    Vertice* matehuala = grafo_d_insertar_vertice(mapa, (Ciudad){"Matehuala"});
    Vertice* dr_arrollo = grafo_d_insertar_vertice(mapa, (Ciudad){"Dr Arrollo"});
    Vertice* cd_victoria = grafo_d_insertar_vertice(mapa, (Ciudad){"Ciudad Victoria"});
    Vertice* soto_marina = grafo_d_insertar_vertice(mapa, (Ciudad){"Soto de la Marina"});
    Vertice* san_luis = grafo_d_insertar_vertice(mapa, (Ciudad){"San Luis Potosi"});
    Vertice* tampico = grafo_d_insertar_vertice(mapa, (Ciudad){"Tampico"});

    grafo_d_insertar_arcnj(mapa, (Carretera){"Mx-57", 126.0f, 0}, piedras_negras, sabinas);
    grafo_d_insertar_arcnj(mapa, (Carretera){"Mx-2", 176.0f, 0}, piedras_negras, nuevo_laredo);
    grafo_d_insertar_arcnj(mapa, (Carretera){"Mx-57", 115.0f, 0}, sabinas, monclova);
    grafo_d_insertar_arcnj(mapa, (Carretera){"Mx-2", 247.0f, 0}, nuevo_laredo, reynosa);
    grafo_d_insertar_arcnj(mapa, (Carretera){"Mx-57", 194.0f, 0}, monclova, saltillo);
    grafo_d_insertar_arcnj(mapa, (Carretera){"Mx-53", 196.0f, 0}, monclova, monterrey);
    grafo_d_insertar_arcnj(mapa, (Carretera){"Mx-85", 220.0f, 0}, nuevo_laredo, monterrey);
    grafo_d_insertar_arcnj(mapa, (Carretera){"Mx-40", 110.0f, 0}, reynosa, china);
    grafo_d_insertar_arcnj(mapa, (Carretera){"Mx-2", 91.4f, 0}, reynosa, matamoros);
    grafo_d_insertar_arcnj(mapa, (Carretera){"Mx-40", 85.7f, 0}, saltillo, monterrey);
    grafo_d_insertar_arcnj(mapa, (Carretera){"Mx-40", 122.0f, 0}, monterrey, china);
    grafo_d_insertar_arcnj(mapa, (Carretera){"Mx-57", 121.0f, 0}, saltillo, san_roberto);
    grafo_d_insertar_arcnj(mapa, (Carretera){"Mx-85", 80.8f, 0}, monterrey, montemorelos);
    grafo_d_insertar_arcnj(mapa, (Carretera){"Mx-35", 94.6f, 0}, china, montemorelos);
    grafo_d_insertar_arcnj(mapa, (Carretera){"Mx-97", 151.0f, 0}, reynosa, san_fernando);
    grafo_d_insertar_arcnj(mapa, (Carretera){"Mx-101", 140.0f, 0}, matamoros, san_fernando);
    grafo_d_insertar_arcnj(mapa, (Carretera){"Mx-85", 51.4f, 0}, montemorelos, linares);
    grafo_d_insertar_arcnj(mapa, (Carretera){"Mx-58", 46.7f, 0}, san_roberto, galeana);
    grafo_d_insertar_arcnj(mapa, (Carretera){"Mx-58", 73.1f, 0}, galeana, linares);
    grafo_d_insertar_arcnj(mapa, (Carretera){"Mx-58", 104.0f, 0}, san_roberto, linares);
    grafo_d_insertar_arcnj(mapa, (Carretera){"Mx-101", 179.0f, 0}, san_fernando, cd_victoria);
    grafo_d_insertar_arcnj(mapa, (Carretera){"Mx-57", 134.0f, 0}, san_roberto, matehuala);
    grafo_d_insertar_arcnj(mapa, (Carretera){"Mx-29", 50.5f, 0}, matehuala, dr_arrollo);
    grafo_d_insertar_arcnj(mapa, (Carretera){"Mx-85", 155.0f, 0}, linares, cd_victoria);
    grafo_d_insertar_arcnj(mapa, (Carretera){"Mx-57", 192.0f, 0}, matehuala, san_luis);
    grafo_d_insertar_arcnj(mapa, (Carretera){"Mx-101", 338.0f, 0}, san_luis, cd_victoria);
    grafo_d_insertar_arcnj(mapa, (Carretera){"Mx-70/75", 111.0f, 0}, cd_victoria, soto_marina);
    grafo_d_insertar_arcnj(mapa, (Carretera){"Mx-83", 237.0f, 0}, cd_victoria, tampico);
    grafo_d_insertar_arcnj(mapa, (Carretera){"Mx-180/80", 275.0f, 0}, soto_marina, tampico);

    #define N_VERTICES_INICIALES 20
    #define N_ARISTAS_INICIALES 58
    if(mapa->orden!=N_VERTICES_INICIALES || mapa->tamano!=N_ARISTAS_INICIALES) {
        grafo_d_destruir(mapa);
        return NULL;
    }
    #undef N_VERTICES_INICIALES
    #undef N_ARISTAS_INICIALES
    return mapa;
}

void mostrar_ciudades(const Grafo_D* mapa) {
    clear();
    println("Lista de ciudades disponibes:");
    Vect_V* ciudades = grafo_d_get_vertices(mapa);
    if(!ciudades) {
        println("Se precento un error al cargar las ciudades, intentelo denuevo");
        flush();
        return;
    }
    for(int i=0; i<ciudades->tamano; ++i)
        printf("%2d. %s\n", i+1, ciudades->vertices[i]->nombre);
    free(ciudades);
    flush();
    return;
}

void print_param_vehiculo(const ParamVehiculo* vehiculo) {
    printf("Peso del Vehiculo(Ton): %.1f\n", vehiculo->peso);
    printf("Capacidad de Carga(Ton): %.1f\n", vehiculo->carga_max);
    printf("Capacidad de Combustible(L): %.1f\n", vehiculo->combustible_max);
    printf("Rendimiento de Combustible(Km/L): %.2f\n", vehiculo->rendimiento);
}

void print_param_viaje(const ParamViaje* viaje) {
    printf("Carga del Vehiculo(Ton): %.1f\n", viaje->carga);
    printf("Combustible Inicial(L): %.1f\n", viaje->combustible);
    printf("Presupuesto para el Viaje(Mx): %.2f\n", viaje->presupuesto);
}

void configurar_vehiculo(ParamVehiculo* vehiculo) {
    while(true) {
        clear();
        println("Parametros del Vehiculo:");
        print_param_vehiculo(vehiculo); endl;
        println("Seleccione el parametro que desea ajustar",
                "1. Peso del Vehiculo",
                "2. Capacidad de Carga",
                "3. Capacidad de Combustible",
                "4. Rendimiento",
                "5. Salir");
        edlib_set_prompt(PROMPT_OPC);
        int opc = validar_int_en_rango(1, 5);

        edlib_set_prompt(PROMPT_DATO);
        switch(opc) {
        case 1:
            edlib_set_msj_error("El peso debe estar entre 1 y 12 toneladas");
            vehiculo->peso = validar_float_en_rango(1, 12);
            break;
        case 2:
            edlib_set_msj_error("La capacidad de carga debe estar entre 5 y 100 toneladas");
            vehiculo->carga_max = validar_float_en_rango(0, 100);
            break;
        case 3:
            edlib_set_msj_error("La capacidad de combustible debe estar entre 50 y 2000 litros");
            vehiculo->combustible_max = validar_float_en_rango(50, 2000);
            break;
        case 4:
            edlib_set_msj_error("El redimineto del vehiculo debe estar entre 0.5 y 6 Km/L");
            vehiculo->rendimiento = validar_float_en_rango(0.5, 6);
            break;
        case 5:
            return;
        }
    }
}

#define N_POND 3
typedef float (*Ponderacion)(const Grafo_D*, const Carretera*);
void seleccionar_prioridad(Grafo_D* mapa) {
    static Ponderacion ponderaciones[N_POND] = {
        calcular_peso_por_costo,
        calcular_peso_por_tiempo,
        calcular_peso_por_distancia
    };
    static const char* estatus[N_POND+1] = {
        "Costo", "Tiempo" , "Distancia", "ERROR"};

    int i;
    while(true) {
        clear();
        print("Prioridad Actual: "); 
        for(i=0; i<N_POND; ++i) {
            if(mapa->calc_peso==ponderaciones[i])
                break;
        }
        println(estatus[i]);
        println("Seleccione a que desea dar prioridad",
                "1. Minimizar Costos de Entrega",
                "2. Minimizar Tiempo de Entrega",
                "3. Minimizar Distancia de Reparto",
                "4. Regresar");
        edlib_set_prompt(PROMPT_OPC);
        i = validar_int_en_rango(1, N_POND+1)-1;
        if(i==N_POND) return;
        grafo_d_set_calc_peso(mapa, ponderaciones[i]);
    }
}

#define LIMITE_PESO 80.0f
ParamViaje leer_parametros_viaje(const ParamVehiculo* vehiculo) {
    ParamViaje viaje;
    bool usuario_esta_seguro = false;
    while(!usuario_esta_seguro) {
        println("Introduzca el peso de carga del viaje en toneladas");
        edlib_set_prompt(PROMPT_DATO);
        edlib_set_msj_error("El peso de carga debe de ser menor a la\n"
                            "capacidad maxima de carga del vehiculo");
        viaje.carga = validar_float_en_rango(0, vehiculo->carga_max);
        if(viaje.carga+vehiculo->peso <= LIMITE_PESO)
            usuario_esta_seguro = true;
        else {
            printf("Se recomienda no sobrepasar el limite de %.1f\n", LIMITE_PESO);
            println("Esta seguro que desea continuar?(1-Si|2-No)");
            edlib_set_prompt(PROMPT_OPC);
            usuario_esta_seguro = (bool)(validar_int_en_rango(1,2)-1);
        }
    }
    println("Introduzca la cantidad de combustible para el viaje en litros");
    edlib_set_prompt(PROMPT_DATO);
    edlib_set_msj_error("La cantidad de combustible debe ser menor a la capacidad\n"
                        "maxima de combustible del vehiculo y mayor a 10 litros");
    viaje.combustible = validar_float_en_rango(10, vehiculo->combustible_max);
    println("Introduzca el presupuesto de peaje para el viaje en pesos");
    edlib_set_msj_error("El presupuesto no puede ser un numero negativo");
    viaje.presupuesto = validar_float_min(0);
    return viaje;
}

void print_viaje(const Camino_D* viaje) {
    
    printf("Viaje de %s a %s:\n",
        camino_d_get_inicio(viaje)->nombre,
        camino_d_get_fin(viaje)->nombre
    );
    for(int i=0; i<viaje->saltos; ++i) {
        printf("Tomar %s hacia %s\n",
            viaje->ars[i]->nombre,
            viaje->vts[i+1]->nombre
        );
    }
    flush();
    return;
}

Lista_D* leer_ciudades_destino(const Grafo_D* mapa) {
    Lista_D* ciudades = lista_d_crear();
    if(!ciudades) return NULL;
    
    Ciudad buffer = {""};
    Ciudad* ciudad;
    println("Introduzca el nombre de la ciudad donde iniciara el viaje");
    edlib_set_prompt(PROMPT_DATO);
    leer_string(buffer.nombre, L_NOMBRE);
    while(!(ciudad = grafo_d_buscar_vertice(mapa, buffer))) {
        println("No se encontro ninguna ciudad con ese nombre");
        leer_string(buffer.nombre, L_NOMBRE);
    }
    lista_d_insertar_fin(ciudades, ciudad);
    endl;
    println("Introduzca los nombres de las ciudades a visitar",
            "en el orden en el que seran visitadas. Introduzca",
            "una linea vacia para finalizar la captura");
    while(leer_string(buffer.nombre, L_NOMBRE)) {
        if((ciudad = grafo_d_buscar_vertice(mapa,buffer)))
            lista_d_insertar_fin(ciudades, ciudad);
        else
            println("No se encontro ninguna ciudad con ese nombre");
    }
    return ciudades;
}

void print_camino_debug(Camino_D* camino) {
    if(!camino) {
        printf("Hubo un error con la alloc en el heap\n");
        return;
    }
    printf("vts: %p\n", camino->vts);
    printf("ars: %p\n", camino->ars);
    printf("saltos: %u\n", camino->saltos);
    printf("longitud: %f\n", camino->longitud);
}

Camino_D* viaje_secuencial(const Grafo_D* mapa) {
    clear();
    println("Parametros del Vehiculo Actual:");
    print_param_vehiculo(&mapa->contexto->vehiculo);
    println("Desea continuar con esta configuracion?(1-Si|2-No)");
    edlib_set_prompt(PROMPT_OPC);
    if(validar_int_en_rango(1,2)==2) return NULL;
    mapa->contexto->viaje = leer_parametros_viaje(&mapa->contexto->vehiculo);

    Lista_D* ciudades = leer_ciudades_destino(mapa);
    Camino_D* viaje = camino_d_crear_trivial(lista_d_pop_inicio(ciudades));
    while(!lista_d_isempty(ciudades)) {
        Camino_D* segmento = grafo_d_dijkstra(mapa,
            camino_d_get_fin(viaje),
            lista_d_get_inicio(ciudades)
        );
        for(int i=0; i<segmento->saltos; ++i) {
            if(mapa->contexto->viaje.presupuesto >= segmento->ars[i]->cuota) {
                mapa->contexto->viaje.presupuesto -= segmento->ars[i]->cuota;
            } else {
                segmento = camino_d_frecortar(segmento, i);
                break;
            }
        }
        viaje = camino_d_fconcatenar(viaje, segmento);
        if(camino_d_get_fin(viaje)==lista_d_get_inicio(ciudades))
            lista_d_eliminar_inicio(ciudades);
    }
    lista_d_destruir(ciudades);
    return viaje;
}

Camino_D* viaje_generico(const Grafo_D* mapa) {
    return NULL;
}