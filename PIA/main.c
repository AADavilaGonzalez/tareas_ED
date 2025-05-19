#include "app.c"
#include "grafo_d.h"

int main(void) {
    
    Grafo_D* mapa = incializar_mapa();
    if(!mapa) {
        exit_grafico(EXIT_FAILURE,
            "Hubo un error al inicializar el sistema",
            "El programa procedera a cerrarse");
    }

    Viaje viaje;
    while(true) {
        clear();
        println("Sistema de Gestion de Transporte ACME Technologies",
                "--------------------------------------------------",
                "0. Desplegar Menu de Ayuda",
                "1. Mostrar Destinos Disponibles",
                "2. Configurar Parametros",
                "3. Seleccionar Prioridad",
                "4. Generar Ruta Secuencial",
                "5. Generar Ruta Generica",
                "6. Salir");
        edlib_set_prompt(PROMPT_OPC);
        switch(validar_int_en_rango(0,6)) {
        case 0:
            print_ayuda_general();
            break;
        case 1:
            mostrar_ciudades(mapa);
            break;
        case 2:
            configurar_parametros(mapa->contexto);
            break;
        case 3:
            seleccionar_prioridad(mapa);
            break;
        case 4:
            viaje = viaje_secuencial(mapa);
            if(viaje.camino!=NULL) {
                print_viaje(viaje);
                camino_d_destruir(viaje.camino);
            }
            limpiar_pesos_de_entrega(mapa);
            break;
        case 5:
            viaje = viaje_generico(mapa);
            if(viaje.camino!=NULL) {
                print_viaje(viaje);
                camino_d_destruir(viaje.camino);
            }
            limpiar_pesos_de_entrega(mapa);
            break;
        case 6:
            grafo_d_destruir(mapa);
            exit_grafico(EXIT_SUCCESS,
                "Terminando la ejecucion del programa");
        }
    }
}