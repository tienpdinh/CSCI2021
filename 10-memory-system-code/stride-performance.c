#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>               // for clock() and other functions
#include <stdio.h>
#include <sys/time.h>

int main(int argc, char *argv[]){

  if(argc < 4){
    printf("usage: %s <length> <stride1> <stride2>\n",argv[0]);
    return 1;
  }

  int length  = atoi(argv[1]);
  int stride1 = atoi(argv[2]);
  int stride2 = atoi(argv[3]);

  int *data = malloc(length*sizeof(int));
  for(int i=0; i<length; i++){
    data[i] = i;
  }

  clock_t begin, end;
  struct timeval tv1, tv2;

  // Warm cache
  int sumX = 0;
  for(int i=0; i<2*stride1; i++){
    sumX += data[i];
  }


  int sum1 = 0;
  gettimeofday(&tv1, NULL);
  begin = clock();                 // get current moment
  for(int i=0; i<length; i += stride1){
    sum1 += data[i];
  }
  end = clock();                   // get later moment to compare to start
  gettimeofday(&tv2, NULL);

  double stride1_cpu_time = ((double) (end - begin)) / CLOCKS_PER_SEC;
  double stride1_wall_time = 
    ((double) (tv2.tv_usec - tv1.tv_usec) / 1000000) +
    ((double) (tv2.tv_sec - tv1.tv_sec));


  sumX = 0;
  for(int i=0; i<2*stride2; i++){
    sumX += data[i];
  }

  int sum2 = 0;
  gettimeofday(&tv1, NULL);
  begin = clock();                 // get current moment
  for(int i=0; i<length; i += stride2){
    sum2 += data[i];
  }
  end = clock();                   // get later moment to compare to start
  gettimeofday(&tv2, NULL);
  double stride2_cpu_time = ((double) (end - begin)) / CLOCKS_PER_SEC;
  double stride2_wall_time = 
    ((double) (tv2.tv_usec - tv1.tv_usec) / 1000000) +
    ((double) (tv2.tv_sec - tv1.tv_sec));

  free(data);

  printf("%12d adds with stride1=%4d, CPU time: %.3f sec, Wall time: %.3f \n",
         length/stride1,stride1,stride1_cpu_time,stride1_wall_time);
  printf("%12d adds with stride2=%4d, CPU time: %.3f sec, Wall time: %.3f \n",
         length/stride2,stride2,stride2_cpu_time,stride2_wall_time);

  return sum1+sum2;
}

