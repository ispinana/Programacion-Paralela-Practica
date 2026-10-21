#include <stdio.h>
#include <stdlib.h>
#include "menu.h"
#include "gradiente.h"
#include "casos_prueba.h"

/* Pide una opción entera dentro del intervalo indicado. */
static int elegir_opcion(const char *mensaje, int minimo, int maximo) {
    int opcion;
    int caracter;
    while (1) {
        printf("%s", mensaje);
        if (scanf("%d", &opcion) == 1 && opcion >= minimo && opcion <= maximo) {
            while ((caracter = getchar()) != '\n' && caracter != EOF) {}
            return opcion;
        }
        while ((caracter = getchar()) != '\n' && caracter != EOF) {}
        printf("Opcion no valida. Intentalo de nuevo.\n");
    }
}

static int pedir_cantidad(const char *mensaje) {
    int cantidad;
    int caracter;
    while (1) {
        printf("%s", mensaje);
        if (scanf("%d", &cantidad) == 1 && cantidad > 0) {
            while ((caracter = getchar()) != '\n' && caracter != EOF) {}
            return cantidad;
        }
        while ((caracter = getchar()) != '\n' && caracter != EOF) {}
        printf("Introduce un numero entero mayor que cero.\n");
    }
}

void ejecutar_menu(void) {
    int modo, tipo, num_funciones = 0;
    int num_variables, num_monomios, opcion_funciones, opcion_punto;
    Function *funciones = NULL;
    double *punto = NULL;
    double **gradientes = NULL;

    printf("\n=== MODO DE EJECUCION ===\n");
    printf("1. Secuencial\n2. OpenMP\n");
    modo = elegir_opcion("Elige una opcion: ", 1, 2);

    printf("\n=== TIPO DE PROBLEMA ===\n");
    printf("1. Caso basico conocido\n2. Problema personalizado\n");
    tipo = elegir_opcion("Elige una opcion: ", 1, 2);

    if (tipo == 1) {
        funciones = crear_caso_basico(&num_funciones);
        punto = crear_punto_basico();
    } else {
        num_funciones = pedir_cantidad("Numero de funciones: ");
        num_variables = pedir_cantidad("Numero de variables: ");
        num_monomios = pedir_cantidad("Numero de monomios: ");

        printf("\n=== COMO CREAR LAS FUNCIONES ===\n");
        printf("1. Generar automaticamente\n2. Introducir manualmente\n");
        opcion_funciones = elegir_opcion("Elige una opcion: ", 1, 2);
        if (opcion_funciones == 1)
            funciones = crear_funciones_prueba(num_funciones, num_variables, num_monomios);
        else
            funciones = crear_funciones_usuario(num_funciones, num_variables, num_monomios);

        if (funciones == NULL) {
            fprintf(stderr, "No se pudieron crear las funciones.\n");
            return;
        }

        printf("\n=== COMO CREAR EL PUNTO ===\n");
        printf("1. Generar automaticamente\n2. Introducir manualmente\n");
        opcion_punto = elegir_opcion("Elige una opcion: ", 1, 2);
        if (opcion_punto == 1)
            punto = crear_punto(num_variables);
        else
            punto = crear_punto_usuario(num_variables);
    }

    if (funciones == NULL || punto == NULL) {
        fprintf(stderr, "Error al crear el problema.\n");
        if (funciones != NULL) liberar_funciones(funciones, num_funciones);
        free(punto);
        return;
    }

    gradientes = crear_gradientes(funciones, num_funciones);
    if (gradientes == NULL) {
        fprintf(stderr, "Error al reservar memoria para gradientes.\n");
        liberar_funciones(funciones, num_funciones);
        free(punto);
        return;
    }

    if (modo == 2) {
        printf("\nAviso: OpenMP aun no esta implementado; se calcula secuencialmente.\n");
    }
    calcular_gradientes(funciones, num_funciones, punto, gradientes);

    printf("\n=== RESULTADOS ===\n");
    for (int f = 0; f < num_funciones; f++) {
        printf("Gradiente funcion %d: ", f);
        for (int v = 0; v < funciones[f].num_variables; v++) {
            printf("%.2f ", gradientes[f][v]);
        }
        printf("\n");
    }

    liberar_gradientes(gradientes, num_funciones);
    liberar_funciones(funciones, num_funciones);
    free(punto);
}
