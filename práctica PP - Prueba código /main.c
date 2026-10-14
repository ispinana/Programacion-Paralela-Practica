#include <stdio.h>
#include <stdlib.h>

// Representación de un monomio:
/*
    Ejemplo: 3xy

    coeficiente = 3
    exponentes = [1, 1, 0]
*/
typedef struct {
    double coeficiente;
    int *exponentes;
} Monomio;


// Representación de una función
/*
    - numero de variables
    - numero de monomios
    - Monomio *monomios;
*/

typedef struct {
    int num_variables;
    int num_monomios;
    Monomio *monomios;
} Function;


// CALCULAR LA BASE DEL EXPONENTE
double potencia(double base, int exponente) {
    double resultado = 1.0;

    for(int i = 0; i < exponente; i++) {
        resultado *= base;
    }

    return resultado;
}


// CALCULAR DERIVADA DE UN MONOMIO RESPECTO A UNA VARIABLE
double derivar_monomio(Monomio *monomio, double *punto, int num_variables, int variable) {

    // Si la variable no aparece en el monomio, su exponente es 0 y por ende, su derivada también
    if(monomio->exponentes[variable] == 0) {
            return 0.0;
    }

    // Regla: cx^a --> derivada: cax^(a - 1)
    double resultado = monomio->coeficiente * monomio->exponentes[variable];

    for(int i = 0; i < num_variables; i++) {
        int exponente = monomio->exponentes[i];

        if(i == variable) {
            exponente--;
        }

        resultado *= potencia(punto[i], exponente);
    }

    return resultado;
}


// CALCULAR EL GRADIENTE COMPLETO DE UNA FUNCIÓN
void calcular_gradiente(Function *funcion, double *punto, double *gradiente) {

    for(int variable = 0; variable < funcion->num_variables; variable++) {
        double derivada = 0.0;

        for(int m = 0; m < funcion->num_monomios; m++) {
            derivada += derivar_monomio(&funcion->monomios[m], punto, funcion->num_variables, variable);
        }

        gradiente[variable] = derivada;
    }
}


void calcular_gradientes(Function *funciones, int num_funciones, double *punto, double **gradientes) {
    for(int i = 0; i < num_funciones; i++) {
        calcular_gradiente(&funciones[i], punto, gradientes[i]);
    }
}

int main()
{
    int num_funciones = 2;

    // ARRAY DE FUNCIONES
    Function *funciones = malloc(num_funciones * sizeof(Function));


    /* ========================================
       FUNCIÓN 0

       f1(x,y,z) = 3xy + 4yz + 2x + 5
       ======================================== */

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



    /* ========================================
       FUNCIÓN 1

       f2(x,y,z) = x² + yz + 3z
       ======================================== */

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


    /* ========================================
       PUNTO DE EVALUACIÓN
       ======================================== */

    double punto[] = {1.0, 2.0, 3.0};


    /* ========================================
       RESERVAR LOS GRADIENTES

       gradientes[0] -> gradiente función 0
       gradientes[1] -> gradiente función 1
       ======================================== */

    double **gradientes = malloc(num_funciones * sizeof(double *));

    for(int f = 0; f < num_funciones; f++) {
        gradientes[f] = malloc(funciones[f].num_variables * sizeof(double));
    }


    /* ========================================
       CALCULAR TODOS LOS GRADIENTES
       ======================================== */

    calcular_gradientes(funciones, num_funciones, punto, gradientes);


    /* ========================================
       MOSTRAR RESULTADOS
       ======================================== */

    for(int f = 0; f < num_funciones; f++) {
        printf("Gradiente funcion %d: ", f);

        for(int v = 0; v < funciones[f].num_variables; v++) {
            printf("%.2f ", gradientes[f][v]);
        }

        printf("\n");
    }


    /* ========================================
       LIBERAR MEMORIA
       ======================================== */

    for(int f = 0; f < num_funciones; f++) {
        for(int m = 0; m < funciones[f].num_monomios; m++) {
            free(funciones[f].monomios[m].exponentes);
        }

        free(funciones[f].monomios);
        free(gradientes[f]);
    }

    free(gradientes);
    free(funciones);

    return 0;
}
