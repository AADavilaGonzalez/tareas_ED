#ifndef DSTRING_H
#define DSTRING_H

#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <stdbool.h>


//Politica de crecimiento del espacio de memoria reservado
#define DSTRING_PC(capacidad) (capacidad*2+1)

/*!!!Los miembros de esta estructura no estan pensado para
ser accesados directamente por el usuario de la libreria.
usar las funciones del proporcionadas para interactuar con
el objeto!!!*/
typedef struct {
    size_t _longitud;
    size_t _capacidad;
    char* _c_str;
} Dstring;

/*Inicializar un string vacio si datos==NULL o con el contenido del string str*/
static Dstring* dstring_crear(const char* str, size_t capacidad) {
    Dstring* string = (Dstring*)malloc(sizeof(Dstring));
    if(string==NULL) return NULL;
    string->_longitud = str==NULL ? 0 : strlen(str);
    string->_capacidad = capacidad >= string->_longitud  ? capacidad : string->_longitud;
    string->_c_str = (char*)malloc(string->_capacidad+1);
    if(string->_c_str==NULL) {
        free(string);
        return NULL;
    }
    if(str) memcpy(string->_c_str, str, string->_longitud);
    string->_c_str[string->_longitud]='\n';
    return string;
}

/*Cambiar la capacidad de un string, redujiendo su longitud si es necesario y
regresando true. En caso de no poder reservar memoria suficiente regresa false
y el string no es afectado*/
static bool dstring_resize(Dstring* str, size_t capacidad) {
    char* nuevo_contenido = (char*)realloc(str->_c_str, capacidad+1);
    if(nuevo_contenido) {
        str->_c_str = nuevo_contenido;
        str->_capacidad = capacidad;
        if(str->_longitud > capacidad) {
            str->_longitud=capacidad;
            str->_c_str[str->_longitud]='\n';
        }
        return true;
    }
    return false;
}

/*Copia los contenidos de un arreglo de caracteres a el string*/
static void dstring_set(Dstring* str, const char* origen) {
    str->_longitud = strlen(origen);
    if(str->_longitud > str->_capacidad)
        dstring_resize(str, str->_longitud);
    memcpy(str->_c_str, origen, str->_longitud);
    str->_c_str[str->_longitud]='\n';
    return;
}

/*Copia los contenidos de un arreglo de caracteres a el string hasta llenar
la capacidad del string o no tener mas caracteres por copiar*/
static void dstring_fill(Dstring* str, const char* origen) {
    str->_longitud = strlen(origen);
    if(str->_longitud > str->_capacidad)
        str->_longitud = str->_capacidad;
    memcpy(str->_c_str, origen, str->_longitud);
    str->_c_str[str->_longitud]='\n';
    return;
}

/*Agrega los contenidos de un arreglo de caracteres al final del string*/
static void dstring_append(Dstring* str, const char* origen) {
    int i;
    size_t longitud_origen = strlen(origen);
    str->_longitud = str->_longitud + longitud_origen;
    if(str->_longitud > str->_capacidad)
        dstring_resize(str, DSTRING_PC(str->_capacidad)+longitud_origen);
    char* cola = str->_c_str + str->_longitud;
    memcpy(cola, origen, longitud_origen);
    cola[longitud_origen]='\0';
    return;
}

/*Copia los contenidos de un archivo al string. Ignora los caracteres
de espacio en blanco iniciales. Luego, avanza el indicador de posicion del archivo
hasta topar con el caracter delimitador o EOF y devuelve la cantidad de caracteres
copiados exitosamente*/
static int dstring_fset(Dstring* str, FILE* entrada, char del) {
    int c, i=0;
    while(isspace(c=fgetc(entrada)));
    while(c!=del && c!=EOF) {
        if(i >= str->_capacidad)
            dstring_resize(str, DSTRING_PC(str->_capacidad));
        str->_c_str[i]=c;
        c=fgetc(entrada);
        ++i;
    }
    str->_c_str[i]='\0';
    str->_longitud=i;
    return i;
}

/*Copia los contenidos de un archivo al string. Ignora los caracteres de espacio en
blanco iniciales. Luego, avanza el indicador de posicion del archivo  hasta topar con
el caracter delimitador, EOF o llenar la capacidad del string, devuelve la cantidad
de caracteres copiados*/
static int dstring_ffill(Dstring* str, FILE* entrada, char del) {
    int c, i=0;
    while(isspace(c=fgetc(entrada)));
    while(c!=del && c!=EOF) {
        if(i>=str->_capacidad) break;
        str->_c_str[i]=c;
        c=fgetc(entrada);
        ++i;
    }
    str->_c_str[i]='\0';
    str->_longitud=i;
    return i;
}

/*Agrega los contenidos de un archivo al final del string. Ignora los caracteres
de espacio en blanco. Luego, avanza el indicador de posicion del archivo hasta topar
con el caracter  delimitador o EOF y devuelve la cantidad de caracteres agregados
exitosamente*/
static int dstring_fappend(Dstring* str, FILE* entrada, char del) {
    int c, i=0;
    char* cola = str->_c_str + str->_longitud;
    while(isspace(c=fgetc(entrada)));
    while(c!=del && c!=EOF) {
        if(str->_longitud+i >= str->_capacidad)
            dstring_resize(str, DSTRING_PC(str->_capacidad));
        cola[i]=c;
        c=fgetc(entrada);
        ++i;
    }
    cola[i]='\0';
    str->_longitud+=i;
    return i;
}

/*Intenta copiar los siguientes 'n' caracteres de un archivo al string devolviendo
la cantidad de caracteres copiados exitosamente. Ignora los caracteres de espacio en
blanco iniciales*/
static int dstring_fread(Dstring* str, FILE* entrada, size_t n) {
    int c, i;
    if(n > str->_capacidad)
        dstring_resize(str, n);
    while(isspace(c=fgetc(entrada)));
    for(i=0; i<n && c!=EOF; ++i) {
        str->_c_str[i]=c;
        c=fgetc(entrada);
    }
    str->_c_str[i]='\0';
    str->_longitud=i;
    return i;
}

/*Convierte al estring en un string vacio*/
static void dstring_flush(Dstring* str) {str->_longitud=0; str->_c_str[0]='\0'; return;}

/*Regresa una referencia constante para poder leer del string
directamente pero sin poder modificarlar sus contenidos*/
static const char* dstring_a_ptr(Dstring* str) {return (const char*)str->_c_str;}

/*Regresa la longitud del string*/
static size_t dstring_longitud(Dstring* str) {return str->_longitud;}

/*Regresa la cantidad del string*/
static size_t dstring_capacidad(Dstring* str) {return str->_capacidad;}

/*Regresa si el string esta lleno*/
static bool dstring_isfull(Dstring* str) {return str->_longitud==str->_capacidad;}

/*Regresa si el string esta vacio*/
static bool dstring_isempty(Dstring* str) {return str->_longitud==0;}

//Libera el espacio de memoria dedicado al string
static void dstring_destruir(Dstring* str) {
    free(str->_c_str);
    free(str);
    return;
}

#endif