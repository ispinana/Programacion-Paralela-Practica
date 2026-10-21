#ifndef GRADIENTE_H
#define GRADIENTE_H

typedef struct {
    double coeficiente;
    int *exponentes;
} Monomio;

typedef struct {
    int num_variables;
    int num_monomios;
    Monomio *monomios;
} Function;

double potencia(double base, int exponente);

double derivar_monomio(
    Monomio *monomio,
    double *punto,
    int num_variables,
    int variable
);

void calcular_gradiente(
    Function *funcion,
    double *punto,
    double *gradiente
);

void calcular_gradientes(
    Function *funciones,
    int num_funciones,
    double *punto,
    double **gradientes
);

#endif
