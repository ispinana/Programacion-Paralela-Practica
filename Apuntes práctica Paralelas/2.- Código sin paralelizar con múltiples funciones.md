Partiendo de la base del código anterior, al no tener que cambiar como tal la lógica del código anterior sino más bien poner una nueva función superior a la que ya calcula el propio gradiente a partir de una función, el cambio viene precedido justamente de crear una función que toma la función del gradiente para realizar el cálculo por múltiples funciones.

## 1. Función calcular_gradientes()
Obtiene como parametros un array de funciones, su tamaño, el punto y un array de gradientes, donde se almacenara el resultado obtenido en cada cálculo.
```C
void calcular_gradientes(Function *funciones, int num_funciones, double *punto, double **gradientes) {
    for(int i = 0; i < num_funciones; i++) {
        calcular_gradiente(&funciones[i], punto, gradientes[i]);
    }
}

```
Esto, más adelante se podrá paralelizar fácilmente con pragma, bajo el comando:
`pragma omp parallel for`.

## 2. Modificación de la función main()
En main, simplemente he añadido la lógica nueva con dos arrays:
`f1 (x,y,z) = 3xy + 4yz + 2x + 5` y `f2 (x,y,z) = x^2 + yz + 3z`.

Después de crearlos, añadimos el punto de evaluación y lo siguiente ya es utilizar el método principal de calcular_gradientes(), para posteriormente mostrar sus resultados y liberar la memoria. 