#include <stdio.h>
#define EDLIB_MAIN
#include "edlib.h"

/*Imprimir matriz elemento por filas, elemento por elemento*/
void print_matriz(double* matriz, size_t n) {
    for(int i=0; i<n; ++i) {
        printf("| ");
        for(int j=0; j<n; ++j) {
            printf("%5.2f ", matriz[i*n+j]);
        }
        printf("|\n");
    }
    return;
}

/*Llena la matriz 'menor' con la infomacion correspondiente a la menor de
la matriz obtenida ignorando la primera fila y la columna 'col'*/ 
void construir_menor(double* matriz, size_t n, double* menor, size_t col) {
    for(int i=1; i<n; ++i) {
        for(int j=0, k=0; j<n; ++j) {
            if(j==col) continue; //Si j==col resagamos k
            menor[(i-1)*(n-1)+k]=matriz[i*n+j];
            ++k;
        }
    }
    return;
}

/*Encuentra la deteminante de una matriz 'n'*'n' utilizando la expansion de
Laplaz por deteminantes de menores. La funcion se llama recusivamente para
calcular las determinantes de las menores necesarias para calcular la
determinante*/
double determinante(double* matriz, size_t n) {
    if(n==1) return matriz[0];
    double det=0;
    double menor[n-1][n-1]; //Espacio de memoria para almacenar las menores
    for(int i=0; i<n; ++i) { //Hacemos la suma de 'n' menores
        construir_menor((double*)matriz, n, (double*)menor, i);
        //sumamos cada termino signo*elemento*determinante_menor
        det+=(i%2 ? 1:-1)*matriz[i]*determinante((double*)menor, n-1);
    }
    return det;
}


//|{9,8,5,4,6,1,2,2,7}|=132
int main(void) {
    println("Programa para calcular el determinante de una matriz");
    print("Dimension de la matriz");
    edlib_set_msj_error("Introduzca un numero natural entre 1 y 100");
    size_t n = validar_uint_en_rango(1,100);
    double matriz[n][n];
    for(int i=0; i<n; ++i) {
        for(int j=0; j<n; ++j) {
            edlib_set_msj_error("Introduzca un numero real valido");
            printf("Elemento[%d][%d]", i, j);
            matriz[i][j]=validar_float();
        }
    } endl;
    println("Matriz Resultante...");
    print_matriz((double*)matriz, n); endl;
    println("Calculando Determinante...");
    double det = determinante((double*)matriz, n);
    printf("Determinante: %.2f\n", det);
    return 0;
}