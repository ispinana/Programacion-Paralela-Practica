#include <stdio.h>

#include "gradiente.h"
#include "casos_prueba.h"

int main() {
    int num_funciones;

    /* ========================================
       CREAR CASO DE PRUEBA
       ======================================== */
    Function *funciones = crear_caso_basico(&num_funciones);
    double *punto = crear_punto_basico();
    double **gradientes = crear_gradientes(funciones, num_funciones);

    /* ========================================
       CALCULAR GRADIENTES
       ======================================== */
    calcular_gradientes(funciones, num_funciones, punto, gradientes);

    /* ========================================
       MOSTRAR RESULTADOS
       ======================================== */
    for(int f = 0; f < num_funciones; f++) {
        printf("Gradiente funcion %d: ",f);

        for(int v = 0; v < funciones[f].num_variables; v++){
            printf("%.2f ", gradientes[f][v]);
        }

        printf("\n");
    }


    /* ========================================
       LIBERAR MEMORIA
       ======================================== */
    liberar_gradientes(gradientes, num_funciones);
    liberar_funciones(funciones, num_funciones);
    free(punto);

    return 0;
}
