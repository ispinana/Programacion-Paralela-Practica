#include <stdio.h>
#include <stdlib.h>
#include "casos_prueba.h"

Function *crear_funciones_usuario(int num_funciones, int num_variables, int num_monomios) {

    Function *funciones = calloc(num_funciones, sizeof(Function));

    if(funciones == NULL) {
        printf("Error reservando memoria para las funciones.\n");
        return NULL;
    }

    for(int f = 0; f < num_funciones; f++) {

        funciones[f].num_variables = num_variables;
        funciones[f].num_monomios = num_monomios;

        funciones[f].monomios = calloc(num_monomios, sizeof(Monomio));

        if(funciones[f].monomios == NULL) {
            liberar_funciones(funciones, num_funciones);
            return NULL;
        }

        printf("\n========== FUNCION %d ==========\n", f + 1);

        for(int m = 0; m < num_monomios; m++) {

            printf("\nMonomio %d\n", m + 1);

            printf("Coeficiente: ");
            if(scanf("%lf", &funciones[f].monomios[m].coeficiente) != 1) {
                liberar_funciones(funciones, num_funciones);
                return NULL;
            }

            funciones[f].monomios[m].exponentes = calloc(num_variables, sizeof(int));

            if(funciones[f].monomios[m].exponentes == NULL) {
                liberar_funciones(funciones, num_funciones);
                return NULL;
            }

            for(int v = 0; v < num_variables; v++) {

                printf("Exponente variable %d: ", v);

                if(scanf("%d", &funciones[f].monomios[m].exponentes[v]) != 1 ||
                   funciones[f].monomios[m].exponentes[v] < 0) {
                    printf("Exponente no valido.\n");
                    liberar_funciones(funciones, num_funciones);
                    return NULL;
                }
            }
        }
    }

    return funciones;
}

double *crear_punto_usuario(int num_variables) {

    double *punto = malloc(num_variables * sizeof(double));

    if(punto == NULL) {
        printf("Error reservando memoria para el punto.\n");
        return NULL;
    }

    printf("\nIntroduzca el valor de cada variable:\n");

    for(int i = 0; i < num_variables; i++) {

        printf("Variable %d: ", i);

        if(scanf("%lf", &punto[i]) != 1) {
            free(punto);
            return NULL;
        }
    }

    return punto;
}

double **crear_gradientes(Function *funciones, int num_funciones) {

    double **gradientes = calloc(num_funciones, sizeof(double *));

    if(gradientes == NULL) {
        return NULL;
    }

    for(int f = 0; f < num_funciones; f++) {

        gradientes[f] = malloc(funciones[f].num_variables * sizeof(double));

        if(gradientes[f] == NULL) {
            liberar_gradientes(gradientes, num_funciones);
            return NULL;
        }
    }

    return gradientes;
}

void liberar_funciones(Function *funciones, int num_funciones) {

    if(funciones == NULL) {
        return;
    }

    for(int f = 0; f < num_funciones; f++) {

        if(funciones[f].monomios != NULL) {

            for(int m = 0; m < funciones[f].num_monomios; m++) {
                free(funciones[f].monomios[m].exponentes);
            }

            free(funciones[f].monomios);
        }
    }

    free(funciones);
}

void liberar_gradientes(double **gradientes, int num_funciones) {

    if(gradientes == NULL) {
        return;
    }

    for(int f = 0; f < num_funciones; f++) {
        free(gradientes[f]);
    }

    free(gradientes);
}
