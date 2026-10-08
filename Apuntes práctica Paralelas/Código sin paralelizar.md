# Cálculo de un gradiente
Tenemos una función:
```text
f(x, y, z) = 3xy + 4yz + 2x + 5
```

El gradiente se hace calculando la derivada de cada variable:

```text
∇f = (∂f/∂x, ∂f/∂y, ∂f/∂z)
```

___
## 1. Derivar cada variable de la función
### Respecto de {x}
- Variable: **3xy**
- Derivada: 3y

+ Variable: **4yz**
+ Derivada: 0

* Variable: **2x**
* Derivada: 2

- Variable: **5**
- Derivada: 0

RESULTADO: 3y + 2
### Respecto de {y}

- Variable: **3xy**
- Derivada: 3x

+ Variable: **4yz**
+ Derivada: 4z

* Variable: **2x**
* Derivada: 0

- Variable: **5**
- Derivada: 0

RESULTADO: 3x + 4z
### Respecto de {y}

- Variable: **3xy**
- Derivada: 0

+ Variable: **4yz**
+ Derivada: 4y

* Variable: **2x**
* Derivada: 0

- Variable: **5**
- Derivada: 0

RESULTADO: 4y
## 2. Juntar las tres derivadas
Al juntarlo, queda tal que así:
```text
∇f(x, y, z) = (3y + 2, 3x + 4z, 4y)
```

Ahora, el enunciado como tal utiliza la equivalencia donde: (x, y, z) = (1, 2, 3), por lo que al sustituir cada valor se obtiene lo siguiente:

```text
∇f(x, y, z) = (3*2 + 2, 3*1 + 4*3, 4*2)
∇f(x, y, z) = 8, 15, 8)
```

# Aplicación del cálculo al codigo
La apicación del codigo a nivel estructural es separar la función en cada monomio, donde trabaja en cada iteración con una variable concreta, es decir:

```text
                 FUNCIÓN
        3xy + 4yz + 2x + 5
                 |
                 v
        ---------------------
        |         |         |
        x         y         z
        |         |         |
       df/dx     df/dy     df/dz
        |         |         |
        8         15        8
```
Y el vector resultado que usamos como ejemplo:
```text
[8, 15, 8]
```

## 1. Representación del monomio en C
La forma de representar cada monomio de la función en el codigo es mediante un typedef struct tal que asi:
```C
typedef struct {
    double coeficiente;
    int *exponentes;
} Monomio;
```

Para la presentación total de toda la función, sería asi:
3xy + 4yz + 2x + 5

| Monomio | coeficiente |   x |   y |   z |
| ------- | ----------: | --: | --: | --: |
| \(3xy\) |           3 |   1 |   1 |   0 |
| \(4yz\) |           4 |   0 |   1 |   1 |
| \(2x\)  |           2 |   1 |   0 |   0 |
| \(5\)   |           5 |   0 |   0 |   0 |
Por lo que a nivel interno, según en la estructura definida seria tal que:
```text
monomio[0]
    coeficiente = 3
    exponentes = [1,1,0]

monomio[1]
    coeficiente = 4
    exponentes = [0,1,1]

monomio[2]
    coeficiente = 2
    exponentes = [1,0,0]

monomio[3]
    coeficiente = 5
    exponentes = [0,0,0]
```

## 2. Representación de la función en C
Para representar la función, seguiríamos este otro modo:
```C
typedef struct {
    int num_variables;
    int num_monomios;
    Monomio *monomios;
} Funcion;
```

Que únicamente indica cuántas variables tiene, cuántos términos y donde estan almacenados, algo asi como los tamaños y posiciones generales. Para nuestro ejemplo, seria tal que asi:
```C
funcion.num_variables = 3;
funcion.num_monomios = 4;
```
Porque las variables serian: [x, y, z], mientras que los monomios son: [3, 4, 2, 5]

## 3. función calcular_gradiente()
La función calcular_gradiente pide como parametros una Funcion, un double llamado punto y otro llamado gradiente.

Esto a niveles conceptuales, la Función es como tal la propia función, el punto se refiere a si es [x, y, z] y el gradiente es el resultado donde se almacenará.

### Primer bucle: recorrer variables
El bucle for de esta función recorre todos los puntos [x, y, z], de esta manera habrá un total de 3 iteraciones, donde se calculará la derivada respectivamente de cada una:
```C
for (int variable = 0; variable < funcion->num_variables; variable++)
```

En cada iteración, la variable double derivada lo que hará será ir sumándose a cada derivada que se ejecute, por ejemplo:
```text
derivada = 0

3xy aporta 6
derivada = 6

4yz aporta 0
derivada = 6

2x aporta 2
derivada = 8

5 aporta 0
derivada = 8
```

Siendo el total de df/dx = 8.

### Segundo bucle: recorrer monomios
Teniendo este bucle:
```C
for (int m = 0; m < funcion->num_monomios; m++)
```

Se deriva el monomio en según cada iteración, realizando la función con dicho nombre.
```C
derivada += 
derivar_monomio(&funcion->monomios[m], punto, funcion->num_variables, variable
);
```

## 4. función derivar_monomio()
Esta función recibe como parámetros el propio monomio, el punto en el que se encuentra, los números de variables y la variable que estamos derivando.

Si estuvieramos en la primera iteración, seria tal que:
```text
monomio = 3xy
punto = (1,2,3)
variable = x
```

La primera comprobación al derivar es si el monomio contiene la variable respecto a la que estoy derivando ahora mismo, la que me interesa. En caso de que no la tenga, siemplemente se pondrá a 0:
```C
if (monomio->exponentes[variable] == 0) {
    return 0.0;
}
```

Como en el caso de ejemplo, 3xy tiene en monomios: [1, 1, 0] de [x, y, z], pasa este filtro sin problema. 

Entonces, en este caso aplicamos la regla de la derivada, que es:
```C
double resultado = monomio->coeficiente * monomio->exponentes[variable];
```

Es decir:
```text
resultado = 3 * 1
```

### Tercer bucle
Teniendo:
```C
for (int i = 0; i < num_variables; i++)
```

Este bucle recorren las variables [x, y, z] para que, después de haber derivado, se calcule el monomio resultante del punto. En caso de 3xy, el resultado para el coeficiente es 3 porque se calculó con 1, y para la variable "x" se debe de restar su exponente.
```C
int exponente = monomio->exponentes[i];

if (i == variable) {
    exponente--;
}

resultado *= potencia(punto[i], exponente)
```

Lo que implica:
```text
x --> x^n-1

x^1 = x^0 = 1

Resultado: 3y
```

## 5. Función potencia()
Lo único que hace esta función es calcular  la base sobre su exponente, es decir:
```text
2^3 = 2 * 2 * 2
```

# Recorrido completo: resumen

```text
main
 |
 | crea la función:
 | 3xy + 4yz + 2x + 5
 |
 | crea el punto:
 | (1,2,3)
 |
 v
calcular_gradiente
 |
 +-------------------------------------+
 | variable = x                        |
 |                                     |
 |   monomio 3xy -> 6                  |
 |   monomio 4yz -> 0                  |
 |   monomio 2x  -> 2                  |
 |   monomio 5   -> 0                  |
 |                                     |
 |   suma = 8                           |
 +-------------------------------------+
 |
 +-------------------------------------+
 | variable = y                        |
 |                                     |
 |   3xy -> 3                          |
 |   4yz -> 12                         |
 |   2x  -> 0                          |
 |   5   -> 0                          |
 |                                     |
 |   suma = 15                          |
 +-------------------------------------+
 |
 +-------------------------------------+
 | variable = z                        |
 |                                     |
 |   3xy -> 0                          |
 |   4yz -> 8                          |
 |   2x  -> 0                          |
 |   5   -> 0                          |
 |                                     |
 |   suma = 8                           |
 +-------------------------------------+
 |
 v

gradiente = [8,15,8]
```

# ¿Dónde paralelizar? 

Especialmente, la paralelización seria en el bucle dentro de la función de calcular el gradiente:
```C
for (int variable = 0; variable < funcion->num_variables; variable++)
```

Y también en la derivación de monomios, es decir, en el otro bucle dentro del anterior:
```C
for (int m = 0; m < funcion->num_monomios; m++) {
    derivada += derivar_monomio(...);
}
```

