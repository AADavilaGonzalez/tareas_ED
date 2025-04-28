#include "app.c"

int main(void) {
    Contexto contexto = {
        (ParamVehiculo){
            .peso = 4.5f,
            .carga_max = 50.0f,
            .combustible_max = 1000.0f,
            .rendimiento = 3.0f,
        },
        (ParamViaje){0}
    };

    Grafo_D* mapa = incializar_mapa();
    if(!mapa) {
        exit_grafico(EXIT_FAILURE,
            "Hubo un error al inicializar el sistema",
            "El programa procedera a cerrarse");
    }
    grafo_d_set_cmp_vt(mapa, comparar_ciudad_por_nombre);
    grafo_d_set_calc_peso(mapa, calcular_peso_por_distancia);
    grafo_d_set_contexto(mapa, &contexto);

    Camino_D* viaje;
    while(true) {
        clear();
        println("Sistema de Gestion de Transporte Aceros ACME",
                "--------------------------------------------",
                "1. Mostrar Ciudades Disponibles",
                "2. Configurar Vehiculo",
                "3. Seleccionar Prioridad",
                "4. Generar Viaje Secuencial",
                "5. Generar Viaje Generico",
                "6. Salir");
        edlib_set_prompt(PROMPT_OPC);
        switch(validar_int_en_rango(1,6)) {
        case 1:
            mostrar_ciudades(mapa);
            break;
        case 2:
            configurar_vehiculo(&contexto.vehiculo);
            break;
        case 3:
            seleccionar_prioridad(mapa);
            break;
        case 4:
            viaje = viaje_secuencial(mapa);
            if(viaje) {print_viaje(viaje); free(viaje);}
            break;
        case 5:
            viaje = viaje_generico(mapa);
            if(viaje) {print_viaje(viaje); free(viaje);}
            break;
        case 6:
            grafo_d_destruir(mapa);
            exit_grafico(EXIT_SUCCESS,
                "Terminando la ejecucion del programa");
        }
    }
}