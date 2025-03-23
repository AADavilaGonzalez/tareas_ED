#include <stdio.h>
#define EDLIB_MAIN
#include "edlib.h"

int invertir(int num, int aux)
{
    if(num == 0)
        return aux; //se retorna la cantidad acumulada

    return invertir(num / 10, aux * 10 + (num % 10)); //se quita el ultimo digito del numero y
    //el ultimo digito se agrega al acumulador

}

int main()
{
    int num, resultado;

    //Se ingresa el numero que se desea invertir
    printf("Ingrese el numero a invertir:\n");
    num = validar_int_min(0);


    printf("El numero inverso es: \n");
    //se manda a llamar a la funcion para invertir el numero
    resultado = invertir(num, 0); //se agrega un acumulador para construir el inverso
    printf("%d", resultado);

    return 0;
}
