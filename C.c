/*
* @file   : C.c
* @author : Camilo Donoso Collao
*           Loreto Romero Ponce
* @date   : 19/12/2020
* @brief  : Código para tarea 02 en ELO 321, semestre 2020-2
*           Corresponde a la parte C.
*/

#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <pthread.h>

/* Variables globales */

struct timeval tv1, tv2;

/* Mutex lock */
pthread_mutex_t lock; 

int sudoku_array[9][9] = {
  {6,2,4,5,3,9,1,8,7},
  {5,1,9,7,2,8,6,3,4},
  {8,3,7,6,1,4,2,9,5},
  {1,4,3,8,6,5,7,2,9},
  {9,5,8,2,4,7,3,6,1},
  {7,6,2,3,9,1,4,5,8},
  {3,7,1,9,5,6,8,4,2},
  {4,9,6,1,8,2,5,7,3},
  {2,8,5,4,7,3,9,1,6}
};

int rows_checked[9] = { 0,0,0,0,0,0,0,0,0 };

int cols_checked[9] = { 0,0,0,0,0,0,0,0,0 };

int sub_grids_checked[9] = { 0,0,0,0,0,0,0,0,0 };

struct Area
{
  int init_row;
  int fin_row;
  int init_col;
  int fin_col;
  int *pnt; /* Este es un puntero a un elemento del arreglo de filas, columnas o grillas*/
};

/* Declaracion de funciones */

/*
 * @brief   : hace un chequeo de un area dada de sudoku_array
 * @param A : estructura que contiene los andices del area a chequear del arreglo bidimensional
 * @return  : 
 */
void* validity_check(void *arg);

/*
 * @brief   : hace la revisi�n completa de sudoku_array con threads generados con POSIX API
 * @param - : -
 * @return  : si chequeo falla, retorna 0; en otro caso, retorna 1
 */
int sol_con_threads_POSIXAPI();

int main() { 
  int repeticiones = 100;
  int i;
  int valida = 1;
  double promedio = 0.0;

  /* Tomar medicion de tiempos para obtener promedio de las repeticiones */
  for (i = 0; i < repeticiones; i++) {
    /* Punto de referencia de inicio */
    gettimeofday(&tv1, NULL);

    /* Ejecutar un proceso de revision completa de sudoku_array */
    valida = sol_con_threads_POSIXAPI();

    /* Punto de referencia de fin, cuando todos los threads terminaron su trabajo */
    gettimeofday(&tv2, NULL);

    /* Imprimir tiempo que tardo un proceso de revision */
    double t = (double)(tv2.tv_usec - tv1.tv_usec) / 1000000.0 + (double)(tv2.tv_sec - tv1.tv_sec);
    printf("Time = %f sec\n", t);

    promedio += t;
  }

  /* Imprimir tiempo que tardaron las repeticiones en promedio */
  promedio = promedio / (double)repeticiones;
  printf("Time promedio = %f sec\n", promedio);

  /* Imprimir resultado de evaluaci�n de sudoku_array */
  if (valida == 0)
    printf("Contenido del arreglo no es soluci�n v�lida.\n");
  else
    printf("Contenido del arreglo es soluci�n v�lida.\n");

  return 0;
}

void* validity_check(void *arg) {
  int i, j, k;
  int B[9] = { 0,0,0,0,0,0,0,0,0 };
  struct Area *A = arg;

  /* Modificar las posiciones de B segun los digitos presentes en sudoku_array */
  for (i = A->init_row; i <= A->fin_row; i++) {
    for (j = A->init_col; j <= A->fin_col; j++) {
      for (k = 0; k < 9; k++) {
        if ((sudoku_array[i][j] == k + 1) && (B[k] == 0)) {
          B[k] = 1;
        }
      }
    }
  }

  int exit = 1;
  k = 0;
  while ((k < 9) && (exit != 0)){
    /* Revisar si hay algun digito entre 1 y 9 que este ausente en B[9] */
    if (B[k] == 0) {
      exit = 0;
    }
    k++;
  }
  (*A->pnt) = exit;
}

int sol_con_threads_POSIXAPI() {
  /* Para evitar que el area sea modificada antes de que la función validity_check la pueda leer,
  se hizo una estructura para cada fila, columan y grilla a revisar*/
  struct Area rows[9], cols[9], grids[9];
  int i, j;
  int sol_valida = 1;

  /* ID de los hilos */
  pthread_t threadID[27];

  /* Chequeo de filas */
  for (i = 0; i < 9; i++) {
    rows[i].init_row = i;
    rows[i].fin_row = i;
    rows[i].init_col = 0;
    rows[i].fin_col = 8;
    rows[i].pnt = &rows_checked[i];
    pthread_create(&threadID[i], NULL, validity_check, &rows[i]);
  }

  /* Chequeo de columnas*/
  for (i = 0; i < 9; i++) {
    cols[i].init_row = 0;
    cols[i].fin_row = 8;
    cols[i].init_col = i;
    cols[i].fin_col = i;
    cols[i].pnt = &cols_checked[i];
    pthread_create(&threadID[i+9], NULL, validity_check, &cols[i]);
  }

  /* Chequeo de casillas*/
  int k = 0;
  for (i = 0; i < 3; i++) {
    for (j = 0; j < 3; j++) {
      grids[k].init_row = i * 3;
      grids[k].fin_row = i * 3 + 2;
      grids[k].init_col = j * 3;
      grids[k].fin_col = j * 3 + 2;
      grids[k].pnt = &sub_grids_checked[k];
      pthread_create(&threadID[k+18], NULL, validity_check, &grids[k]);
      k++;
    }
  }

  for(i = 0; i < 27;i++){
    pthread_join(threadID[i], NULL);
  }

  /* Revisar si hay algun chequeo igual a 0 para todas las filas, columnas y subcuadriculas */
  for (i = 0; i < 9; i++) {
    if ((rows_checked[i] == 0) || (cols_checked[i] == 0) || (sub_grids_checked[i] == 0)) {
      sol_valida = 0;
    }
  }
  return sol_valida;
}