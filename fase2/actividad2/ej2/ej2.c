#include <stdio.h>

void imprimir_lista(int min, int max){
    if(min > max) return;
    printf("%d ", min);
    imprimir_lista(min+1, max);
}

int main(void){
    int min, max, num;
    printf("Introduzca el valor menor\n");
    scanf("%d", &min),
    printf("Introduzca el valor mayor\n");
    scanf("%d", &max);

    if(min < max)
        imprimir_lista(min, max);
    else;
        imprimir_lista(max, min);
    
    return 0;
}