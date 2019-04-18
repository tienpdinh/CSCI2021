// func_v_macro.c: demonstrate timing differences between using
// function calls and macros. The mget()/vset() functions and
// MGET()/VSET() macros behave the same but macros do not involve
// control jumps so lead to better efficiency without
// optimizations. Performing function inlining such as is done at gcc
// -O3 will lead to near identical performance as the bodies of the
// small functions will be inserted at their call sites just like the
// macros are.

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>               // for clock() and other functions
#include <stdio.h>
#include <sys/time.h>
#include "matvec.h"

int mget(matrix_t mat, int i, int j){
  return mat.data[i*mat.cols + j];
}
int vset(vector_t vec, int i, int x){
  return vec.data[i] = x;
}

void row_sumsA(matrix_t mat, vector_t sums){
  for(int i=0; i<mat.rows; i++){
    int sum = 0;
    for(int j=0; j<mat.cols; j++){
      sum += mget(mat,i,j);
    }
    vset(sums, i, sum);
  }
}

#define MGET(mat,i,j) ((mat).data[((i)*((mat).cols)) + (j)])
#define VSET(vec,i,x) ((vec).data[(i)] = (x))

void row_sumsB(matrix_t mat, vector_t sums){
  for(int i=0; i<mat.rows; i++){
    int sum = 0;
    for(int j=0; j<mat.cols; j++){
      sum += MGET(mat,i,j);
    }
    VSET(sums, i, sum);
  }
}

int main(int argc, char *argv[]){

  if(argc < 3){
    printf("usage: %s <rows> <cols> \n",argv[0]);
    return 1;
  }

  int rows = atoi(argv[1]);
  int cols = atoi(argv[2]);


  // Allocate the matrix and fill it in with 1,2,3,4...
  matrix_t mat;
  int ret = matrix_init(&mat, rows,cols);
  matrix_fill_sequential(mat);

  // Variables for timing
  clock_t begin, end;
  double cpu_time;


  vector_t sumsA;
  vector_init(&sumsA, mat.rows);
  begin = clock();
  row_sumsA(mat,sumsA);
  end = clock();
  cpu_time = ((double) (end - begin)) / CLOCKS_PER_SEC;
  printf("row_sumsA: %.4e secs\n",cpu_time);    

  
  vector_t sumsB;
  vector_init(&sumsB, mat.rows);
  begin = clock();
  row_sumsB(mat,sumsB);
  end = clock();
  cpu_time = ((double) (end - begin)) / CLOCKS_PER_SEC;
  printf("row_sumsB: %.4e secs\n",cpu_time);    

  matrix_free_data(&mat);
  vector_free_data(&sumsA);
  vector_free_data(&sumsB);

  return 0;
}
