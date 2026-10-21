#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "gradiente.h"
#include "casos_prueba.h"

int main() {
    int num_funciones, num_variables, num_monomios;
    int opcion;

    printf("========== INTRODUCIR FUNCIONES MANUALMENTE ==========\n");

    printf("Numero de funciones: ");
    if (scanf("%d", &num_funciones) != 1 || num_funciones <= 0) {
        printf("Numero de funciones no valido.\n");
        return 1;
    }

    printf("Numero de variables por funcion: ");
    if (scanf("%d", &num_variables) != 1 || num_variables <= 0) {
        printf("Numero de variables no valido.\n");
        return 1;
    }

    printf("Numero de monomios por funcion: ");
    if (scanf("%d", &num_monomios) != 1 || num_monomios <= 0) {
        printf("Numero de monomios no valido.\n");
        return 1;
    }

    Function *funciones = crear_funciones_usuario(
        num_funciones, num_variables, num_monomios
    );

    if (funciones == NULL) {
        return 1;
    }

    double *punto = crear_punto_usuario(num_variables);

    if (punto == NULL) {
        liberar_funciones(funciones, num_funciones);
        return 1;
    }

    double **gradientes = crear_gradientes(funciones, num_funciones);

    if (gradientes == NULL) {
        liberar_funciones(funciones, num_funciones);
        free(punto);
        return 1;
    }

    do {
        printf("\n========== TIPO DE EJECUCION ==========\n");
        printf("1. Secuencial\n");
        printf("2. Paralelo con OpenMP\n");
        printf("3. Paralelo con CUDA\n");
        printf("4. Comparar tiempos de ejecucion\n");
        printf("5. Salir\n");
        printf("Seleccione una opcion: ");

        if (scanf("%d", &opcion) != 1) {
            printf("Entrada no valida.\n");
            break;
        }

        switch(opcion) {

            case 1: {
                clock_t inicio = clock();

                calcular_gradientes(
                    funciones, num_funciones, punto, gradientes
                );

                clock_t fin = clock();

                for(int f = 0; f < num_funciones; f++) {
                    printf("\nGradiente funcion %d: (", f + 1);

                    for(int v = 0; v < funciones[f].num_variables; v++) {
                        if(v > 0) {
                            printf(", ");
                        }

                        printf("%.2f", gradientes[f][v]);
                    }

                    printf(")\n");
                }

                double tiempo = (double)(fin - inicio) / CLOCKS_PER_SEC;
                printf("\nTiempo secuencial (CPU): %.6f segundos\n", tiempo);

                break;
            }

            case 2:
                printf("\nPendiente: implementar OpenMP.\n");
                break;

            case 3:
                printf("\nPendiente: implementar CUDA.\n");
                break;

            case 4:
                printf("\nPendiente: comparar tiempos secuencial, OpenMP y CUDA.\n");
                break;

            case 5:
                printf("\nSaliendo del programa...\n");
                break;

            default:
                printf("\nOpcion no valida.\n");
                break;
        }

    } while(opcion != 5);

    liberar_gradientes(gradientes, num_funciones);
    liberar_funciones(funciones, num_funciones);
    free(punto);

    return 0;
}
