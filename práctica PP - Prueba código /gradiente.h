
#ifndef GRADIENTE_H
#define GRADIENTE_H

/*
    Representación de un monomio. Ejemplo:

    3xy

    coeficiente = 3
    exponentes = [1, 1, 0]
*/
typedef struct {
    double coeficiente;
    int *exponentes;
} Monomio;


// Representación de una función.
typedef struct {
    int num_variables;
    int num_monomios;
    Monomio *monomios;
} Function;


double potencia(double base, int exponente); // Calcula base^exponente.
double derivar_monomio(Monomio *monomio, double *punto, int num_variables, int variable); // Calcula la derivada de un monomio respecto a una variable concreta.
void calcular_gradiente(Function *funcion, double *punto, double *gradiente); // Calcula el gradiente de una función.
void calcular_gradientes(Function *funciones, int num_funciones, double *punto, double **gradientes); // Calcula los gradientes de varias funciones.

#endif
