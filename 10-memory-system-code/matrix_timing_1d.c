#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>               // for clock() and other functions
#include <stdio.h>
#include <sys/time.h>

int main(int argc, char *argv[]){

  if(argc < 3){
    printf("usage: %s <rows> <cols> [which]\n",argv[0]);
    printf(" which is one of:\n");
    printf("   both : do both row- and col-wise summing (default)\n");
    printf("   row  : do only the row-wise summing\n");
    printf("   col  : do only the column-wise summing\n");
    return 1;
  }

  int rows = atoi(argv[1]);
  int cols = atoi(argv[2]);
  int do_row=1, do_col=1;

  if(argc > 3){
    if(strcmp(argv[3],"both")==0){ }
    else if(strcmp(argv[3],"row")==0){
      do_col=0;
    }
    else if(strcmp(argv[3],"col")==0){
      do_row=0;
    }
    else{
      printf("Unknown option '%s'\n",argv[3]);
      return 1;
    }
  }
  int *mat = malloc(rows*cols*sizeof(int));
  for(int i=0; i<rows*cols; i++){ // fill sequentially
    mat[i] = i;
  }

  clock_t begin, end;
  struct timeval tv1, tv2;

  if(do_row){
    gettimeofday(&tv1, NULL);
    begin = clock();                 // get current moment
    int sumR = 0;
    for(int i=0; i<rows; i++){
      for(int j=0; j<cols; j++){
        sumR += mat[i*cols + j];
      }
    }
    end = clock();                   // get later moment to compare to start
    gettimeofday(&tv2, NULL);

    double rowwise_cpu_time = ((double) (end - begin)) / CLOCKS_PER_SEC;
    double rowwise_wall_time = 
      ((double) (tv2.tv_usec - tv1.tv_usec) / 1000000) +
      ((double) (tv2.tv_sec - tv1.tv_sec));

    printf("sumR: %ld row-wise CPU time: %.3f sec, Wall time: %.3f \n",
           sumR,rowwise_cpu_time,rowwise_wall_time);
  }

  if(do_col){
    gettimeofday(&tv1, NULL);
    begin = clock();                 // get current moment
    int sumC = 0;
    for(int j=0; j<cols; j++){
      for(int i=0; i<rows; i++){
        sumC += mat[i*cols + j];
      }
    }
    end = clock();                   // get later moment to compare to start
    gettimeofday(&tv2, NULL);
    double colwise_cpu_time = ((double) (end - begin)) / CLOCKS_PER_SEC;
    double colwise_wall_time = 
      ((double) (tv2.tv_usec - tv1.tv_usec) / 1000000) +
      ((double) (tv2.tv_sec - tv1.tv_sec));
    printf("sumC: %ld col-wise CPU time: %.3f sec, Wall time: %.3f \n",
           sumC,colwise_cpu_time,colwise_wall_time);
  }
  free(mat);
  return 0;
}

