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

int main()
{
    // f(x, y, z) = 3xy + 4yz + 2x + 5

    Function funcion;
    funcion.num_variables = 3;
    funcion.num_monomios = 4;

    funcion.monomios = malloc(funcion.num_monomios * sizeof(Monomio));

    // Cada monomio necesita un array de exponente, por lo que inicializamos todo a 0
    for(int i = 0; i < funcion.num_monomios; i++) {
        funcion.monomios[i].exponentes = calloc(funcion.num_variables, sizeof(int));
    }

    // MONOMIO 0 --> 3xy
    funcion.monomios[0].coeficiente = 3;
    funcion.monomios[0].exponentes[0] = 1; //x
    funcion.monomios[0].exponentes[1] = 1; //y
    funcion.monomios[0].exponentes[2] = 0; //z

    // MONOMIO 1 --> 4yz
    funcion.monomios[1].coeficiente = 4;
    funcion.monomios[1].exponentes[0] = 0; //x
    funcion.monomios[1].exponentes[1] = 1; //y
    funcion.monomios[1].exponentes[2] = 1; //z

    // MONOMIO 2 --> 2x
    funcion.monomios[2].coeficiente = 2;
    funcion.monomios[2].exponentes[0] = 1; //x
    funcion.monomios[2].exponentes[1] = 0; //y
    funcion.monomios[2].exponentes[2] = 0; //z

    // MONOMIO 3 --> 5
    funcion.monomios[3].coeficiente = 5;
    funcion.monomios[3].exponentes[0] = 0; //x
    funcion.monomios[3].exponentes[1] = 0; //y
    funcion.monomios[3].exponentes[2] = 0; //z


    // PUNTO DONDE EVALUAMOS: (x, y, z) = (1, 2, 3)
    double punto[] = {1.0, 2.0, 3.0};

    //Guardar derivadas
    double gradiente[3];

    calcular_gradiente(&funcion, punto, gradiente);

    printf("Gradiente: \n");
    for(int i = 0; i < funcion.num_variables; i++) {
        printf("%.2f ", gradiente[i]);
    }

    printf("\n");

    // LIBERAR MEMORIA
    for(int i = 0; i < funcion.num_monomios; i++) {
        free(funcion.monomios[i].exponentes);
    }

    free(funcion.monomios);

    return 0;
}
