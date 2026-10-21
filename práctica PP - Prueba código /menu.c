#include <stdio.h>
#include "menu.h"

static int leer_entero(const char *mensaje, int minimo, int maximo) {
    int valor;
    int c;

    while (1) {
        printf("%s", mensaje);
        if (scanf("%d", &valor) == 1 && valor >= minimo && valor <= maximo) {
            while ((c = getchar()) != '\n' && c != EOF) {}
            return valor;
        }
        while ((c = getchar()) != '\n' && c != EOF) {}
        printf("Opcion no valida. Intentalo de nuevo.\n");
    }
}

OpcionesMenu mostrar_menu(void) {
    OpcionesMenu opciones = {0};

    printf("\n=== MODO DE EJECUCION ===\n");
    printf("1. Secuencial\n2. OpenMP\n");
    opciones.modo = leer_entero("Elige una opcion: ", 1, 2);

    printf("\n=== TIPO DE PROBLEMA ===\n");
    printf("1. Caso basico conocido\n2. Problema personalizado\n");
    opciones.tipo_problema = leer_entero("Elige una opcion: ", 1, 2);

    if (opciones.tipo_problema == 2) {
        opciones.num_funciones = leer_entero("Numero de funciones: ", 1, 1000000);
        opciones.num_variables = leer_entero("Numero de variables: ", 1, 1000000);
        opciones.num_monomios = leer_entero("Numero de monomios: ", 1, 1000000);

        printf("\n=== COMO CREAR LAS FUNCIONES ===\n");
        printf("1. Generar automaticamente\n2. Introducir manualmente\n");
        opciones.opcion_funciones = leer_entero("Elige una opcion: ", 1, 2);

        printf("\n=== COMO CREAR EL PUNTO ===\n");
        printf("1. Generar automaticamente\n2. Introducir manualmente\n");
        opciones.opcion_punto = leer_entero("Elige una opcion: ", 1, 2);
    }

    return opciones;
}
