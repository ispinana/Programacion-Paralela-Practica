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

