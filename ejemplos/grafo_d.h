/*Grafo_D V0.2: Libraria de TDA Implementado Mediante Lista de Adyacencia*/
#ifndef _GRAFO_D_H
#define _GRAFO_D_H

#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>
#include <string.h>
#include <limits.h>
#include <assert.h>

/*  LIBRERIA DE GRAFOS DINAMICOS GRAFO_D
    Esta es una libreria de tipo cabezera que implementa el tipo de dato abstracto
    Grafo_D mediante una lista de adyacencia. Su alcance es limitado ya que las operaciones
    no estan optimizadas asimtoticamente debido este TDA fue imlementado unicamente con
    listas enlazadas.

    La libreria esta disenada para que tanto los vertices como las aristas puedan aceptar
    un valor de tipo dato generico para su representacion asi como structs si se requiere
    de una representacion mas compleja. Si no se especifica los tipos de dato de los
    vertices/aristas se asume que se representaran por medio de un tipo de dato (int).

    Las macros siguientes permiten la customizacion de los tipos de datos que se usaran para
    la representar los distintos componentes/propiedades del grafo. Deben definirse antes de
    incluir la libreria.
    ----------------------------------------------------------------------------------------

    DATO_VERTICE/STRUCT_VERTICE: Permite asignar el tipo de dato que se usara para
    representar a cada vertice de los grafos creados con la libreria. Solo uno de estos
    dos macros debe ser definido a la vez: DATO_VERTICE si el tipo definido es un tipo por
    default del lenguaje (int,float,double,long, etc.) o STRUCT_VERTICE si el dato es un
    tipo de dato struct. Ejemplos:
    #define DATO_VERTICE double
    #define STRUCT_VERTICE Punto, sea punto un struct definido por el usuario

    DATO_VERTICE/STRUCT_VERTICE: Permite asignar el tipo de dato que se usara para
    representar a cada arista de los grafos creados con la libreria. Solo uno de estos
    dos macros debe ser definido a la vez: DATO_ARISTA si el tipo definido es un tipo por
    default del lenguaje (int,float,double,long, etc.) o STRUCT_ARISTA si el dato es un
    tipo de dato struct. Ejemplos:
    #define DATO_ARISTA double
    #define STRUCT_ARISTA Punto, sea punto un struct definido por el usuario

    DATO_PESO: Permite asignar el tipo de dato que se usa para representar el peso de una
    arista, la matriz de pesos sera una matriz de este tipo de dato. Si se define un DATO_PESO
    antes de incluir la libreria, se debera definir tambien la macro PESO_NO_ARISTA. El valor
    de DATO_PESO tiene que se un tipo por default numerico(float, int, etc). Ejemplo:
    #define DATO_PESO double
    #define DATO_PESO unsigned int

    PESO_NO_ARISTA: Es un valor tipo DATO_PESO que sera el asignado cuando no exista una arista
    entre dos vertices. Suele ser un valor muy alto en relacion a el tipo especificado. Ejemplo:
    Si DATO_PESO fue definido como double entonces
    #define PESO_NO_ARISTA HUGE_VAL
    Si DATO_PESO fue definido como unsigned long long
    #define PESO_NO_ARISTA ULLONG_MAX
*/

/*------------------------Macros y Customizacion de la Libreria------------------------*/
#if defined(STRUCT_VERTICE) && defined(DATO_VERTICE)
#error "Defina exlusivamente STRUCT_VERTICE o DATO_VERTICE no ambos"
#endif

#if defined(STRUCT_ARISTA) && defined(DATO_ARISTA)
#error "Defina exlusivamente STRUCT_ARISTA o DATO_ARISTA no ambos"
#endif

#ifdef STRUCT_VERTICE
#define Vertice STRUCT_VERTICE
#endif

#ifdef STRUCT_ARISTA
#define Arista STRUCT_ARISTA
#endif

#ifdef DATO_VERTICE
#define Vertice DATO_VERTICE
#endif

#ifdef DATO_ARISTA
#define Arista DATO_ARISTA
#endif

#ifdef DATO_PESO
#define peso_t DATO_PESO
#ifndef PESO_NO_ARISTA
#error "Defina la MACRO PESO_NO_ARISTA para el DATO_PESO definido" 
#endif 
#endif

#ifndef Vertice
#define Vertice int
#endif

#ifndef Arista
#define Arista int
#endif

#ifndef peso_t
#define peso_t int
#define PESO_NO_ARISTA INT_MAX
#endif

#ifdef GRAFO_D_METADATA
#define MetaData GRAFO_D_METADATA
#endif

#define malloc_fam(tipo_estructura, tipo_elemento, tamano) \
    malloc(sizeof(tipo_estructura)+sizeof(tipo_elemento)*tamano)

/*----------------------Definicion de los tipos de datos de interfaz---------------------*/

typedef struct vect_v{
    size_t tamano;
    Vertice* vertices[];
} Vect_V;

/*  Crea un vector estatico en el heap capaz de contener hasta 'tamano' verices
    No es posible modificar el tamano del vector despues de crearlo
*/
static inline Vect_V* vect_v_crear(size_t tamano) {
    Vect_V* vect = (Vect_V*)malloc_fam(Vect_V, Vertice*, tamano);
    if(!vect) return NULL;
    vect->tamano=tamano;
    memset(vect->vertices,0, sizeof(Vertice*)*tamano);
    return vect;
}

typedef struct vect_a {
    size_t tamano;
    Arista* aristas[];
} Vect_A;

/*  Crea un vector estatico en el heap capaz de contener hasta 'tamano' verices
    No es posible modificar el tamano del vector despues de crearlo
*/
static inline Vect_A* vect_a_crear(size_t tamano) {
    Vect_A* vect = (Vect_A*)malloc_fam(Vect_A, Arista*, tamano);
    if(!vect) return NULL;
    vect->tamano=tamano;
    memset(vect->aristas, 0, sizeof(Arista*)*tamano);
    return vect;
}

struct _nodo_a;
struct _nodo_v;

struct _nodo_a {
    struct _nodo_a* sig;
    Arista ar;
    struct _nodo_v* fin;
};

struct _nodo_v {
    struct _nodo_v* sig;
    Vertice vt;
    size_t grado_s;
    struct _nodo_a* lista_ady;
}; 

typedef struct grafo_d {
    struct _nodo_v* lista_ady;
    struct _nodo_v* lista_fin;
    size_t orden;
    size_t tamano;
    bool (*cmp_vt)(const Vertice*, const Vertice*);
    bool (*cmp_ar)(const Arista*, const Arista*);
    peso_t (*calc_peso)(const struct grafo_d*, const Arista*);
    #ifdef GRAFO_D_METADATA
    MetaData contexto;
    #endif
} Grafo_D;

/*---------------------------Operaciones basicas del grafo------------------------------*/

#ifndef STRUCT_VERTICE
static bool _grafo_d_cmp_vt_default(const Vertice* v1, const Vertice* v2) {return *v1==*v2;}
#define cmp_vt_default _grafo_d_cmp_vt_default
#else
#define cmp_vt_default NULL
#endif

#ifndef STRUCT_ARISTA
static bool _grafo_d_cmp_ar_default(const Arista* a1, const Arista* a2) {return *a1==*a2;}
#define cmp_ar_default _grafo_d_cmp_ar_default
#else
#define cmp_ar_default NULL
#endif

static peso_t _grafo_d_calc_peso_default(const Grafo_D* grafo, const Arista* arista) {return (peso_t)1;}
#define calc_peso_default _grafo_d_calc_peso_default

/*  Crear un grafo vacio para empezar a realizar operaciones. Algunas funciones requieren
    que el grafo tenga asociado un comportamineto en particular, mediante las funciones
    grafo_d_set_cmp_vt(), grafo_d_set_cmp_ar() y grafo_d_set_calc_peso() 
*/
static Grafo_D* grafo_d_crear(void) {
    Grafo_D* grafo = (Grafo_D*)malloc(sizeof(Grafo_D));
    if(!grafo) return NULL;
    grafo->lista_ady=NULL;
    grafo->lista_fin=NULL;
    grafo->orden=0;
    grafo->tamano=0;
    grafo->cmp_vt=cmp_vt_default;
    grafo->cmp_ar=cmp_ar_default;
    grafo->calc_peso=calc_peso_default;
    return grafo;
}

/*  Regresa la cantidad de vertices en el grafo*/
static inline size_t grafo_d_get_orden(const Grafo_D* grafo) {return grafo->orden;}

/*  Regresa la cantidad de aristas en el grafo*/
static inline size_t grafo_d_get_tamano(const Grafo_D* grafo) {return grafo->tamano;}

/*  Asigna una funcion bool cmp_vt(Vertice*, Vertice*) implementada por el usario de
    la libreria responsable de comparar las vertices del grafo. Esta funcion se debe
    registrarse obligatorimente cuando el usario ha definido los vertices del grafo
    como tipo struct y se va hacer uso de la funcion grafo_d_buscar_vertice(). 
*/
static inline void grafo_d_set_cmp_vt(Grafo_D* grafo,
    bool (*cmp_vt)(const Vertice*, const Vertice*)) {grafo->cmp_vt=cmp_vt;}

/* Regresa el comportamiento de comparacion de vertices a su estado por defecto*/
static inline void grafo_d_unset_cmp_vt(Grafo_D* grafo) {
    grafo->cmp_vt=cmp_vt_default;}

/*  Asigna una funcion bool cmp_ar(Arista*, Arista*) implementada por el usuario de
    la libreria responsable de comparar las aristas de el grafo. Esta funcion debe
    registrarse obligatoriamente cuando el usuario ha definido las aristas del grafo
    como tipo struct y se va hacer uso de alguna de las funciones grafo_d_buscar_arista(s)_...()
    a excepcion de las funciones grafo_d_buscar_arista(s)_entre_vert()
*/
static inline void grafo_d_set_cmp_ar(Grafo_D* grafo,
    bool (*cmp_ar)(const Arista*, const Arista*)) {grafo->cmp_ar=cmp_ar;}

/* Regresa el comportamiento de comparacion de aristas a sus estado por defecto*/
static inline void grafo_d_unset_cmp_ar(Grafo_D* grafo) {
    grafo->cmp_ar=cmp_ar_default;}

/*  Asigna una funcion peso_t calc_peso(Arista*) implementada por el usuario de la
    libreria reponsable de asignar un peso en base a la informacion de una arista del grafo
    Esta funcion nunca es obligatoria de registrar, su comportamiento por default es regresar
    (peso_t)1 para toda arista elemento del grafo.
*/
static inline void grafo_d_set_calc_peso(Grafo_D* grafo,
    peso_t (*calc_peso)(const Grafo_D*,const Arista*)) {grafo->calc_peso=calc_peso;}

/* Regresa el comportamiento de asignacion de pesos a su estado pro defecto*/
static inline void grafo_d_unset_calc_peso(Grafo_D* grafo) {
    grafo->calc_peso=calc_peso_default;}

/*  Regresa si el grafo se encuentra vacio*/
static inline bool grafo_d_isempty(const Grafo_D* grafo) {
    return grafo->lista_ady==NULL
        && grafo->lista_fin==NULL 
        && grafo->orden==0;
}

/*  Libera la memoria reservada dinamicamente para el grafo, el puntero a el grafo
    pasado a la funcion queda invalidado despues de esta operacion
*/
static void grafo_d_destruir(Grafo_D* grafo) {
    struct _nodo_v* vptr = grafo->lista_ady, *vtmp;
    while(vptr!=NULL) {
        struct _nodo_a *aptr = vptr->lista_ady, *atmp;
        while(aptr!=NULL) {
            atmp=aptr;
            aptr=aptr->sig;
            free(atmp);
        }
        vtmp=vptr;
        vptr=vptr->sig;
        free(vtmp);
    }
    free(grafo);
    return;
}

/*----------------------------Operaciones sobre los vertices-----------------------------*/

/*  Regresa un vector dinamcamente alojado que contiene todos los vertices del grafo.
    El vector debe ser liberado con una llamada correspondiente a free()
*/
static Vect_V* grafo_d_get_vertices(const Grafo_D* grafo) {
    Vect_V* vec = (Vect_V*)malloc_fam(Vect_V, Vertice*, grafo->orden);
    if(!vec) return NULL;
    vec->tamano=grafo->orden;
    int i=0;
    struct _nodo_v* vptr = grafo->lista_ady;
    while(vptr!=NULL) {
        vec->vertices[i]=&vptr->vt;
        vptr=vptr->sig;
        ++i;
    }
    return vec;
}

/*  Inserta un vertice con los datos que contenga el agumento vt, devuelve la direccion
    de memoria que identifica al vertice como elemento unico del grafo, las demas operaciones
    que esperan un argumento vertice toman este valor de retorno para identificar el vertice
*/
static Vertice* grafo_d_insertar_vertice(Grafo_D* grafo, Vertice vt) {
    struct _nodo_v* nuevo = (struct _nodo_v*)malloc(sizeof(struct _nodo_v));
    if(!nuevo) return NULL;
    nuevo->lista_ady=NULL;
    nuevo->sig=NULL;
    nuevo->vt=vt;
    nuevo->grado_s=0;
    //Vertices se insetan por el final en tiempo constante
    if(grafo->lista_fin==NULL) {
        grafo->lista_ady=nuevo;
        grafo->lista_fin=nuevo;
    }
    else {
        grafo->lista_fin->sig=nuevo;
        grafo->lista_fin=nuevo;
    }
    ++(grafo->orden);
    return &nuevo->vt;
}

/*  Regresa la direccion de memoria (identificador) del primer vertice que haga que
    la funcion grafo->cmp_vt() regrese como verdadero
*/
static Vertice* grafo_d_buscar_vertice(const Grafo_D* grafo, Vertice ref) {
    assert(grafo->cmp_vt!=NULL);
    struct _nodo_v* vptr = grafo->lista_ady;
    while(vptr!=NULL) {
        if(grafo->cmp_vt(&vptr->vt,&ref))
            return &vptr->vt;
        vptr=vptr->sig;
    }
    return NULL;
}

/*  Regresa un vector almacenado dinamicamente que contine los vertices que hacen que
    funcion grafo->cmp_vt() regrese verdadero. El vector esta reservado con memoria dinamica
    por lo que necesita ser liberado con una llamada a free()
*/
static Vect_V* grafo_d_buscar_vertices(const Grafo_D* grafo, Vertice ref) {
    assert(grafo->cmp_vt!=NULL);
    Vect_V* vectmp = (Vect_V*)malloc_fam(Vect_V, Vertice*, grafo->orden);
    if(!vectmp) return NULL;
    vectmp->tamano=0;
    struct _nodo_v* vptr=grafo->lista_ady;
    while(vptr!=NULL) {
        if(grafo->cmp_vt(&vptr->vt, &ref)) {
            vectmp->vertices[vectmp->tamano]=&vptr->vt;
            ++(vectmp->tamano);
        }
        vptr=vptr->sig;
    }
    Vect_V* vector = (Vect_V*)malloc_fam(Vect_V, Vertice*, vectmp->tamano);
    if(!vector) {free(vectmp); return NULL;}
    memcpy(vector->vertices, vectmp->vertices, sizeof(Vertice*)*vectmp->tamano);
    vector->tamano=vectmp->tamano;
    free(vectmp);
    return (Vect_V*)vector;
}


/*  Elimna un unico vertice cuyo identificador esta dado por el argumento vt. Las aristas
    que concetan con el vertice vt tambien son eliminadas. Esta funcion espera como argumento vt
    un puntero valido a un vertice del grafo, resultado de las funciones crear o buscar vertices.
    De no ser asi el comportamiento de la funcion es indefinido.
*/
static void grafo_d_eliminar_vertice(Grafo_D* grafo, Vertice* vt) {
    struct _nodo_v* vptr = grafo->lista_ady, *vprev=NULL, *vtmp;
    //Recorremos todos los vertices
    while(vptr!=NULL) {
        struct _nodo_a* aptr = vptr->lista_ady, *aprev=NULL, *atmp;
        //Si el nodo actual contiene el vertice a eliminar
        if(vt==&vptr->vt) {
            //Borramos todas las aristas que salen del vertice
            while(aptr!=NULL) {
                atmp=aptr;
                aptr=aptr->sig;
                free(atmp);
            }
            //Actualizamos el numero de aristas del grafo
            grafo->tamano-=vptr->grado_s;
            //Movemos solamente el puntero de vertice actual
            vtmp=vptr;
            vptr=vptr->sig;
            /*Si el vertice a elminar es el ultimo eliminamos
            actualizamos grafo->lista->fin*/
            if(vtmp==grafo->lista_fin) 
                grafo->lista_fin=vprev;
            //Conectamos la lista saltando el vertice eliminado
            if(vprev!=NULL) vprev->sig=vptr; 
            else grafo->lista_ady=vptr;
            //Eliminamos el vertice y actualizamos orden
            free(vtmp);
            --(grafo->orden);
        }
        //Si es cualquier otro vertice
        else {
            //Recorremos todas sus aristas
            while(aptr!=NULL) {
                //Si la arista termina en el vertice a eliminar
                if(vt==&aptr->fin->vt) {
                    //Movemos solamente el puntero de arista actual
                    atmp=aptr;
                    aptr=aptr->sig;
                    //Conectamos la lista saltando el vertice eliminado
                    if(aprev!=NULL) aprev->sig=aptr;
                    else vptr->lista_ady=aptr;
                    //Eliminamos la arista y actualizamos grado, tamano
                    free(atmp);
                    --(vptr->grado_s);
                    --(grafo->tamano);
                }
                else {
                    //Si fue una arista regular avanzamos aptr y aprev
                    aprev=aptr;
                    aptr=aptr->sig;
                }
            }
            //Si fue un vertice regular avanzamos vptr y vprev
            vprev=vptr; 
            vptr=vptr->sig;
        }
    }
    return;
}

/*----------------------------Operaciones sobre las aristas------------------------------*/

/*  Regresa un vector dinamicamente alojado que contine todas las aristas del grafo.
    El vector debe ser liberado con una correspondiente llamada a free()
*/
static Vect_A* grafo_d_get_aristas(const Grafo_D* grafo) {
    Vect_A* vec = (Vect_A*)malloc_fam(Vect_A, Arista*, grafo->tamano);
    if(!vec) return NULL;
    vec->tamano=grafo->tamano;
    int i=0;
    struct _nodo_v* vptr = grafo->lista_ady;
    while(vptr!=NULL) {
        struct _nodo_a* aptr = vptr->lista_ady;
        while(aptr!=NULL) {
            vec->aristas[i]=&aptr->ar;
            aptr=aptr->sig;
            ++i;
        }
        vptr=vptr->sig;
    }
    return vec;
}

/*  Inserta una arista entre el vertice ini y el vertice fin que va de ini a fin. Los datos de la
    arista seran los suministrados mediante el argumento ar. La funcion devuelve la direccion de memoria
    (identificador) de la arista como elemento unico del grafo.
*/
static Arista* grafo_d_insertar_arista(Grafo_D* grafo, Arista ar, const Vertice* ini, const Vertice* fin) {
    struct _nodo_a* nuevo = (struct _nodo_a*)malloc(sizeof(struct _nodo_a));
    if(!nuevo) return NULL;
    nuevo->ar=ar; nuevo->fin=NULL;
    struct _nodo_v* vptr=grafo->lista_ady, *inicio=NULL;
    //Encontramos los nodos correspondientes a ini y a fin
    while(nuevo->fin==NULL || inicio==NULL) {
        if(ini==&vptr->vt) inicio=vptr;
        if(fin==&vptr->vt) nuevo->fin=vptr;
        vptr=vptr->sig;
    }
    //La arista se inserta por el principio
    nuevo->sig=inicio->lista_ady;
    inicio->lista_ady=nuevo;
    ++(inicio->grado_s);
    ++(grafo->tamano);
    return &nuevo->ar;
}

/*  Inseta un par de aristas conjugadas (una arista de ini a fin y otra de fin a ini) entre dos vertices.
    Los datos para ambas aristas estan dados por el paramentro ar. La funcion devuelve un vector alamacenado
    dinamicamente de tamano 2 que contine ambas aristas. Debido a que el vector que regresa la funcion es
    dinamicamente alojado en memoria debe ser liberado con una llamada free()
*/
static Vect_A* grafo_d_insertar_aristas_conjugadas(Grafo_D* grafo, Arista ar, const Vertice* ini, const Vertice* fin) {
    struct _nodo_a* ini_fin = (struct _nodo_a*)malloc(sizeof(struct _nodo_a));
    if(!ini_fin) return NULL;
    struct _nodo_a* fin_ini = (struct _nodo_a*)malloc(sizeof(struct _nodo_a));
    if(!fin_ini) {free(ini_fin); return NULL;}
    Vect_A* vect = (Vect_A*)malloc_fam(Vect_A, Arista*, 2);
    if(!vect) {free(ini_fin); free(fin_ini); return NULL;}
    vect->tamano=2;
    ini_fin->ar=fin_ini->ar=ar;
    ini_fin->fin=fin_ini->fin=NULL;
    struct _nodo_v* vptr=grafo->lista_ady;
    while(ini_fin->fin==NULL || fin_ini->fin==NULL) {
        if(ini==&vptr->vt) {
            fin_ini->fin=vptr;
            ini_fin->sig=vptr->lista_ady;
            vptr->lista_ady=ini_fin;
            ++(vptr->grado_s);
        }
        if(fin==&vptr->vt) {
            ini_fin->fin=vptr;
            fin_ini->sig=vptr->lista_ady;
            vptr->lista_ady=fin_ini;
            ++(vptr->grado_s);
        }
        vptr=vptr->sig;
    }

    grafo->tamano+=2;
    vect->aristas[0]=&ini_fin->ar;
    vect->aristas[1]=&fin_ini->ar;
    return vect;
}

/*  Inserta un par de aristas conjugadas (una de ini a fin y otra de fin a ini) en el grafo ambos con
    la informacion suministrada al paramentro ar. La funcion regresa si la insersion se realizo exitosamente.
*/
static bool grafo_d_insertar_arcnj(Grafo_D* grafo, Arista ar, const Vertice* ini, const Vertice* fin) {
    struct _nodo_a* ini_fin = (struct _nodo_a*)malloc(sizeof(struct _nodo_a));
    if(!ini_fin) return false;
    struct _nodo_a* fin_ini = (struct _nodo_a*)malloc(sizeof(struct _nodo_a));
    if(!fin_ini) {free(ini_fin); return false;}
    ini_fin->ar=fin_ini->ar=ar;
    ini_fin->fin=fin_ini->fin=NULL;
    struct _nodo_v* vptr=grafo->lista_ady;
    while(ini_fin->fin==NULL || fin_ini->fin==NULL) {
        if(ini==&vptr->vt) {
            fin_ini->fin=vptr;
            ini_fin->sig=vptr->lista_ady;
            vptr->lista_ady=ini_fin;
            ++(vptr->grado_s);
        }
        if(fin==&vptr->vt) {
            ini_fin->fin=vptr;
            fin_ini->sig=vptr->lista_ady;
            vptr->lista_ady=fin_ini;
            ++(vptr->grado_s);
        }
        vptr=vptr->sig;
    }
    grafo->tamano+=2;
    return true;
}

/*  Regresa la direccion de memoria(identificador) del la primer arista que haga que la
    funcion grafo->cmp_ar() regrese verdadero.
*/
static Arista* grafo_d_buscar_arista(const Grafo_D* grafo, Arista ref) {
    assert(grafo->cmp_ar!=NULL);
    struct _nodo_v* vptr = grafo->lista_ady;
    while(vptr!=NULL) {
        struct _nodo_a* aptr = vptr->lista_ady;
        while(aptr!=NULL) {
            if(grafo->cmp_ar(&aptr->ar,&ref)) {
                return &aptr->ar;
            }
            aptr=aptr->sig;
        }
        vptr=vptr->sig;
    }
    return NULL;
}

/*  Regresa un vector almacenado dinamicamente con las direcciones de memoria de todas
    las aristas en el grafo que hagan que la funcion grafo->cmp_ar() regrese verdader.
    El vector debera ser liberado mediante una llamada a la funcion free()
*/
static Vect_A* grafo_d_buscar_aristas(const Grafo_D* grafo, Arista ref) {
    assert(grafo->cmp_ar!=NULL);
    Vect_A* vectmp = (Vect_A*)malloc_fam(Vect_A, Arista*, grafo->tamano);
    if(!vectmp) return NULL;
    vectmp->tamano=0;
    struct _nodo_v* vptr = grafo->lista_ady;
    while(vptr!=NULL) {
        struct _nodo_a* aptr = vptr->lista_ady;
        while(aptr!=NULL) {
            if(grafo->cmp_ar(&aptr->ar, &ref)) {
                vectmp->aristas[vectmp->tamano]=&aptr->ar;
                ++(vectmp->tamano); 
            }
            aptr=aptr->sig;
        }
        vptr=vptr->sig;
    }
    Vect_A* vector = (Vect_A*)malloc_fam(Vect_A, Arista*, vectmp->tamano);
    if(!vector) {free(vectmp); return NULL;}
    memcpy(vector->aristas, vectmp->aristas, sizeof(Arista*)*vectmp->tamano);
    vector->tamano=vectmp->tamano;
    free(vectmp);
    return (Vect_A*)vector;
}

/*  Regresa la primera arista que tenga como inicio al vertice ini y de fin al vertice fin*/
static Arista* grafo_d_buscar_arista_entre_vert(const Grafo_D* grafo, const Vertice* ini, const Vertice* fin) {
    struct _nodo_v* vptr = grafo->lista_ady;
    while(ini!=&vptr->vt) vptr=vptr->sig;
    struct _nodo_a* aptr = vptr->lista_ady;
    while(aptr!=NULL) {
        if(fin==&aptr->fin->vt)
            return &aptr->ar;
        aptr=aptr->sig;
    }
    return NULL;
}

/*  Regresa un vector alamacenado dinamicamente con todas las aristas del grafo que tengan como
    inicio al vertice ini y de fin al vertice fin. El vector debera ser liberado mediante 
    una llamada a la funcion free()
*/
static Vect_A* grafo_d_buscar_aristas_entre_vert(const Grafo_D* grafo, const Vertice* ini, const Vertice* fin) {
    struct _nodo_v* vptr=grafo->lista_ady;
    while(vptr!=NULL && ini!=&vptr->vt) vptr=vptr->sig;
    Vect_A* vectmp = (Vect_A*)malloc_fam(Vect_A, Arista*, vptr->grado_s);
    if(!vectmp) return NULL;
    vectmp->tamano=0;
    struct _nodo_a* aptr=vptr->lista_ady;
    while(aptr!=NULL) {
        if(fin==&aptr->fin->vt) {
            vectmp->aristas[vectmp->tamano]=&aptr->ar;
            ++(vectmp->tamano); 
        }
        aptr=aptr->sig;
    }
    Vect_A* vector = (Vect_A*)malloc_fam(Vect_A, Arista*, vectmp->tamano);
    if(!vector) {free(vectmp); return NULL;}
    memcpy(vector->aristas, vectmp->aristas, sizeof(Arista*)*vectmp->tamano);
    vector->tamano=vectmp->tamano;
    free(vectmp);
    return (Vect_A*)vector;
}

/*  Regresa la primera arista que haga que la funcion grafo->cmp_ar() regrese verdadero asi
    como que tenga como inicio al vertice ini y de fin al vertice fin
*/
static Arista* grafo_d_buscar_arista_estricto(const Grafo_D* grafo, Arista ref, const Vertice* ini, const Vertice* fin) {
    assert(grafo->cmp_ar!=NULL);
    struct _nodo_v* vptr=grafo->lista_ady;
    while(ini!=&vptr->vt) vptr=vptr->sig;
    struct _nodo_a* aptr=vptr->lista_ady;
    while(aptr!=NULL) {
        if(fin==&aptr->fin->vt && grafo->cmp_ar(&aptr->ar, &ref))
            return &aptr->ar;
        aptr=aptr->sig;
    }
    return NULL;
}

/*  Regresa un vector alamacenado dinamicamente con todas las aristas del grafo que hagan que la
    funcion grafo->cmp_ar() regrese verdadero asi como que tenga como inicio al vertice ini y de fin
    al vertice fin. El vector debera ser liberado mediante una llamada a la funcion free()
*/
static Vect_A* grafo_d_buscar_aristas_estricto(const Grafo_D* grafo, Arista ref, const Vertice* ini, const Vertice* fin) {
    assert(grafo->cmp_ar!=NULL);
    struct _nodo_v* vptr=grafo->lista_ady;
    while(ini!=&vptr->vt) vptr=vptr->sig;
    Vect_A* vectmp = (Vect_A*)malloc_fam(Vect_A, Arista*, vptr->grado_s);
    if(!vectmp) return NULL;
    vectmp->tamano=0;
    struct _nodo_a* aptr=vptr->lista_ady;
    while(aptr!=NULL) {
        if(fin==&aptr->fin->vt && grafo->cmp_ar(&aptr->ar, &ref)) {
            vectmp->aristas[vectmp->tamano]=&aptr->ar;
            ++(vectmp->tamano); 
        }
        aptr=aptr->sig;
    }
    Vect_A* vector = (Vect_A*)malloc_fam(Vect_A, Arista*, vectmp->tamano);
    if(!vector) {free(vectmp); return NULL;}
    memcpy(vector->aristas, vectmp->aristas, sizeof(Arista*)*vectmp->tamano);
    vector->tamano=vectmp->tamano;
    free(vectmp);
    return (Vect_A*)vector;
}

/*  Elimina la arista del grafo pasada como agumento ar. El argumento ar debe ser el
    resultado de llamar a alguna funcion de crear o buscar arista. En caso contrario, el
    comportamiento de esta funcio es indefinido
*/
static void grafo_d_elminar_arista(Grafo_D* grafo, Arista* ar) {
    struct _nodo_v* vptr = grafo->lista_ady;
    while(vptr!=NULL) {
        struct _nodo_a* aptr = vptr->lista_ady, *aprev;
        if(aptr!=NULL && ar==&aptr->ar) {
            vptr->lista_ady=aptr->sig;
            free(aptr);
            --(vptr->grado_s);
            --(grafo->tamano);
            return;
        }
        aprev=aptr; aptr=aptr->sig;        
        while(aptr!=NULL) {
            if(ar==&aptr->ar) {
                aprev->sig=aptr->sig;
                free(aptr);
                --(vptr->grado_s);
                --(grafo->tamano);
                return;
            }
            aprev=aptr;
            aptr=aptr->sig;
        }
        vptr=vptr->sig;
    }
    return;
}

/*----------------------------Operaciones de Representacion Matricial------------------------------*/

/*Matriz de Adyacencia con referencias
a los DATOS crudos de cada arista*/
typedef struct matrizady_d {
    size_t orden;
    Arista* datos[];
} MatrizAdy_D;

/*Matriz de Adyacencia matematicamente
correcta con valores NUMERICOS enteros*/
typedef struct matrizady_n {
    size_t orden;
    size_t datos[];
} MatrizAdy_N;

/*Matriz de PESOS*/
typedef struct matrizady_p {
    size_t orden;
    peso_t datos[];
} MatrizAdy_P;

/*  Devuelve el elemento de una matriz de adyacencia o de pesos que corresponde a la arista del
    grafo que tiene inicio en el vertice agrado en la posicion i y fin el vertice agregado en
    la posicion j.
*/
#define GD_MATRIZ_INDEX(matriz, i, j) (*(matriz->datos+i*matriz->orden+j))

/*  Regresa una matiz de adyacencia de (grafo->orden)x(grafo->orden) almacenada dinamicamente cuyos
    ejes estan ordenados de acuerdo a el orden en el que los vertices fueron insertados en el grafo.
    La matriz contine la direccion de memoria a un dato tipo Arista en cada celda de la matriz.
    Todo acceso a la matriz de hacerse mediante la MACRO GD_MATRIZ_INDEX(matriz, i, j). La memoria
    reservada para la matriz debe de ser liberada mediante una llamada a la funcion free(). Esta matriz
    NO TOMA EN CUENTA varias aristas entre los mismos vertices (multigrafos), tomando por defecto la
    primera arista encontrada
*/
static MatrizAdy_D* grafo_d_generar_matriz_datos(const Grafo_D* grafo) {
    MatrizAdy_D* matriz = (MatrizAdy_D*)malloc_fam(
        MatrizAdy_D, Arista*, grafo->orden*grafo->orden);
    if(!matriz) return NULL;
    matriz->orden=grafo->orden;
    struct _nodo_v* ini=grafo->lista_ady;
    for(int i=0; i<grafo->orden; ++i, ini=ini->sig) {
        struct _nodo_v* fin=grafo->lista_ady;
        for(int j=0; j<grafo->orden; ++j, fin=fin->sig) {
            Arista** ptr_celda=(matriz->datos)+i*grafo->orden+j;
            struct _nodo_a* aptr=ini->lista_ady;
            *ptr_celda=NULL;
            while(aptr!=NULL) {
                if(fin==aptr->fin) { 
                    *ptr_celda=&aptr->ar;
                    break;
                }
                aptr=aptr->sig;
            }
        }
    }
    return matriz;
}

/*  Regresa una matiz de adyacencia de (grafo->orden)x(grafo->orden) almacenada dinamicamente cuyos
    ejes estan ordenados de acuerdo a el orden en el que los vertices fueron insertados en el grafo.
    La matriz almacena la cantidad de conexiones entre aristas de acuerdo al criterio de matriz de
    ayacencia definido matematicamente para grafos ponderados. Todo acceso a la matriz de hacerse
    mediante la MACRO GD_MATRIZ_INDEX(matriz, i, j). La memoria reservada para la matriz debe de ser
    liberada medianteuna llamada a la funcion free()
*/
static MatrizAdy_N* grafo_d_generar_matriz_ady(const Grafo_D* grafo) {
    MatrizAdy_N* matriz = (MatrizAdy_N*)malloc_fam(
        MatrizAdy_N, size_t, grafo->orden*grafo->orden);
    if(!matriz) return NULL;
    matriz->orden=grafo->orden;
    struct _nodo_v* ini=grafo->lista_ady;
    for(int i=0; i<grafo->orden; ++i, ini=ini->sig) {
        struct _nodo_v* fin=grafo->lista_ady;
        for(int j=0; j<grafo->orden; ++j, fin=fin->sig) {
            size_t* ptr_celda=(matriz->datos)+i*grafo->orden+j;
            struct _nodo_a* aptr=ini->lista_ady;
            *ptr_celda=0;
            while(aptr!=NULL) {
                if(fin==aptr->fin) { 
                    ++(*ptr_celda);
                }
                aptr=aptr->sig;
            }
        }
    }
    return matriz;
}

/*  Regresa una matiz de adyacencia de (grafo->orden)x(grafo->orden) almacenada dinamicamente cuyos
    ejes estan ordenados de acuerdo a el orden en el que los vertices fueron insertados en el grafo.
    La matriz contine la direccion de memoria a un dato tipo peso_t en cada celda de la matriz. El
    valor de cada celda esta determinado por el resultado de la funcion grafo->calc_peso() sobre la
    arista correspondiente a cada posicion. Todo acceso a la matriz de hacerse mediante la MACRO
    GD_MATRIZ_INDEX(matriz, i, j). La memoria reservada para la matriz debe de ser liberada mediante
    una llamada a la funcion free() Esta matriz NO TOMA EN CUENTA varias aristas entre los mismos
    vertices (multigrafos), tomando por defecto la primera arista encontrada
*/
static MatrizAdy_P* grafo_d_generar_matriz_pesos(const Grafo_D* grafo) {
    MatrizAdy_P* matriz = (MatrizAdy_P*)malloc_fam(
        MatrizAdy_P,peso_t , grafo->orden*grafo->orden);
    if(!matriz) return NULL;
    matriz->orden=grafo->orden;
    struct _nodo_v* ini=grafo->lista_ady;
    for(int i=0; i<grafo->orden; ++i, ini=ini->sig) {
        struct _nodo_v* fin=grafo->lista_ady;
        for(int j=0; j<grafo->orden; ++j, fin=fin->sig) {
            peso_t* ptr_celda=(matriz->datos)+i*grafo->orden+j;
            struct _nodo_a* aptr=ini->lista_ady;
            *ptr_celda=PESO_NO_ARISTA;
            while(aptr!=NULL) {
                if(fin==aptr->fin) { 
                    *ptr_celda=grafo->calc_peso(grafo,&aptr->ar);
                    break;
                }
                aptr=aptr->sig;
            }
        }
    }
    return matriz;
}

/*------------------------------Operaciones de busqueda de Caminos--------------------------------*/
//  !!!ESTRUCTURA DE USO INTERNO!!!
struct _nodo_c {
    struct _nodo_c* sig;
    struct _nodo_v* vt_actual;
    struct _nodo_a* ar_puente;
    struct _nodo_c* nd_padre;
    peso_t dist_orig;
};

/*  !!!FUNCION DE USO INTERNO!!!
    Busca en la lista de Nodos_C el Nodo_C que hace referencia a el
    struct _nodo_v pasado como segundo argumento.
*/
static struct _nodo_c* _get_nodo_c_vertice(struct _nodo_c* cptr, struct _nodo_v* vt) {
    while(cptr!=NULL) {
        if(cptr->vt_actual==vt) return cptr;
        cptr=cptr->sig;
    }
    return NULL;
}

/*  !!!FUNCION DE USO INTERNO!!!
    Busca en la lista de Nodos_C el Nodo_C con el valor de dist_orig minimo 
    (y finito) en toda la lista.
*/
static struct _nodo_c* _get_nodo_c_minimo(struct _nodo_c* cptr) {
    struct _nodo_c* minimo = cptr;
    while(cptr!=NULL) {
        if(cptr->dist_orig < minimo->dist_orig)
            minimo=cptr;
        cptr=cptr->sig;
    }
    if(minimo->dist_orig!=PESO_NO_ARISTA)
        return minimo;
    return NULL;
}

/*  !!!FUNCION DE USO INTERNO!!!
    Libera el espacio de memoria de la lista de Nodos_C apuntada por
    el puntero cptr. cptr debe ser la cabeza de la lista para evitar
    perdida de memoria
*/
static void _liberar_lista_c(struct _nodo_c* cptr) {
    struct _nodo_c* ctmp;
    while(cptr!=NULL) {
        ctmp=cptr;
        cptr=cptr->sig;
        free(ctmp);
    }
    return;
}

typedef struct camino_d {
    Vertice** vts;
    Arista** ars;
    size_t saltos;
    peso_t longitud;
} Camino_D;

/*  !!!FUNCION DE USO INTERNO!!!
    Reserva memoria contigua para un Camino_D para que la estructura completa
    pueda ser liberada mediante un solo llamada a free()
*/
static inline Camino_D* _camino_d_alloc(size_t saltos) {
    Camino_D* camino = (Camino_D*)malloc(
        sizeof(Camino_D)+
        sizeof(Vertice**)*(saltos+1)+
        sizeof(Arista**)*saltos);
    if(!camino) return NULL;
    camino->vts=(Vertice**)((char*)camino+sizeof(Camino_D));
    camino->ars=(Arista**)((char*)camino+sizeof(Camino_D)+sizeof(Vertice**)*(saltos+1));
    return camino;
}

/*  Crea un camino nulo que representa la ausencia de un camino entre dos vertices.
    La memoria debe ser liberada manualmente mediante una llamada a free()
*/
static Camino_D* camino_d_crear_nulo(void) {
    Camino_D* camino = (Camino_D*)malloc(sizeof(Camino_D));
    if(!camino) return NULL;
    camino->vts=NULL;
    camino->ars=NULL;
    camino->saltos=0;
    camino->longitud=PESO_NO_ARISTA;
    return camino;
}

/*  Crea un camino trivial que solo contiene el vertice indicado. La memoria del
    debe ser liberada manualmente mediante una llamada a free()
*/
static Camino_D* camino_d_crear_trivial(const Vertice* vt) {
    Camino_D* camino = _camino_d_alloc(0);
    if(!camino) return NULL;
    camino->vts[0]=(Vertice*)vt;
    camino->saltos=0;
    camino->longitud=0;
    return camino;
}

/*  Regresa si un camino en particular es un camino nulo*/
static inline bool camino_d_es_nulo(const Camino_D* camino) {
    return  camino->vts==NULL   &&
            camino->ars==NULL   &&
            camino->saltos==0   &&
            camino->longitud==PESO_NO_ARISTA;
}

/*  Regresa el primero vertice del camino no nulo 'camino'*/
static inline Vertice* camino_d_get_inicio(const Camino_D* camino) {
    return camino->vts[0];
}

/*  Regresa el ultimo vertice del camino no nulo 'camino'*/
static inline Vertice* camino_d_get_fin(const Camino_D* camino) {
    return camino->vts[camino->saltos];
}

/*  Regresa el subcamino culla cantidad de saltos esta dada por 'indice'
    es decir regresa un camino conformado por los primeros 'indice'+1 vertices
    del camino original*/
static Camino_D* camino_d_recortar(const Camino_D* camino, size_t indice) {
    Camino_D* subcamino = _camino_d_alloc(indice);
    if(!subcamino) return NULL;
    subcamino->vts[0]=camino->vts[0];
    for(int i=0; i<indice; ++i) {
        subcamino->vts[i+1]=camino->vts[i+1];
        subcamino->ars[i]=camino->ars[i];
    }
    return subcamino;
}

/*  Version de camino_d_recotar que regresa la version recortada de camino y se encarga
    de liberar la memoria utilizada por camino para hacer posible asignaciones como
    camino = camino_d_frecortar(camino, i) sin filtrar memoria
*/
static inline Camino_D* camino_d_frecortar(Camino_D* camino, size_t indice) {
    Camino_D* tmp = camino_d_recortar(camino, indice); free(camino);
    return tmp; 
}

/*  Regreasa un nuevo camino conformado por los contenidos de c1 concatenados a los
    contenidos de c2. Para concatenar los caminos exitosamente, ambos no deben ser
    nulos y c1 debe terminar en el mismo vertice en el que c2 empieza. De lo
    contrario, se devolvera un camino nulo. 
*/
static Camino_D* camino_d_concatenar(const Camino_D* c1, const Camino_D* c2) {
    if(camino_d_es_nulo(c1) || camino_d_es_nulo(c2) || c1->vts[c1->saltos]!=c2->vts[0])
        return camino_d_crear_nulo(); 
    Camino_D* camino = _camino_d_alloc(c1->saltos+c2->saltos);
    if(!camino) return NULL;
    camino->saltos=c1->saltos+c2->saltos;
    camino->longitud=c1->longitud+c2->longitud;
    camino->vts[0]=c1->vts[0];
    int i,j;
    for(i=0; i<c1->saltos; ++i) {
        camino->vts[i+1]=c1->vts[i+1];
        camino->ars[i]=c1->ars[i];
    }
    for(j=0; j<c2->saltos; ++j) {
        camino->vts[j+i+1]=c2->vts[j+1];
        camino->ars[j+i]=c2->ars[j];
    }
    return camino;
}

/*  Version de camino_d_concatenar que la version concatenada de c1 y c2 y se encarga
    de liberar la memoria de ambos para hacer posibles asignaciones como
    camino = camino_d_fconcatenar(camino1, camino2) sin filtrar memoria
*/
static inline Camino_D* camino_d_fconcatenar(Camino_D* c1, Camino_D* c2) {
    Camino_D* tmp = camino_d_concatenar(c1, c2); free(c1); free(c2);
    return tmp;
}

/*  !!!FUNCION DE USO INTERNO!!!!
    Construye un Camino_D en base a la infomacion recolectada durante la ejecucion
    de el algorimo de dijsktra. Se asume que nodo_fin es el nodo correspondiente a
    un vertice que ya ha sido encontrado
*/
static inline Camino_D* _dijkstra_constuir_camino(const struct _nodo_c* nodo_fin) {
    size_t saltos=0;
    const struct _nodo_c* cptr=nodo_fin;
    while(cptr->nd_padre!=NULL) {
        ++saltos;
        cptr=cptr->nd_padre;
    }

    Camino_D* camino = _camino_d_alloc(saltos);
    if(!camino) return NULL;
    camino->saltos=saltos;
    camino->longitud=nodo_fin->dist_orig;
    camino->vts[0]=&cptr->vt_actual->vt;
    
    cptr=nodo_fin;
    for(size_t i=camino->saltos; i>0; --i) {
        camino->vts[i]=&cptr->vt_actual->vt;
        camino->ars[i-1]=&cptr->ar_puente->ar;
        cptr=cptr->nd_padre;
    }

    return camino;
}

/*  Encuentra el camino mas corto entre el vertice ini y fin utilizando el algoritmo
    de Dijkstra. El camino se regresa como un struct tipo Camino_D dinamicamente almacenado
    en memoria y por lo tanto debera de liberarse utilizando la funcion camino_d_destruir.
    En caso de error la funcion regresa NULL. En caso de que no exista ningun camino entre
    el los vertice ini y fin, la funcion regresa un camino invalido, no NULL, e igualmente
    debera ser liberado usando camino_d_destruir. 
*/
static Camino_D* grafo_d_dijkstra_unico(const Grafo_D* grafo, const Vertice* ini, const Vertice* fin) {

    struct _nodo_v* vptr; struct _nodo_a* aptr; struct _nodo_c* cptr;
    struct _nodo_c* visitados=NULL;
    struct _nodo_c* no_visitados=NULL;
    vptr=grafo->lista_ady;
    //Inicializamos listas de visitados y no visitados
    while(vptr!=NULL) {
        cptr=(struct _nodo_c*)malloc(sizeof(struct _nodo_c));
        if(!cptr) {
            _liberar_lista_c(visitados);
            _liberar_lista_c(no_visitados);
            return NULL;
        }
        if(ini!=&vptr->vt) {
            cptr->sig=no_visitados;
            cptr->vt_actual=vptr;
            cptr->ar_puente=NULL;
            cptr->nd_padre=NULL;
            cptr->dist_orig=PESO_NO_ARISTA;
            no_visitados=cptr;
        }
        else {
            cptr->sig=NULL;
            cptr->vt_actual=vptr;
            cptr->ar_puente=NULL;
            cptr->nd_padre=NULL;
            cptr->dist_orig=0;
            visitados=cptr;
        }
        vptr=vptr->sig;
    }

    /*----------------Parte Iterativa----------------
        Ejecutamos Dijkstra hasta encontrar el camino
        mas corto hasta el vertice fin */
    struct _nodo_c* nodo_ref = visitados;
    while(fin!=&nodo_ref->vt_actual->vt) {

        //Para cada arista de salida del vertice
        aptr = nodo_ref->vt_actual->lista_ady;
        while(aptr!=NULL) {
            struct _nodo_c* nodo_fin = _get_nodo_c_vertice(no_visitados, aptr->fin);
            if(nodo_fin!=NULL) {
                peso_t dp=nodo_ref->dist_orig+grafo->calc_peso(grafo,&aptr->ar);
                if(dp < nodo_fin->dist_orig) {
                    nodo_fin->dist_orig = dp;
                    nodo_fin->nd_padre  = nodo_ref;
                    nodo_fin->ar_puente = aptr;
                }
            }
            aptr=aptr->sig;
        }

        //Acualizar nodo_ref
        nodo_ref = _get_nodo_c_minimo(no_visitados);

        //Si no existen vertices alcanzables regresamos un camino nulo
        if(nodo_ref==NULL) {
            _liberar_lista_c(visitados);
            _liberar_lista_c(no_visitados);
            return camino_d_crear_nulo();
        };

        //Pasar nuevo nodo_ref de no_visitados a visitados
        if(nodo_ref==no_visitados) {
            no_visitados=no_visitados->sig;
            nodo_ref->sig=visitados;
            visitados=nodo_ref;
        }
        else {
            cptr=no_visitados;
            while(cptr->sig!=nodo_ref)
                cptr=cptr->sig;
            cptr->sig=nodo_ref->sig;
            nodo_ref->sig=visitados;
            visitados=nodo_ref;
        }
    }
    _liberar_lista_c(no_visitados);
    Camino_D* camino = _dijkstra_constuir_camino(nodo_ref);
    if(!camino) {
        _liberar_lista_c(visitados);
        return NULL;
    }
    _liberar_lista_c(visitados);
    return camino;
}

typedef struct vect_c{
    size_t tamano;
    Camino_D* caminos[];
} Vect_C;

static void vect_c_destruir(Vect_C* vector) {
    for(int i=0; i<vector->tamano; ++i) {
        if(vector->caminos[i]!=NULL)
            free(vector->caminos[i]);
    }
    free(vector);
} 

static bool _vect_v_contiene_vt(Vect_V* vector, const Vertice* vt) {
    for(int i=0; i<vector->tamano; ++i)
        if(vt==vector->vertices[i]) return true;
    return false;
}

static bool _vect_c_esta_lleno(Vect_C* vector) {
    for(int i=0; i<vector->tamano; ++i)
        if(vector->caminos[i]==NULL) return false;
    return true;
}


/*  Encuentra los caminos mas cortos entre ini y cada vertice elemento del vector
    finales. El orden de los caminos entre ini y finales[i] esta dado en orden 
    acendente de menor longitud a mayor longiud. La estructura Vect_C regresada
    por esta funcion debe ser liberada mediante un llamado a vect_c_destruir()
*/
static Vect_C* grafo_d_dijkstra_multiple(const Grafo_D* grafo,
    const Vertice* ini, Vect_V* finales) {

    Vect_C* vector = (Vect_C*)malloc_fam(Vect_C, Camino_D*, finales->tamano);
    if(!vector) return NULL;
    vector->tamano = finales->tamano;
    memset(vector->caminos, 0, sizeof(Camino_D*)*vector->tamano);

    struct _nodo_v* vptr; struct _nodo_a* aptr; struct _nodo_c* cptr;
    struct _nodo_c* visitados=NULL;
    struct _nodo_c* no_visitados=NULL;
    vptr=grafo->lista_ady;
    //Inicializamos listas de visitados y no visitados
    while(vptr!=NULL) {
        cptr=(struct _nodo_c*)malloc(sizeof(struct _nodo_c));
        if(!cptr) {
            free(vector);
            _liberar_lista_c(visitados);
            _liberar_lista_c(no_visitados);
            return NULL;
        }
        if(ini!=&vptr->vt) {
            cptr->sig=no_visitados;
            cptr->vt_actual=vptr;
            cptr->ar_puente=NULL;
            cptr->nd_padre=NULL;
            cptr->dist_orig=PESO_NO_ARISTA;
            no_visitados=cptr;
        }
        else {
            cptr->sig=NULL;
            cptr->vt_actual=vptr;
            cptr->ar_puente=NULL;
            cptr->nd_padre=NULL;
            cptr->dist_orig=0;
            visitados=cptr;
        }
        vptr=vptr->sig;
    }

    /*----------------Parte Iterativa----------------
        Ejecutamos Dijkstra hasta encontrar el camino
        para todos los vertices en el vector fin*/
    size_t i=0;
    struct _nodo_c* nodo_ref = visitados;
    while(true) {
        /*Si el vertice que se encontro esta en la lista de finales
        consturimos su camino y lo agremos al vector*/
        if(_vect_v_contiene_vt(finales, &nodo_ref->vt_actual->vt)) {
            Camino_D* camino = _dijkstra_constuir_camino(nodo_ref);
            if(!camino) {
                vect_c_destruir(vector);
                _liberar_lista_c(visitados);
                _liberar_lista_c(no_visitados);
                return NULL;
            }
            vector->caminos[i]=camino;
            ++i;
        }
        /*Si ya encontramos todos los caminos requeridos, salimos*/
        if(_vect_c_esta_lleno(vector)) {
            _liberar_lista_c(visitados);
            _liberar_lista_c(no_visitados);
            return vector;
        }

        //Para cada arista de salida del vertice
        aptr = nodo_ref->vt_actual->lista_ady;
        while(aptr!=NULL) {
            struct _nodo_c* nodo_fin = _get_nodo_c_vertice(no_visitados, aptr->fin);
            if(nodo_fin!=NULL) {
                peso_t dp=nodo_ref->dist_orig+grafo->calc_peso(grafo,&(aptr->ar));
                if(dp < nodo_fin->dist_orig) {
                    nodo_fin->dist_orig = dp;
                    nodo_fin->nd_padre  = nodo_ref;
                    nodo_fin->ar_puente = aptr;
                }
            }
            aptr=aptr->sig;
        }

        //Acualizar nodo_ref
        nodo_ref = _get_nodo_c_minimo(no_visitados);

        /*Si no existen vertices alcanzables llenamos los
        camninos no encontrados con caminos nulos y regresamos*/
        if(nodo_ref==NULL) {
            _liberar_lista_c(visitados);
            _liberar_lista_c(no_visitados);
            for(; i<vector->tamano; ++i) {
                vector->caminos[i]=camino_d_crear_nulo();
                if(vector->caminos[i]==NULL) {
                    vect_c_destruir(vector);
                    return NULL;
                }
            }
            return vector;
        };

        //Pasar nuevo nodo_ref de no_visitados a visitados
        if(nodo_ref==no_visitados) {
            no_visitados=no_visitados->sig;
            nodo_ref->sig=visitados;
            visitados=nodo_ref;
        }
        else {
            cptr=no_visitados;
            while(cptr->sig!=nodo_ref)
                cptr=cptr->sig;
            cptr->sig=nodo_ref->sig;
            nodo_ref->sig=visitados;
            visitados=nodo_ref;
        }
    }
}

/*-------------------------------Operaciones de Ordenacion---------------------------------*/

typedef enum {
    ANTES,
    DESPUES
} orden_t;

/*  Ordena los vertices en la lista de adyacencia del grafo de acuerdo a la funcion
    proporcionada como segundo argumento. La funcion orden debe regresar la posicion de el
    primer vertice con respecto al segundo en terminos de el enum orden_t (ANTES, DESPUES)
*/
static void grafo_d_ordenar_vertices(Grafo_D* grafo, orden_t (*orden)(Vertice*, Vertice*)) { 
    struct _nodo_v* lista_ordenada = NULL;
    while(grafo->lista_ady!=NULL) { 
        struct _nodo_v* vptr=grafo->lista_ady;
        Vertice* ultimo=&vptr->vt;
        struct _nodo_v* prev_ultimo=NULL;
        while(vptr->sig!=NULL) {
            if(orden(&vptr->sig->vt,ultimo)==DESPUES) {
                ultimo=&vptr->sig->vt;
                prev_ultimo=vptr;
            }
            vptr=vptr->sig;
        }
        if(prev_ultimo==NULL) {
            vptr=grafo->lista_ady;
            grafo->lista_ady=vptr->sig;
            vptr->sig=lista_ordenada;
            lista_ordenada=vptr;
        }
        else {
            vptr=prev_ultimo->sig;
            prev_ultimo->sig=vptr->sig;
            vptr->sig=lista_ordenada;
            lista_ordenada=vptr;
        }
    }
    grafo->lista_ady=lista_ordenada;
}



/*  !!!FUNCION DE USO INTERNO!!!
    Ordena la lista de ayacencia del struct _nodo_v pasado como primer argumento de acuerdo a la funcion
    proporcionada como segundo argumento. La funcion orden debe regresar la posicion de el
    primer vertice con respecto al segundo en terminos de el enum orden_t (ANTES, DESPUES)
*/
static void _grafo_d_ordenar_aristas(struct _nodo_v* nodo, orden_t (*orden)(Arista*, Arista*)) {
    struct _nodo_a* lista_ordenada = NULL;
    while(nodo->lista_ady!=NULL) {
        struct _nodo_a* aptr=nodo->lista_ady;
        Arista* ultimo=&aptr->ar;
        struct _nodo_a* prev_ultimo=NULL;
        while(aptr->sig!=NULL) {
            if(orden(&aptr->sig->ar,ultimo)==DESPUES) {
                ultimo=&aptr->sig->ar;
                prev_ultimo=aptr;
            }
            aptr=aptr->sig;
        }
        if(prev_ultimo==NULL) {
            aptr=nodo->lista_ady;
            nodo->lista_ady=aptr->sig;
            aptr->sig=lista_ordenada;
            lista_ordenada=aptr;
        }
        else {
            aptr=prev_ultimo->sig;
            prev_ultimo->sig=aptr->sig;
            aptr->sig=lista_ordenada;
            lista_ordenada=aptr;
        }
    }
    nodo->lista_ady=lista_ordenada;
}



/*  Ordena toda la represetacion interna del grafo de acuerdo a las dos funciones
    proporcionadas como argumentos. Cada funcion orden debe regresar la posicion de el
    primer vertice/arista con respecto al segundo en terminos de el enum orden_t (ANTES, DESPUES)
*/
static void grafo_d_ordenar(Grafo_D* grafo,
    orden_t (*orden_vt)(Vertice*,Vertice*), orden_t  (*orden_ar)(Arista*, Arista*)) {
    
    grafo_d_ordenar_vertices(grafo, orden_vt);
    struct _nodo_v* vptr=grafo->lista_ady;
    while(vptr!=NULL) {
        _grafo_d_ordenar_aristas(vptr, orden_ar);
        vptr=vptr->sig;
    }
    return;
}



/*------------------------------Operaciones de Representacion--------------------------*/

/*  Imprime una representacion cruda del grafo en su forma de lista de adyacencia
    Los vertices y aristas del grafo estan identificados por su direccion de memoria
    el cual es unico para cada vertice/arista.
*/
static void grafo_d_fprint_debug(const Grafo_D* grafo, FILE* salida) {
    fprintf(salida, "G: %p | orden:%lu, tamano:%lu\n",
        grafo, grafo->orden, grafo->tamano);
    struct _nodo_v* vptr=grafo->lista_ady;
    while(vptr!=NULL) {
        fprintf(salida, "*V:%p", &vptr->vt);
        struct _nodo_a* aptr=vptr->lista_ady;
        while(aptr!=NULL) {
            fprintf(salida, " -> A:%p", &aptr->ar);
            aptr=aptr->sig;
        }
        putc('\n', salida);
        vptr=vptr->sig;
    }
}
static inline void grafo_d_print_debug(const Grafo_D* grafo)
{grafo_d_fprint_debug(grafo, stdout);}



/*  Imprime la lista de adyacencia de el grafo pasado como primer argumeto. Se debe suministrar
    una funcion responsable de imprimir la representacion de cada vertice del grafo como
    segundo argumento. Es necesario que la funcion imprima los datos de cada vertice en una
    sola linea para garantizar un formateo correcto*/
static void grafo_d_fprint_lista_ady(
    const Grafo_D* grafo,
    void (*print_vt)(Vertice*, FILE*),
    FILE* salida)
{
    
    fprintf(salida, "Grafo | orden:%lu, tamano:%lu\n",
        grafo->orden, grafo->tamano);
    struct _nodo_v* vptr=grafo->lista_ady;
    while(vptr!=NULL) {
        fputs("*[", salida);
        print_vt(&vptr->vt, salida);
        putc(']', salida);
        struct _nodo_a* aptr=vptr->lista_ady;
        while(aptr!=NULL) {
            fputs(" -> (", salida);
            print_vt(&aptr->fin->vt, salida);
            putc(')', salida);
            aptr=aptr->sig;
        }
        putc('\n', salida);
        vptr=vptr->sig;
    }
}
static inline void grafo_d_print_lista_ady(
    const Grafo_D* grafo,
    void (*print_vt)(Vertice*, FILE*))
{grafo_d_fprint_lista_ady(grafo, print_vt, stdout);}



/*  Imprime la lista de adyacencia de el grafo ponderado pasado como primer argumeto.
    Se debe suministrar una funcion responsable de imprimir la representacide cada vertice del 
    grafo como segundo argumento y otra funcion responsable de imprimir el peso de cada arista
    como tercer argumento. Es necesario que la funcion imprima los datos de los vertices y pesos 
    en una sola linea para garantizar un formateo correcto. El peso del grafo sera calculado a
    partir de la funcion suministrada mediante grafo_d_set_calc_peso()*/
static void grafo_d_fprint_lista_ady_pond(
    const Grafo_D* grafo,
    void (*print_vt)(Vertice*, FILE*),
    void (*print_peso)(peso_t, FILE*),
    FILE* salida) {

    fprintf(salida, "Grafo | orden:%lu, tamano:%lu\n",
        grafo->orden, grafo->tamano);
    struct _nodo_v* vptr=grafo->lista_ady;
    while(vptr!=NULL) {
        fputs("*[", salida);
        print_vt(&vptr->vt, salida);
        putc(']', salida);
        struct _nodo_a* aptr=vptr->lista_ady;
        while(aptr!=NULL) {
            fputs(" -> (w:", salida);
            print_peso(grafo->calc_peso(grafo,&aptr->ar), salida);
            fputs(",v:", salida);
            print_vt(&aptr->fin->vt, salida);
            putc(')', salida);
            aptr=aptr->sig;
        }
        putc('\n', salida);
        vptr=vptr->sig;
    }
}
static inline void grafo_d_print_lista_ady_pond(
    const Grafo_D* grafo,
    void (*print_vt)(Vertice*, FILE*),
    void (*print_peso)(peso_t, FILE*))
{grafo_d_fprint_lista_ady_pond(grafo, print_vt, print_peso, stdout);}



static void grafo_d_generar_gv(
    const Grafo_D* grafo,
    void (*print_vt)(Vertice*, FILE*),
    FILE* salida)
{
    fputs("digraph G {\n", salida);
    struct _nodo_v* vptr=grafo->lista_ady;
    while(vptr!=NULL) {
        fprintf(salida, "%ld[label=\"",
            (size_t)&vptr->vt);
        print_vt(&vptr->vt, salida);
        fputs("\"]\n", salida);
        vptr=vptr->sig; 
    }
    if(grafo->tamano!=0)
        putc('\n', salida);
    vptr=grafo->lista_ady;
    while(vptr!=NULL) {
        struct _nodo_a* aptr=vptr->lista_ady;
        while(aptr!=NULL) {
            fprintf(salida, "%ld->%ld\n",
            (size_t)&vptr->vt,
            (size_t)&aptr->fin->vt);
            aptr=aptr->sig;
        }
        vptr=vptr->sig;
    }
    putc('}', salida);
}

#endif