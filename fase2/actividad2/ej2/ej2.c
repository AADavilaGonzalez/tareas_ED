#include <stdio.h>

void imprimir_lista(int min, int max){
    /*Caso base*/
    if(min > max) return;
    /* Imprimimos el siguiente número*/
    printf("%d ", min);
    /* Llamamos a la función incrementando el minimo para imprimirlo*/
    imprimir_lista(min+1, max);
}

int main(void){
    int min, max, num;
    printf("Programa para imprimir una lista\n"
        "de los numeros entre dos valores\n");
    printf("Introduzca el valor menor\n");
    scanf("%d", &min),
    printf("Introduzca el valor mayor\n");
    scanf("%d", &max);

    /* Condicional en caso de que el usuario ingrese los valores mal*/
    if(min < max)
        imprimir_lista(min, max);
    else;
        imprimir_lista(max, min);
    
    return 0;
}