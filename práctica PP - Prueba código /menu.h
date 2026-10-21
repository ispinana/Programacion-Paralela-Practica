#ifndef MENU_H
#define MENU_H

typedef struct {
    int modo;
    int tipo_problema;
    int num_funciones;
    int num_variables;
    int num_monomios;
    int opcion_funciones;
    int opcion_punto;
} OpcionesMenu;

OpcionesMenu mostrar_menu(void);

#endif
