#ifndef CASOS_PRUEBA_H
#define CASOS_PRUEBA_H

#include "gradiente.h"

Function *crear_caso_basico(int *num_funciones); // Crea el caso conceptual de dos funciones que estamos utilizando actualmente
double *crear_punto_basico(); // Crea el punto (1,2,3)

Function *crear_funciones_prueba(int num_funciones, int num_variables, int num_monomios); // Crea las funciones de prueba segun la cantidad impuesta por el usuario
Function *crear_funciones_usuario(int num_funciones, int num_variables, int num_monomios); // Crea las funciones y asigna el valor de cada coeficiente por el usuario
double *crear_punto(int num_variables); // Crea los puntos en funcion de la cantidad de variables impuesta por el usuario
double *crear_punto_usuario(int num_variables); // Asigna los puntos elegidos por el usuario

double **crear_gradientes(Function *funciones, int num_funciones); // Reserva memoria para los gradientes

void liberar_funciones(Function *funciones, int num_funciones); // Libera las funciones
void liberar_gradientes(double **gradientes, int num_funciones); // Libera los gradientes

#endif
