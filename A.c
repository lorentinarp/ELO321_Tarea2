/*
* @file   : A.c
* @author : Camilo Donoso Collao
*           Loreto Romero Ponce
* @date   : xx/12/2020
* @brief  : Código para tarea 02 en ELO 321, semestre 2020-2
*           Corresponde a la parte A.
*/

#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>

/* Variables globales */

struct timeval tv1, tv2;

int sudoku_array [9][9]={
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

int rows_checked[9] = {0,0,0,0,0,0,0,0,0};

int cols_checked[9] = {0,0,0,0,0,0,0,0,0};

int sub_grids_checked[9] = {0,0,0,0,0,0,0,0,0};

struct Area
{
  int init_row;
  int fin_row;
  int init_col;
  int fin_col;
};

/* Declaración de funciones */

/*
 * @brief   : hace un chequeo de un área dada de sudoku_array
 * @param A : estructura que contiene los índices del área a chequear del arreglo bidimensional
 * @return  : si falta algún dígito entre 1 y 9, retorna 0; en otro caso, retorna 1
 */
int validity_check(struct Area A);

int main(){
  /* Punto de referencia de inicio */
  gettimeofday(&tv1, NULL); 

  struct Area A;
  int i,j;
  int sol_valida = 1;

  /* Chequeo de filas */
  for (i = 0 ; i < 9 ; i++){
    A.init_row = i;
    A.fin_row = i;
    A.init_col = 0;
    A.fin_col = 8;
    rows_checked[i] = validity_check(A);
  }

  /* Chequeo de columnas*/
  for (i = 0 ; i < 9 ; i++){
    A.init_row = 0;
    A.fin_row = 8;
    A.init_col = i;
    A.fin_col = i;
    cols_checked[i] = validity_check(A);
  }

  /* Chequeo de casillas*/
  int k = 0;
  for (i = 0 ; i < 3 ; i++){
    for (j = 0 ; j < 3 ; j++){
      A.init_row = i*3;
      A.fin_row = i*3+2;
      A.init_col = j*3;
      A.fin_col = j*3+2;
      sub_grids_checked[k] = validity_check(A);
      k++;
    }
  }

  /* Revisar si hay algún chequeo igual a 0 para todas las filas, columnas y subcuadrículas */
  for (i = 0 ; i < 9 ; i++){
    if ((rows_checked[i] == 0) || (cols_checked[i] == 0) || (sub_grids_checked[i] == 0)){
      sol_valida = 0;
    }
  }

  /* Punto de referencia de fin */
  gettimeofday(&tv2, NULL);
  printf("Time = %f sec\n", (double)(tv2.tv_usec - tv1.tv_usec) / 1000000.0 +
      (double)(tv2.tv_sec - tv1.tv_sec));

  /* Imprimir resultado de evaluación de sudoku_array */
  if (sol_valida == 0)
    printf("No es solución válida\n");
  else 
    printf("Es solución válida\n");

  return sol_valida;
}

int validity_check(struct Area A){
  int i,j,k;
  int B[9] = {0,0,0,0,0,0,0,0,0};

  /* Modificar las posiciones de B según los dígitos presentes en sudoku_array */
  for (i = A.init_row; i <= A.fin_row  ; i++){
    for (j = A.init_col ; j <= A.fin_col ; j++){
      for (k = 0 ; k < 9 ; k++){
        if ((sudoku_array[i][j] == k+1) && (B[k] == 0)){
          B[k] = 1;
        }
      }
    }
  }

  for (k = 0 ; k < 9 ; k++){
    /* Revisar si hay algún dígito entre 1 y 9 que esté ausente en B[9] */
    if (B[k] == 0) {
      return 0;
    }
  }

  /* En caso de que todos los dígitos del 1 al 9 estén en B[9] */
  return 1;
}