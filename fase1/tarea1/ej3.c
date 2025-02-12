/*En una escuela se almacena información sobre los alumnos, ésta se almacena de la
siguiente manera. Por cada alumno se almacena la siguiente información:
* Nombre del alumno: cadena de caracteres.
* Matrícula del alumno: entero largo.
* Número de semestres cursados: entero.
* Calificación promedio por semestre: arreglo unidimensional de tipo real. Su
    capacidad máxima es para 9 elementos.
* Carrera: cadena de caracteres.

Desarrollar un programa en C tal, que dada la información de n alumnos, pueda
efectuar las siguientes operaciones:
a) Listar nombres y matrícula de los estudiantes que tengan un promedio general
mayor a 9.
b) Listar nombres y matrícula de los estudiantes, de la carrera de economía, que
hayan obtenido un promedio superior a 9 en todos los semestres cursados hasta
el momento.
Escribir nombre y matrícula del alumno que tiene el mayor promedio de la carrera de
Ingeniería en Computación.*/

#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#define EDLIB_MAIN
#include "edlib.h"

#define STR_MAX 64
#define SEMESTRES 9

typedef struct {
    char nombre[STR_MAX];
    char carrera[STR_MAX];
    unsigned long matricula;
    unsigned int sem_cursados;
    float promedios[SEMESTRES];
    float prom_general;
} Alumno;

void print_alumno(Alumno* alumno) {
    printf("*Nombre:    %s\n", alumno->nombre);
    printf("*Matricula: %lu\n", alumno->matricula);
}

int main(void) {
    printf("SISTEMA DE PROCESAMIENTO DE DATOS DE ALUMNOS FCFM\n\n");
    printf("Introduzca la cantidad de alumnos a procesar");
    size_t n = validar_uint();
    Alumno alumnos[n];
    for(size_t i=0; i<n; ++i) {
        Alumno* alumno = alumnos+i;
        printf("***Introduzca la informacion del alumno no. %d***\n", i+1);
        edlib_set_mensaje_error("El nombre debe se ser de menos de 60 caracteres");
        printf("*Nombre"); leer_string(alumno->nombre, STR_MAX);
        edlib_set_mensaje_error("El nombre de la carrera de debe se ser de menos de 60 caracteres");
        printf("*Carrera"); leer_string(alumno->carrera, STR_MAX);
        for(char* ptr=alumno->carrera; *ptr!='\0'; ++ptr) *ptr=toupper(*ptr);
        edlib_set_mensaje_error("La matricula debe ser un numero decimal de a lo mas 7 digitos");
        printf("*Matricula"); alumno->matricula=validar_int_en_rango(0,9999999);
        edlib_set_mensaje_error("Los semestres cursados deben ser un numero entre 0 y 9");
        printf("*Semestres Cursados"); alumno->sem_cursados=validar_uint_en_rango(0, 9);
        printf("<-*Introduzca la calificacion de los semestres cursados*->\n");
        alumno->prom_general=0;
        for(size_t j=0; j < alumno->sem_cursados; ++j) {
            printf("\t\t*Calificacion Semestre no. %u", j+1);
            edlib_set_mensaje_error("La calificacion debe ser un numero real entre 0 y 100");
            alumno->promedios[j]=validar_float_en_rango(0,100);
            alumno->prom_general+=alumno->promedios[j];
        }
        alumno->prom_general/=alumno->sem_cursados;
    }
    printf("\n\nAlumnos con promedio mayor a 90:\n\n");
    for(size_t i=0; i<n; ++i) {
        Alumno* alumno=alumnos+i;
        if(alumno->prom_general > 90) {
            print_alumno(alumno);
            putchar('\n');
        }
    }
    printf("\nAlumnos de ECONOMIA con promedios mayor a 90 en todos sus semestres:\n\n");
    {
        const char* nombre_licenciatura="ECONOMIA";
        for(size_t i=0; i<n; ++i) {
            Alumno* alumno = alumnos+i;
            if(strcmp(nombre_licenciatura, alumno->carrera)==0) {
                bool cumple_con_promedio=true;
                for(size_t j=0; j < alumno->sem_cursados; ++j) {
                    if(alumno->promedios[j] <= 90)
                        cumple_con_promedio=false;
                }
                if(cumple_con_promedio) {
                    print_alumno(alumno);
                    putchar('\n');
                }
            }
        }
    }
    printf("\nAlumno con mayor calificacion de la carrera de COMPUTACION:\n\n");
    {
        const char* nombre_licenciatura="COMPUTACION";
        Alumno* alumno_max=NULL;
        size_t i;
        for(i=0; i<n; ++i) {
            Alumno* alumno = alumnos+i;
            if(strcmp(nombre_licenciatura, alumno->carrera)==0) {
                alumno_max=alumno;
                break;
            }
        }
        for(i+=1; i<n; ++i) {
            Alumno* alumno = alumnos+i;
            if(strcmp(nombre_licenciatura, alumno->carrera)==0) {
                if(alumno->prom_general > alumno_max->prom_general) {
                    alumno_max=alumno;
                }
            }
        }
        if(alumno_max!=NULL) {
            print_alumno(alumno_max);
            putchar('\n');
        } else {
            printf("No se encontraron alumnos de la carrera de COMPUTACION!\n");
        }
    }
    return 0;
}