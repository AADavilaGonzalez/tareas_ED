#include <stdio.h>
#define EDLIB_MAIN
#include "edlib.h"

int invertir(int num)
{
    if(num < 10) //si el numero tiene nada mas un digito, se regresa el mismo numero
    {
        printf("%d", num);
        return;
    }
    
    printf("%d", num % 10); //se extrae el ultimo digito del numero y se imprime
    
    //se vuelve a llamar a la funcion pasandole como parametro el numero
    //pero sin el ultimo digito
    return invertir(num/10);
}

int main()
{
    int num;

    //Se ingresa el numero que se desea invertir
    printf("Ingrese el numero a invertir:\n");
    num = validar_int_min(0);
    
    printf("El numero inverso es: \n");
    invertir(num); //se manda a llamar a la funcion para invertir el numero

    return 0;
}
