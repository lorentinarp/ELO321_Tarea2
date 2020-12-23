# ELO321_Tarea2

Integrantes:
- Camilo Donoso Collao     201521040-3     camilo.donoso@sansano.usm.cl
- Loreto Romero Ponce      201554001-2     loreto.romero@sansano.usm.cl


## Parte A
La parte A de la tarea se desarrolló en un código, A.c, este realiza el chequeo de un arreglo bidimensional global donde se encuentra 
la posible solución de un Sudoku para saber si la solución es correcta o no. El programa esta diseñado para chequear un número determinado
de veces, en este caso se realiza 100 veces, y se calcula el tiempo que tarda cada chequeo para luego realizar un promedio del tiempo.
Este programa no utiliza hilos.

El programa A.c se compila de la siguiente manera:

  gcc A.c -o A 

y se ejecuta de la siguiente manera:

  ./A  

## Parte B
La parte B se desarrolló en el código B.c, este realiza el chequeo de un arreglo bidimensional global donde se encuentra la posible solución
a un Sudoku. El programa ejecuta la verificación del arreglo un número determinado de veces, en este caso 100 veces, y luego calcula el tiempo
que tardó en cada verificación para luego calcular un promedio de tiempo. El programa utiliza OpenMP API para ejecutar secciones del código 
en paralelo (multi-threading).

El programa B.c se compila de la siguiente manera:

  gcc -o B -fopenmp B.c

Para seleccionar el máximo de hilos a usar se utiliza el siguiente comando:

  export OMP_NUM_THREADS=10

Se debe ingresar un número entero que indique cuantos hilos utilizar, en este caso son 10 hilos.

Para ejecutar el programa:

  ./B  

## Parte C
La parte C se desarrolló en el código C.c, este realiza el chequeo de un arreglo bidimensional global donde se encuentra la posible solución
a un Sudoku. El programa ejecuta la verificación del arreglo un número determinado de veces, en este caso 100 veces, y luego calcula el tiempo
que tardó en cada verificación para luego calcular un promedio de tiempo. El programa utiliza POSIX API para generar 27 hilos, de los cuales
9 son para verificar las filas del arreglo, 9 para las columnas y 9 para las subgrillas.

El programa C.c se compila de la siguiente manera:

  gcc C.c -o C -lpthread

Y se ejecuta de la siguiente manera:

 ./C

## Parte D
La parte D de la tarea se desarrolló en un texto, report.txt, donde se explican las conclusiones de esta tarea.



