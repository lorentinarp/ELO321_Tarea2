/*
* @file   : C.c
* @author : Camilo Donoso Collao
*           Loreto Romero Ponce
* @date   : 19/12/2020
* @brief  : C�digo para tarea 02 en ELO 321, semestre 2020-2
*           Corresponde a la parte C.
*/

#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>

/* Variables globales */

struct timeval tv1, tv2;

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
};

/* Declaraci�n de funciones */

/*
 * @brief   : hace un chequeo de un �rea dada de sudoku_array
 * @param A : estructura que contiene los �ndices del �rea a chequear del arreglo bidimensional
 * @return  : 
 */
void* validity_check(void*);

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

  /* Tomar medici�n de tiempos para obtener promedio de las repeticiones */
  for (i = 0; i < repeticiones; i++) {
    /* Punto de referencia de inicio */
    gettimeofday(&tv1, NULL);

    /* Ejecutar un proceso de revisi�n completa de sudoku_array */
    valida = sol_con_threads_POSIXAPI();

    /* Punto de referencia de fin, cuando todos los threads terminaron su trabajo */
    gettimeofday(&tv2, NULL);

    /* Imprimir tiempo que tard� un proceso de revisi�n */
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

  return;
}

void* validity_check(void*) { //MODIFICAR PARA C
  int i, j, k;
  int B[9] = { 0,0,0,0,0,0,0,0,0 };

  /* Modificar las posiciones de B seg�n los d�gitos presentes en sudoku_array */
  for (i = A.init_row; i <= A.fin_row; i++) {
    for (j = A.init_col; j <= A.fin_col; j++) {
      for (k = 0; k < 9; k++) {
        if ((sudoku_array[i][j] == k + 1) && (B[k] == 0)) {
          B[k] = 1;
        }
      }
    }
  }

  for (k = 0; k < 9; k++) {
    /* Revisar si hay alg�n d�gito entre 1 y 9 que est� ausente en B[9] */
    if (B[k] == 0) {
      return 0;
    }
  }

  /* En caso de que todos los d�gitos del 1 al 9 est�n en B[9] */
  return 1;
}

int sol_con_threads_POSIXAPI() { //MODIFICAR PARA C
  struct Area A;
  int i, j;
  int sol_valida = 1;

  /* Chequeo de filas */
  for (i = 0; i < 9; i++) {
    A.init_row = i;
    A.fin_row = i;
    A.init_col = 0;
    A.fin_col = 8;
    rows_checked[i] = validity_check();
  }

  /* Chequeo de columnas*/
  for (i = 0; i < 9; i++) {
    A.init_row = 0;
    A.fin_row = 8;
    A.init_col = i;
    A.fin_col = i;
    cols_checked[i] = validity_check();
  }

  /* Chequeo de casillas*/
  int k = 0;
  for (i = 0; i < 3; i++) {
    for (j = 0; j < 3; j++) {
      A.init_row = i * 3;
      A.fin_row = i * 3 + 2;
      A.init_col = j * 3;
      A.fin_col = j * 3 + 2;
      sub_grids_checked[k] = validity_check();
      k++;
    }
  }

  /* Revisar si hay alg�n chequeo igual a 0 para todas las filas, columnas y subcuadr�culas */
  for (i = 0; i < 9; i++) {
    if ((rows_checked[i] == 0) || (cols_checked[i] == 0) || (sub_grids_checked[i] == 0)) {
      sol_valida = 0;
    }
  }

  return sol_valida;
}