#define EDLIB_MAIN
#include "edlib.h"

/*Estructura para almacenar (poder regresar)
tanto el numero como la suma de sus digitos*/
typedef struct {
    unsigned int num;
    unsigned int sum;
} num_sum;

/*Suma de los digitos de un numero de manera recursiva*/
unsigned int suma_digitos(unsigned int num) {
    if(num < 10) return num;
    return num%10 + suma_digitos(num/10);
}

/*Pide al usuario un numero para calcular la suma de sus
digitos, lanza la funcion de nuevo si el usuario lo indica.
Devuelve el numero (y la suma) del numero con la mayor
suma de digitos de forma recursiva*/
num_sum mayor_suma_digitos(void) {
    num_sum actual;
    print("Introduzca un numero natural");
    actual.num = validar_uint();
    actual.sum = suma_digitos(actual.num);
    print("Continuar?(1-Si|2-No)");
    if(validar_int_en_rango(1,2)==2) 
        return actual;
    else {
        num_sum siguiente = mayor_suma_digitos();
        return actual.sum > siguiente.sum ? actual : siguiente;
    }
}

int main(void) {
    println("Programa para calcular la mayor suma de digitos");
    num_sum respuesta = mayor_suma_digitos();
    printf("Numero con mayor suma de digitos: %u\n", respuesta.num);
    return 0;
}