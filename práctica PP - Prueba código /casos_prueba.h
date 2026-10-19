#ifndef CASOS_PRUEBA_H
#define CASOS_PRUEBA_H

#include "gradiente.h"

Function *crear_funciones_usuario(int num_funciones, int num_variables, int num_monomios);

double *crear_punto_usuario(int num_variables);

double **crear_gradientes(Function *funciones, int num_funciones);

void liberar_funciones(Function *funciones, int num_funciones);

void liberar_gradientes(double **gradientes, int num_funciones);

#endif
