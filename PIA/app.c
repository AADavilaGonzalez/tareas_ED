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
    float peso_entrega;     //Ton
} Ciudad;

typedef struct {
    char nombre[L_NOMBRE];
    float longitud;         //Km
    float cuota;            //Mx
    float velocidad_prom;   //Km/h
} Carretera;

typedef struct {
    float costo_combustible;   
    float reabastecimiento; 
} ParamConfig;

typedef struct {
    float peso;             //Ton
    float carga_max;        //Ton
    float combustible_max;  //L
    float rendimiento;      //Km/L
    float velocidad_min;    //Km/h
    float velocidad_max;    //Km/h
} ParamVehiculo;

typedef struct {
    float carga;            //Ton
    float combustible;      //L
    float presupuesto;      //Mx
} ParamViaje;

typedef struct {
    ParamConfig config;
    ParamVehiculo vehiculo;
    ParamViaje viaje;
} Contexto;

#define EDLIB_MAIN
#include "edlib.h"
#define STRUCT_VERTICE Ciudad
#define STRUCT_ARISTA Carretera
#define GRAFO_D_METADATA Contexto*
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
static inline float dlogerp(float val, float R) {
    return log(R+1-val)/log(R+1);
}

/*  Define el rendimineto actual del vehiculo como una interpolacion entre el
    rendimineto base(m) y una fraccion del rendimiento base (RENDIMINTO_MIN*m) con
    respecto a una relacion logaritmica entre la carga actual y el peso de carga maximo
    del vehiculo establecido.
*/
#define RENDIMIENTO_MIN 0.2f
static inline float calcular_rendimiento_actual(Contexto* contexto) {
    return  dlogerp(contexto->viaje.carga, contexto->vehiculo.carga_max)*
            (contexto->vehiculo.rendimiento-RENDIMIENTO_MIN*contexto->vehiculo.rendimiento)+
            (RENDIMIENTO_MIN*contexto->vehiculo.rendimiento);
}

/*  Define la velocidad maxima actual del vehiculo como una interpolacion lineal entre
    los valores de velocidad maxima y velocidad minima con respecto a la proporcion
    entre carga actual y carga maxima
*/
static inline float calcular_vel_max_actual(Carretera* carretera, Contexto* contexto) {
    float velocidad_vehiculo = contexto->vehiculo.velocidad_min+
        (1-contexto->viaje.carga/contexto->vehiculo.carga_max)*
        (contexto->vehiculo.velocidad_max-contexto->vehiculo.velocidad_min);
    return velocidad_vehiculo < carretera->velocidad_prom ? velocidad_vehiculo : carretera->velocidad_prom;
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

    grafo_d_insertar_arcnj(mapa, (Carretera){"Mx-57", 126.0f, 0, 80.0f}, piedras_negras, sabinas);
    grafo_d_insertar_arcnj(mapa, (Carretera){"Mx-2", 176.0f, 0, 80.0f}, piedras_negras, nuevo_laredo);
    grafo_d_insertar_arcnj(mapa, (Carretera){"Mx-57", 115.0f, 0, 80.0f}, sabinas, monclova);
    grafo_d_insertar_arcnj(mapa, (Carretera){"Mx-2", 247.0f, 0, 80.0f}, nuevo_laredo, reynosa);
    grafo_d_insertar_arcnj(mapa, (Carretera){"Mx-57", 194.0f, 0, 80.0f}, monclova, saltillo);
    grafo_d_insertar_arcnj(mapa, (Carretera){"Mx-53", 196.0f, 0, 80.0f}, monclova, monterrey);
    grafo_d_insertar_arcnj(mapa, (Carretera){"Mx-85", 220.0f, 0, 80.0f}, nuevo_laredo, monterrey);
    grafo_d_insertar_arcnj(mapa, (Carretera){"Mx-40", 110.0f, 0, 80.0f}, reynosa, china);
    grafo_d_insertar_arcnj(mapa, (Carretera){"Mx-2", 91.4f, 0, 80.0f}, reynosa, matamoros);
    grafo_d_insertar_arcnj(mapa, (Carretera){"Mx-40", 85.7f, 0, 80.0f}, saltillo, monterrey);
    grafo_d_insertar_arcnj(mapa, (Carretera){"Mx-40", 122.0f, 0, 80.0f}, monterrey, china);
    grafo_d_insertar_arcnj(mapa, (Carretera){"Mx-57", 121.0f, 0, 80.0f}, saltillo, san_roberto);
    grafo_d_insertar_arcnj(mapa, (Carretera){"Mx-85", 80.8f, 0, 80.0f}, monterrey, montemorelos);
    grafo_d_insertar_arcnj(mapa, (Carretera){"Mx-35", 94.6f, 0, 80.0f}, china, montemorelos);
    grafo_d_insertar_arcnj(mapa, (Carretera){"Mx-97", 151.0f, 0, 80.0f}, reynosa, san_fernando);
    grafo_d_insertar_arcnj(mapa, (Carretera){"Mx-101", 140.0f, 0, 80.0f}, matamoros, san_fernando);
    grafo_d_insertar_arcnj(mapa, (Carretera){"Mx-85", 51.4f, 0, 80.0f}, montemorelos, linares);
    grafo_d_insertar_arcnj(mapa, (Carretera){"Mx-58", 46.7f, 0, 80.0f}, san_roberto, galeana);
    grafo_d_insertar_arcnj(mapa, (Carretera){"Mx-58", 73.1f, 0, 80.0f}, galeana, linares);
    grafo_d_insertar_arcnj(mapa, (Carretera){"Mx-58", 104.0f, 0, 80.0f}, san_roberto, linares);
    grafo_d_insertar_arcnj(mapa, (Carretera){"Mx-101", 179.0f, 0, 80.0f}, san_fernando, cd_victoria);
    grafo_d_insertar_arcnj(mapa, (Carretera){"Mx-57", 134.0f, 0, 80.0f}, san_roberto, matehuala);
    grafo_d_insertar_arcnj(mapa, (Carretera){"Mx-29", 50.5f, 0, 80.0f}, matehuala, dr_arrollo);
    grafo_d_insertar_arcnj(mapa, (Carretera){"Mx-85", 155.0f, 0, 80.0f}, linares, cd_victoria);
    grafo_d_insertar_arcnj(mapa, (Carretera){"Mx-57", 192.0f, 0, 80.0f}, matehuala, san_luis);
    grafo_d_insertar_arcnj(mapa, (Carretera){"Mx-101", 338.0f, 0, 80.0f}, san_luis, cd_victoria);
    grafo_d_insertar_arcnj(mapa, (Carretera){"Mx-70/75", 111.0f, 0, 80.0f}, cd_victoria, soto_marina);
    grafo_d_insertar_arcnj(mapa, (Carretera){"Mx-83", 237.0f, 0, 80.0f}, cd_victoria, tampico);
    grafo_d_insertar_arcnj(mapa, (Carretera){"Mx-180/80", 275.0f, 0, 80.0f}, soto_marina, tampico);

    #define N_VERTICES_INICIALES 20
    #define N_ARISTAS_INICIALES 58
    if(mapa->orden!=N_VERTICES_INICIALES || mapa->tamano!=N_ARISTAS_INICIALES) {
        grafo_d_destruir(mapa);
        return NULL;
    }
    #undef N_VERTICES_INICIALES
    #undef N_ARISTAS_INICIALES

    static Contexto contexto = {
        (ParamConfig) {
            .costo_combustible=25.0f,
            .reabastecimiento=0.5f,
        },
        (ParamVehiculo){
            .peso = 4.5f,
            .carga_max = 50.0f,
            .combustible_max = 1000.0f,
            .rendimiento = 3.0f,
            .velocidad_min = 30.0f,
            .velocidad_max = 120.0f,
        },
        (ParamViaje){0}
    };

    mapa->contexto=&contexto;
    grafo_d_set_cmp_vt(mapa, comparar_ciudad_por_nombre);
    grafo_d_set_calc_peso(mapa, calcular_peso_por_distancia);

    return mapa;
}

void mostrar_ciudades(const Grafo_D* mapa) {
    clear();
    println("Lista de ciudades disponibes:");
    const Vect_V* ciudades = grafo_d_get_vertices(mapa);
    if(!ciudades) {
        println("Se precento un error al cargar las ciudades, intentelo denuevo");
        flush();
        return;
    }
    for(int i=0; i<ciudades->tamano; ++i)
        printf("%2d. %s\n", i+1, ciudades->vertices[i]->nombre);
    vect_v_destruir(ciudades);
    flush();
    return;
}

void print_param_vehiculo(const ParamVehiculo* vehiculo) {
    printf("Peso del Vehiculo: %.1f Ton\n", vehiculo->peso);
    printf("Capacidad de Carga: %.1f Ton\n", vehiculo->carga_max);
    printf("Capacidad de Combustible: %.1f L\n", vehiculo->combustible_max);
    printf("Rendimiento de Combustible: %.2f Km/L\n", vehiculo->rendimiento);
    printf("Velocidad con Carga Maxima: %.1f Km/h\n", vehiculo->velocidad_min);
    printf("Velocidad sin Carga Alguna: %.1f Km/h\n", vehiculo->velocidad_max);
}

void print_param_viaje(const ParamViaje* viaje) {
    printf("Peso de Carga: %.1f Ton\n", viaje->carga);
    printf("Combustible: %.1f L\n", viaje->combustible);
    printf("Presupuesto de Pejes: %.2f Mx\n", viaje->presupuesto);
}

void print_menu_de_ayuda(void) {
    
}

void configurar_parametros(Contexto* contexto) {
    while(true) {
        clear();
        println("0. Desplegar Menu de Ayuda",
                "-----------------------------------------",
                "Parametros Generales:",
                "1. Precio de Litro de Combustible",
                "2. Razon de Reabastecimiento",
                "-----------------------------------------");
        println("Parametros del Vehiculo:");
        print_param_vehiculo(&contexto->vehiculo); endl;
        println("Seleccione el parametro que desea ajustar",
                "3. Peso del Vehiculo",
                "4. Capacidad de Carga",
                "5. Capacidad de Combustible",
                "6. Rendimiento",
                "7. Velocidad con Carga Maxima",
                "8. Velocidad sin Carga Alguna",
                "9. Salir");
        edlib_set_prompt(PROMPT_OPC);
        int opc = validar_int_en_rango(1, 5);

        edlib_set_prompt(PROMPT_DATO);
        switch(opc) {
        case 0:
            print_menu_de_ayuda();
            break;
        case 1:
            edlib_set_msj_error("El precio de combustible debe ser mayor a 0");
            contexto->config.costo_combustible=validar_float_min(0.01f);
            break;
        case 2:
            edlib_set_msj_error("La razon de reabastecimiento debe estar entre 0.1 y 1");
            contexto->config.reabastecimiento=validar_float_en_rango(0.1f, 1.0f);
            break;
        case 3:
            edlib_set_msj_error("El peso debe estar entre 1 y 12 toneladas");
            contexto->vehiculo.peso = validar_float_en_rango(1.0f, 12.0f);
            break;
        case 4:
            edlib_set_msj_error("La capacidad de carga debe estar entre 5 y 100 toneladas");
            contexto->vehiculo.carga_max = validar_float_en_rango(0.0f, 100.0f);
            break;
        case 5:
            edlib_set_msj_error("La capacidad de combustible debe estar entre 50 y 2000 litros");
            contexto->vehiculo.combustible_max = validar_float_en_rango(50.0f, 2000.0f);
            break;
        case 6:
            edlib_set_msj_error("El redimineto del vehiculo debe estar entre 0.5 y 6 Km/L");
            contexto->vehiculo.rendimiento = validar_float_en_rango(0.5f, 6.0f);
            break;
        case 7:
            edlib_set_msj_error("La velocidad con carga maxima debe ser mayor a 20 Km/h ");
            contexto->vehiculo.velocidad_min = validar_float_min(20.0f);
            break;
        case 8:
            edlib_set_msj_error("La velocidad sin carga alguna debe ser mayor\n"
                "o igual que la velocidad con carga maxima");
            contexto->vehiculo.velocidad_max = validar_float_min(contexto->vehiculo.velocidad_min);
            break;
        case 9:
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
            usuario_esta_seguro = !(bool)(validar_int_en_rango(1,2)-1);
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

#define L_BUFFER_ERROR 128
Lista_D* leer_ciudades_destino(const Grafo_D* mapa) {
    Lista_D* ciudades = lista_d_crear();
    if(!ciudades) return NULL;

    Ciudad* ciudad;
    Ciudad buffer = {"",0};
    char error[L_BUFFER_ERROR];

    println("Introduzca el nombre de la ciudad donde iniciara el viaje");
    edlib_set_prompt(PROMPT_DATO);
    leer_string(buffer.nombre, L_NOMBRE);
    while(!(ciudad = grafo_d_buscar_vertice(mapa, buffer))) {
        println("No se encontro ninguna ciudad con ese nombre");
        leer_string(buffer.nombre, L_NOMBRE);
    }
    ciudad->peso_entrega=0;
    lista_d_insertar_fin(ciudades, ciudad);

    float carga_restante;
    bool usuario_esta_seguro = false;
    while(!usuario_esta_seguro) {
        carga_restante = mapa->contexto->viaje.carga;
        endl;
        println("Introduzca los nombres de las ciudades a visitar",
                "Introduzca una linea vacia para finalizar la captura");
        endl;
        edlib_set_prompt("Ciudad"PROMPT_DATO);
        while(leer_string(buffer.nombre, L_NOMBRE)) {
            ciudad = grafo_d_buscar_vertice(mapa,buffer);
            if(ciudad) {
                snprintf(error, L_BUFFER_ERROR,
                    "El peso de la entrega debe ser menor\n"
                    "o igual a la carga restante: %.1f Ton",
                    carga_restante);
                edlib_set_prompt("Peso Entrega"PROMPT_DATO);
                edlib_set_msj_error(error);
                ciudad->peso_entrega = validar_float_en_rango(0, carga_restante);
                carga_restante-=ciudad->peso_entrega;
                lista_d_insertar_fin(ciudades, ciudad);
            } else
                println("No se encontro ninguna ciudad con ese nombre");
            endl;
            edlib_set_prompt("Ciudad"PROMPT_DATO);
        }
        if(en_rango(carga_restante, 0, 0.5))
            usuario_esta_seguro = true;
        else {
            printf( "El peso restante de la carga del vehiculo\n"
                    "al finalizar el viaje es de %.1f", carga_restante);
            println("Esta seguro que desea continuar? (1-Si|2-No)");
            edlib_set_prompt(PROMPT_OPC);
            usuario_esta_seguro = !(bool)(validar_int_en_rango(1,2)-1);
        }
    }
    return ciudades;
}

/*  Asigna todos los pesos de entrega de los vertices a 0*/
void limpiar_pesos_de_entrega(Grafo_D* mapa) {
    const Vect_V* vect = grafo_d_get_vertices(mapa);
    for(int i=0; i<vect->tamano; ++i) {
        vect->vertices[i]->peso_entrega=0;
    }
    vect_v_destruir(vect);
}

typedef struct {
    Contexto contexto;
    Camino_D* camino;
} Viaje;

Viaje viaje_secuencial(const Grafo_D* mapa) {
    clear();
    println("Parametros del Vehiculo Actual:");
    print_param_vehiculo(&mapa->contexto->vehiculo);
    println("Desea continuar con esta configuracion?(1-Si|2-No)");
    edlib_set_prompt(PROMPT_OPC);
    if(validar_int_en_rango(1,2)==2) return (Viaje){(Contexto){0}, NULL};
    endl;

    println("Iniciando Viaje Generico:",
            "El orden en el que se introduzcan las ciudades determinara",
            "el orden en el que se visitarn las ciudades para hacer entregas");
    mapa->contexto->viaje = leer_parametros_viaje(&mapa->contexto->vehiculo);
    Viaje viaje = {*(mapa->contexto), NULL};

    Lista_D* ciudades = leer_ciudades_destino(mapa);
    Camino_D* camino = camino_d_crear_trivial(lista_d_pop_inicio(ciudades));
    while(!lista_d_isempty(ciudades)) {
        Camino_D* segmento = grafo_d_dijkstra_unico(mapa,
            camino_d_get_fin(camino),
            lista_d_get_inicio(ciudades)
        );
        for(int i=0; i<segmento->saltos; ++i) {
            float consumo = segmento->ars[i]->longitud/
                calcular_rendimiento_actual(mapa->contexto);
            float peaje = segmento->ars[i]->cuota;
            //Consumir Tanque inicial, rellenar con una fraccion del tanque 
            if(mapa->contexto->viaje.combustible > consumo) {
                mapa->contexto->viaje.combustible-=consumo;
            } else {
                mapa->contexto->viaje.combustible=
                    mapa->contexto->config.reabastecimiento*
                    mapa->contexto->vehiculo.combustible_max;
            }
            //Encontrar otra ruta si se nos acaba el presupuesto
            if(mapa->contexto->viaje.presupuesto >= peaje) {
                mapa->contexto->viaje.presupuesto-=peaje;
            } else {
                segmento = camino_d_frecortar(segmento, i);
                break;
            }
        }
        camino = camino_d_fconcatenar(camino, segmento);
        if(camino_d_get_fin(camino)==lista_d_get_inicio(ciudades)) {
            //Actualizar carga cuando llegamos al destino
            mapa->contexto->viaje.carga-=camino_d_get_fin(camino)->peso_entrega;
            lista_d_eliminar_inicio(ciudades);
        }
    }

    viaje.camino=camino;
    mapa->contexto->viaje=(ParamViaje){0};
    lista_d_destruir(ciudades);
    return viaje;
}

Viaje viaje_generico(const Grafo_D* mapa) {
    clear();
    println("Parametros del Vehiculo Actual:");
    print_param_vehiculo(&mapa->contexto->vehiculo);
    println("Desea continuar con esta configuracion?(1-Si|2-No)");
    edlib_set_prompt(PROMPT_OPC);
    if(validar_int_en_rango(1,2)==2) return (Viaje){(Contexto){0}, NULL};
    endl;

    println("Iniciando Viaje Generico",
            "Las ciudades que se ingresen a continuacion se visitaran en",
            "un el orden mas conveniente para realizar las entregas");
    mapa->contexto->viaje = leer_parametros_viaje(&mapa->contexto->vehiculo);
    Viaje viaje = {*(mapa->contexto), NULL};

    Lista_D* ciudades = leer_ciudades_destino(mapa);
    Camino_D* camino = camino_d_crear_trivial(lista_d_pop_inicio(ciudades));
    while(!lista_d_isempty(ciudades)) {
        Camino_D* segmento = grafo_d_dijkstra_unico(mapa,
            camino_d_get_fin(camino),
            lista_d_get_inicio(ciudades)
        );
        for(int i=0; i<segmento->saltos; ++i) {
            float consumo = segmento->ars[i]->longitud/
                calcular_rendimiento_actual(mapa->contexto);
            float peaje = segmento->ars[i]->cuota;
            //Consumir Tanque inicial, rellenar con una fraccion del tanque 
            if(mapa->contexto->viaje.combustible > consumo) {
                mapa->contexto->viaje.combustible-=consumo;
            } else {
                mapa->contexto->viaje.combustible=
                    mapa->contexto->config.reabastecimiento*
                    mapa->contexto->vehiculo.combustible_max;
            }
            //Encontrar otra ruta si se nos acaba el presupuesto
            if(mapa->contexto->viaje.presupuesto >= peaje) {
                mapa->contexto->viaje.presupuesto-=peaje;
            } else {
                segmento = camino_d_frecortar(segmento, i);
                break;
            }
        }
        camino = camino_d_fconcatenar(camino, segmento);
        if(camino_d_get_fin(camino)==lista_d_get_inicio(ciudades)) {
            //Actualizar carga cuando llegamos al destino
            mapa->contexto->viaje.carga-=camino_d_get_fin(camino)->peso_entrega;
            lista_d_eliminar_inicio(ciudades);
        }
    }

    viaje.camino=camino;
    mapa->contexto->viaje=(ParamViaje){0};
    lista_d_destruir(ciudades);
    return viaje;
}

void print_viaje(Viaje viaje) {    
    struct {
        float distancia;
        float tiempo;
        float combustible;
        float peaje;
        float gastos;
    } total={0};

    struct {
        float tiempo;
        float combustible;
        float combustible_tanque;
        float combustible_transito;
    } tmp={0};

    clear();
    println("------------Resumen del Viaje------------"); endl;

    println("Parametros Iniciales:");
    print_param_viaje(&viaje.contexto.viaje);
    printf("Ciudad de Inicio: %s\n", camino_d_get_inicio(viaje.camino)->nombre);
    endl;

    for(int i=0; i<viaje.camino->saltos; ++i) {
        Carretera* carretera = viaje.camino->ars[i];
        Ciudad* ciudad = viaje.camino->vts[i+1];
        printf("Tomar %s hacia %s\n", carretera->nombre, ciudad->nombre);

        printf("Distancia Recorrida: %.1f Km\n", carretera->longitud);
        total.distancia += carretera->longitud;

        tmp.tiempo = carretera->longitud/
            calcular_vel_max_actual(carretera, &viaje.contexto);
        printf("Tiempo Estimado: %.1f Hrs\n", tmp.tiempo);
        total.tiempo += tmp.tiempo;

        tmp.combustible = carretera->longitud/
            calcular_rendimiento_actual(&viaje.contexto);
        printf("Combustible Consumido: %.1f L\n", tmp.combustible);
        total.combustible += tmp.combustible;
        
        if(carretera->cuota!=0.0f) {
            printf("Peaje: %.2f Mx\n", carretera->cuota);
            total.peaje += carretera->cuota;
        }

        if(ciudad->peso_entrega!=0.0f) {
            printf("Se realizo una entrega en %s\n", ciudad->nombre);
            printf("Peso de entrega: %.1f Ton\n", ciudad->peso_entrega);
        }
        endl;
    }
    endl;

    println("-------------Desglose Final--------------");
    printf("Distancia Total Recorrida: %0.1f Km\n", total.distancia);
    printf("Tiempo Total Estimado: %0.1f Hrs\n", total.tiempo);
    printf("Combustible Total Consumido: %0.1f L\n", total.combustible);
    tmp.combustible_transito = total.combustible-viaje.contexto.viaje.combustible;
    if(tmp.combustible_transito >= 0.0f) {
        tmp.combustible_tanque = viaje.contexto.viaje.combustible;
    } else {
        tmp.combustible_tanque = total.combustible;
        tmp.combustible_transito = 0.0f;
    }
    printf("  *Inicialmente en el Tanque: %0.1f L\n", tmp.combustible_tanque);
    printf("  *Comprada en Transito: %0.1f L\n", tmp.combustible_transito);
    printf("Total de Pejes Pagados: %0.1f Mx\n", total.peaje);
    endl;

    total.gastos = total.peaje+total.combustible*
        viaje.contexto.config.costo_combustible;
    printf("Considerando el precio decombustible como %.2f Mx\n",
            viaje.contexto.config.costo_combustible);
    printf("La cantida de gastos fue: %.2f\n", total.gastos);
    flush();
    return;
}