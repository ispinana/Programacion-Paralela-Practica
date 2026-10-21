#include <stdio.h>
#include <stdlib.h>
#include "menu.h"
#include "gradiente.h"
#include "casos_prueba.h"

int main(void) {
    OpcionesMenu opciones = mostrar_menu();
    int num_funciones = opciones.num_funciones;
    Function *funciones = NULL;
    double *punto = NULL;
    double **gradientes = NULL;

    /* CREAR FUNCIONES Y PUNTO SEGUN LO ELEGIDO EN EL MENU */
    if (opciones.tipo_problema == 1) {
        funciones = crear_caso_basico(&num_funciones);
        punto = crear_punto_basico();
    } else {
        if (opciones.opcion_funciones == 1) {
            funciones = crear_funciones_prueba(num_funciones,
                       opciones.num_variables, opciones.num_monomios);
        } else {
            funciones = crear_funciones_usuario(num_funciones,
                       opciones.num_variables, opciones.num_monomios);
        }

        if (funciones == NULL) {
            fprintf(stderr, "Error al crear las funciones.\n");
            return 1;
        }

        if (opciones.opcion_punto == 1) {
            punto = crear_punto(opciones.num_variables);
        } else {
            punto = crear_punto_usuario(opciones.num_variables);
        }
    }

    if (funciones == NULL || punto == NULL) {
        fprintf(stderr, "Error al crear el problema.\n");
        if (funciones != NULL) liberar_funciones(funciones, num_funciones);
        free(punto);
        return 1;
    }

    /* CALCULAR GRADIENTES */
    gradientes = crear_gradientes(funciones, num_funciones);
    if (gradientes == NULL) {
        fprintf(stderr, "Error al reservar memoria para gradientes.\n");
        liberar_funciones(funciones, num_funciones);
        free(punto);
        return 1;
    }

    if (opciones.modo == 1) {
        calcular_gradientes(funciones, num_funciones, punto, gradientes);

    } else if (opciones.modo == 2) {
        printf("\nAviso: OpenMP todavia no esta implementado.\n");
        printf("Se ejecutara el calculo secuencial.\n");

        calcular_gradientes(funciones, num_funciones, punto, gradientes);
    }
    

    /* MOSTRAR RESULTADOS */
    printf("\n=== RESULTADOS ===\n");
    for (int f = 0; f < num_funciones; f++) {
        printf("Gradiente funcion %d: ", f);
        for (int v = 0; v < funciones[f].num_variables; v++) {
            printf("%.2f ", gradientes[f][v]);
        }
        printf("\n");
    }

    /* LIBERAR MEMORIA */
    liberar_gradientes(gradientes, num_funciones);
    liberar_funciones(funciones, num_funciones);
    free(punto);
    return 0;
}
