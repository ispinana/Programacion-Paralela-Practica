#include <stdlib.h>

#include "casos_prueba.h"

Function *crear_caso_basico(int *num_funciones) {
    *num_funciones = 2;
    Function *funciones = malloc((*num_funciones) * sizeof(Function));

    /* ============================================================
       FUNCIÓN 0
       f1(x,y,z) = 3xy + 4yz + 2x + 5
       ============================================================ */
    funciones[0].num_variables = 3;
    funciones[0].num_monomios = 4;

    funciones[0].monomios = malloc(funciones[0].num_monomios * sizeof(Monomio));

    for(int i = 0; i < funciones[0].num_monomios; i++) {
        funciones[0].monomios[i].exponentes = calloc(funciones[0].num_variables, sizeof(int));
    }

    // 3xy
    funciones[0].monomios[0].coeficiente = 3;
    funciones[0].monomios[0].exponentes[0] = 1;
    funciones[0].monomios[0].exponentes[1] = 1;

    // 4yz
    funciones[0].monomios[1].coeficiente = 4;
    funciones[0].monomios[1].exponentes[1] = 1;
    funciones[0].monomios[1].exponentes[2] = 1;

    // 2x
    funciones[0].monomios[2].coeficiente = 2;
    funciones[0].monomios[2].exponentes[0] = 1;

    // 5
    funciones[0].monomios[3].coeficiente = 5;

    /* ============================================================
       FUNCIÓN 1
       f2(x,y,z) = x² + yz + 3z
       ============================================================ */
    funciones[1].num_variables = 3;
    funciones[1].num_monomios = 3;
    funciones[1].monomios = malloc(funciones[1].num_monomios * sizeof(Monomio));

    for(int i = 0; i < funciones[1].num_monomios; i++) {
        funciones[1].monomios[i].exponentes = calloc(funciones[1].num_variables, sizeof(int));
    }

    // x²
    funciones[1].monomios[0].coeficiente = 1;
    funciones[1].monomios[0].exponentes[0] = 2;

    // yz
    funciones[1].monomios[1].coeficiente = 1;
    funciones[1].monomios[1].exponentes[1] = 1;
    funciones[1].monomios[1].exponentes[2] = 1;

    // 3z
    funciones[1].monomios[2].coeficiente = 3;
    funciones[1].monomios[2].exponentes[2] = 1;

    return funciones;
}

double *crear_punto_basico() {
    double *punto = malloc(3 * sizeof(double));

    punto[0] = 1.0;
    punto[1] = 2.0;
    punto[2] = 3.0;

    return punto;
}


Function *crear_funciones_prueba(int num_funciones, int num_variables, int num_monomios) {
    Function *funciones = malloc(num_funciones + sizeof(Function));

    for(int f = 0; f < num_funciones; f++) {
        funciones[f].num_variables = num_variables;
        funciones[f].num_monomios = num_monomios;

        funciones[f].monomios = malloc(num_monomios * sizeof(Monomio));

        for(int m = 0; m < num_monomios; m++) {

            // Coeficiente entre 1 y 5, dependiendo de "f" y "m" para que no todos los monomios sean iguales
            funciones[f].monomios[m].coeficiente = (double) (((f + m) % 5) + 1);

            funciones[f].monomios[m].exponentes = calloc(num_variables, sizeof(int));
            int variable1 = (f + m) % num_variables;

            funciones[f].monomios[m].exponentes[variable1] = 1 + ((f + m) % 2);

            if(num_variables > 1 && m % 2 == 0) {
                int desplazamiento = 1 + (m % (num_variables - 1));
                int variable2 = (variable1 + desplazamiento) % num_variables;

                funciones[f].monomios[m].exponentes[variable2] = 1;
            }
        }
    }

    return funciones;
}

Function *crear_funciones_usuario(int num_funciones, int num_variables, int num_monomios) {
    Function *funciones = malloc(num_funciones * sizeof(Function));

    if(funciones == NULL) {
        printf("Error reservando memoria para las funciones.\n");
        return NULL;
    }

    for(int f = 0; f < num_funciones; f++) {
        funciones[f].num_variables = num_variables;
        funciones[f].num_monomios = num_monomios;
        funciones[f].monomios = malloc(num_monomios * sizeof(Monomio));

        printf("\n============================\n FUNCION %d\n============================\n",f);

        for(int m = 0; m < num_monomios; m++) {
            printf("\nMonomio %d\n", m);
            printf("Coeficiente: ");
            scanf("%lf", &funciones[f].monomios[m].coeficiente);

            funciones[f].monomios[m].exponentes = calloc(num_variables, sizeof(int));

            for(int v = 0; v < num_variables; v++) {
                printf("Exponente variable %d: ", v);
                scanf("%d", &funciones[f].monomios[m].exponentes[v]);
            }
        }
    }

    return funciones;
}

double *crear_punto(int num_variables) {
    double *punto = malloc(num_variables * sizeof(double));

    for(int i = 0; i < num_variables; i++) {
        // Patrón: x0 = 1 | x1 = 2 | x2 = 3 | x3 = 1 | x4 = 2 | x5 = 3
        punto[i] = (double) ((i % 3) + 1);
    }

    return punto;
}

double *crear_punto_usuario(int num_variables) {
    double *punto = malloc(num_variables * sizeof(double));

    if(punto == NULL) {
        print("Error reservando memoria para el punto.\n");
        return NULL;
    }

    printf("\nIntroduzca el valor de cada variable: \n");

    for(int i = 0; i < num_variables; i++) {
        printf("Variable %d: ", i);
        scanf("%lf", &punto[i]);
    }

    return punto;
}


double **crear_gradientes(Function *funciones, int num_funciones) {
    double **gradientes = malloc(num_funciones * sizeof(double *));

    for(int f = 0; f < num_funciones; f++) {
        gradientes[f] = malloc(funciones[f].num_variables * sizeof(double));
    }

    return gradientes;
}


void liberar_funciones(Function *funciones, int num_funciones) {
    for(int f = 0; f < num_funciones; f++) {
        for(int m = 0; m < funciones[f].num_monomios; m++){
            free(funciones[f].monomios[m].exponentes);
        }

        free(funciones[f].monomios);
    }

    free(funciones);
}

void liberar_gradientes(double **gradientes, int num_funciones){
    for(int f = 0; f < num_funciones; f++) {
        free(gradientes[f]);
    }

    free(gradientes);
}
