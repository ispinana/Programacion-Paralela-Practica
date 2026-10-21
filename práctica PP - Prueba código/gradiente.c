#include "gradiente.h"

double potencia(double base, int exponente) {

    double resultado = 1.0;

    for(int i = 0; i < exponente; i++) {
        resultado *= base;
    }

    return resultado;
}

double derivar_monomio(Monomio *monomio, double *punto, int num_variables, int variable) {

    if(monomio->exponentes[variable] == 0) {
        return 0.0;
    }

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

void calcular_gradiente(Function *funcion, double *punto, double *gradiente) {

    for(int variable = 0; variable < funcion->num_variables; variable++) {

        double derivada = 0.0;

        for(int m = 0; m < funcion->num_monomios; m++) {

            derivada += derivar_monomio(
                &funcion->monomios[m],
                punto,
                funcion->num_variables,
                variable
            );
        }

        gradiente[variable] = derivada;
    }
}

void calcular_gradientes(Function *funciones, int num_funciones, double *punto, double **gradientes) {

    for(int i = 0; i < num_funciones; i++) {

        calcular_gradiente(
            &funciones[i],
            punto,
            gradientes[i]
        );
    }
}
