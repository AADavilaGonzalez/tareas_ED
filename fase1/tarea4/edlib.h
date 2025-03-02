#ifndef _EDLIB_H
#define _EDLIB_H

#include <stdlib.h>
#include <stdio.h>
#include <limits.h>
#include <float.h>
#include <ctype.h>
#include <stdbool.h>
#include <string.h>

/*  -------------------------------CONFIGURACION------------------------------
    Las Siguientes MACROS seran definidas para configurar la libreria:
    |
    * EDLIB_MAIN(REQUERIDO): Decide la unidad de traduccion donde se almacena
    |   el estado global de la libreria
    |   default: SIN DEFINIR  
    |
    * EDLIB_RESETEAR_ERROR(opcional): Decide si los mensajes de error seteados
    |   por edlib_set_msj_error() seran reseteados tras cada llamada a las
    |   funciones que usan esta caracteristica de la libreria
    |   default: DEFINIDO
    |
    * EDLIB_SALIDA_ERROR(opcional): Asocia un flujo para la salida de los
    |   mensajes de error
    |   default: DEFINIDO COMO 'stdout'
*/

#define EDLIB_RESETEAR_ERROR
#define EDLIB_SALIDA_ERROR stdout

/*Esta MACRO debe ser definida en solo un unidad de traduccion (archivo .c)
para que estas variables formen parte del estado de esa unidad y las demas
unidades importen las variables desde la unida principal*/
#ifdef EDLIB_MAIN
    char _edlib_msj_error[256]="";
    char _edlib_prompt[16]="> ";
#else
    extern char _edlib_msj_error[256];
    extern char _edlib_prompt[16];
#endif

#define max(a,b) ((a)>(b) ? (a):(b))
#define min(a,b) ((a)<(b) ? (a):(b))
#define en_rango(val, min, max) ((val) >= (min) && (val) <= (max))
#define char_a_int(c) ((int)(c-'0'))

static inline bool edlib_set_msj_error(const char* str) {
    size_t longitud = strlen(str);
    if(longitud > sizeof(_edlib_msj_error)-1) {
        strncpy(_edlib_msj_error, str, sizeof(_edlib_msj_error)-1);
        _edlib_msj_error[sizeof(_edlib_msj_error)-1]='\0';
        return false;
    }
    strcpy(_edlib_msj_error, str);
    return true;
}

static inline const char* edlib_get_msj_error(void) {
    return (const char*)_edlib_msj_error;
}

static inline void edlib_print_msj_error(void) {
    if(_edlib_msj_error[0]!='\0') {
        fputs(_edlib_msj_error, EDLIB_SALIDA_ERROR);
        fputc('\n', EDLIB_SALIDA_ERROR);
    }
    return;
}
#define edlib_msj_error edlib_print_msj_error()

static inline bool edlib_set_prompt(const char* str) {
    size_t longitud = strlen(str);
    if(longitud > sizeof(_edlib_prompt)-1) {
        strncpy(_edlib_prompt, str, sizeof(_edlib_prompt)-1);
        _edlib_prompt[sizeof(_edlib_prompt)-1]='\0';
        return false;
    }
    strcpy(_edlib_prompt, str);
    return true;
}

static inline const char* edlib_get_prompt(void) {
    return (const char*)_edlib_prompt;
}

static inline void edlib_print_prompt(void) {
    fputs(_edlib_prompt, stdout);
    return;
}
#define edlib_prompt edlib_print_prompt()

static inline void clear(void) {
    #ifdef _WIN32
    system("cls");
    #else
    system("clear");
    #endif
    return;
}

static inline void leer_hasta(char delimitador, FILE* flujo) {
    int c; while((c=fgetc(flujo))!=delimitador && c!=EOF);
    return;
}

#define flush() (\
    leer_hasta('\n', stdin))

static inline bool caracter_en_string(char* str, char c) {
    while(*str!='\0') {
        if(*str==c) return true;
        ++str;
    }
    return false;
}

static long long validar_int_en_rango(long long min, long long max) {
    char buffer[32], *ptr;
    int c; long long num;
    while(true) {
        edlib_prompt;
        while(isspace(c=fgetc(stdin)) && c!='\n' && c!=EOF);
        if(!isdigit(c) && c!='+' && c!='-') {
            if(c==EOF) return (min/2+max/2);
            if(c!='\n') flush();
            edlib_msj_error;
            continue;
        }
        ungetc(c, stdin);
        if(!fgets(buffer, sizeof(buffer), stdin)) return (min/2+max/2);
        if(!caracter_en_string(buffer, '\n')) flush();
        num = strtoll(buffer, &ptr, 10);
        if(ptr!=buffer && isspace(*ptr) && en_rango(num, min, max)) break;
        edlib_msj_error;
    }
    #ifdef EDLIB_RESETEAR_ERROR
    edlib_set_msj_error("");
    #endif
    return num;
}

#define validar_int() (\
    validar_int_en_rango(LLONG_MIN, LLONG_MAX))

#define validar_int_min(min) (\
    validar_int_en_rango(min, LLONG_MAX))

#define validar_int_max(max) (\
    validar_int_en_rango(LLONG_MIN, max))

static unsigned long long validar_uint_en_rango( unsigned long long min, unsigned long long max) {
    char buffer[32], *ptr;
    int c; unsigned long long num;
    while(true) {
        edlib_prompt;
        while(isspace(c=fgetc(stdin)) && c!='\n' && c!=EOF);
        if(!isdigit(c) && c!='+') {
            if(c==EOF) return (min/2+max/2);
            if(c!='\n') flush();
            edlib_msj_error;
            continue;
        }
        ungetc(c, stdin);
        if(!fgets(buffer, sizeof(buffer), stdin)) return (min/2+max/2);
        if(!caracter_en_string(buffer, '\n')) flush();
        num = strtoull(buffer, &ptr, 10);
        if(ptr!=buffer && isspace(*ptr) && en_rango(num, min, max)) break;
        edlib_msj_error;
    }
    #ifdef EDLIB_RESETEAR_ERROR
    edlib_set_msj_error("");
    #endif
    return num;
}
#define validar_uint() (\
    validar_uint_en_rango(0, ULLONG_MAX))

#define validar_uint_min(min) (\
    validar_uint_en_rango(min, ULLONG_MAX))

#define validar_uint_max(max) (\
    validar_uint_en_rango(0, max))

static long double validar_float_en_rango(long double min, long double max) {
    char buffer[48], *ptr;
    int c; long double num;
    while(true) {
        edlib_prompt;
        while(isspace(c=fgetc(stdin)) && c!='\n' && c!=EOF);
        if(!isdigit(c) && c!='+' && c!='-' && c!='.') {
            if(c==EOF) return (min/2+max/2);
            if(c!='\n') flush();
            edlib_msj_error;
            continue;
        }
        ungetc(c, stdin);
        if(!fgets(buffer, sizeof(buffer), stdin)) return (min/2+max/2);
        if(!caracter_en_string(buffer,'\n')) flush();
        num = strtold(buffer, &ptr);
        if(ptr!=buffer && isspace(*ptr) && en_rango(num, min, max)) break;
        edlib_msj_error;
    }
    #ifdef EDLIB_RESETEAR_ERROR
    edlib_set_msj_error("");
    #endif
    return num;
}

#define validar_float() (\
    validar_float_en_rango(-LDBL_MAX, LDBL_MAX))

#define validar_float_min(min) (\
    validar_float_en_rango(min, LDBL_MAX))

#define validar_float_max(max) (\
    validar_float_en_rango(-LDBL_MAX, max))

static char leer_caracter(void) {
    fputs(_edlib_prompt, stdout);
    int c = fgetc(stdin);
    if(c!='\n') flush();
    return c;
}

/*Lee un string de caracteres al arreglo de caracteres apuntado por buffer. La funcion debe
saber la cantidad de caracteres 'lbuffer' que puede almacenar el buffer. lbuffer debe ser como
minimo de 1 caracter de longitud ya que la funcion podra leer a lo mas lbuffer-1 caracteres
de entrada ya que debe almacenar '\0' en el ultimo lugar para formar un string valido. Los
valores lmin y lmax controlan la cantidad de caracteres que se leen*/
static size_t leer_string_con_longitud(char* buffer, size_t lmin, size_t lmax ,size_t lbuffer) {
    if(!buffer || lbuffer < 2) return 0;
    int c; size_t l;
    if(lmax >= lbuffer) lmax = lbuffer-1;
    while(true) {
        edlib_prompt;
        while(isspace(c=fgetc(stdin)) && c!='\n');
        for(l=0; l<lbuffer && c!='\n' && c!=EOF; ++l) {
            buffer[l]=c;
            c=fgetc(stdin);
        }
        if(en_rango(l, lmin, lmax) || c==EOF) break;
        if(c!='\n') flush();
        edlib_msj_error;
    }
    buffer[l]='\0';
    #ifdef EDLIB_RESETEAR_ERROR
    edlib_set_msj_error("");
    #endif
    return l;
}

#define leer_string_con_lmax(buffer, lmax, lbuffer) (\
    leer_string_con_longitud(buffer, 0, lmax, lbuffer))

#define leer_string_con_lmin(buffer, lmin, lbuffer) (\
    leer_string_con_longitud(buffer, lmin, lbuffer-1, lbuffer))

#define leer_string(buffer, lbuffer) (\
    leer_string_con_longitud(buffer, 0, lbuffer-1, lbuffer))

/*Imprimir n strings pasados como un arreglo, como un solo string*/
static inline void _print(const char* strings[], size_t n) {
    for(int i=0; i<n; ++i)
        fputs(strings[i], stdout);
    return;
}

/*Imprimir n strings pasados como argumentos variables, como un solo string*/
#define print(...) (\
    _print((const char*[]){__VA_ARGS__},\
    sizeof((const char*[]){__VA_ARGS__})/sizeof(char*)))

/*Imprimir n strings pasados como un arreglo, un string por linea*/
static inline void _println(const char* strings[], size_t n) {
    for(int i=0; i<n; ++i)
        puts(strings[i]);
    return;
}

/*Imprimir n strings pasados como argumentos variables, un string por linea*/
#define println(...) (\
    _println((const char*[]){__VA_ARGS__},\
    sizeof((const char*[]){__VA_ARGS__})/sizeof(char*)))

#define endl fputc('\n', stdout);

#endif