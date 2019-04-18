// Demonstrate how memory references can affect performance unless
// they are optimized away by the compiler

#include <assert.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>               // for clock() and other functions
#include <stdio.h>
#include <sys/time.h>


// Sum by adding on to the memory location given leading to repeated
// writes to memory system
void sum_range1(int start, int stop, int *ans){
  *ans = 0;
  for(int i=start; i<stop; i++){
    *ans += i;
  }
}

// Sum using only a local with one memory write
void sum_range2(int start, int stop, int *ans){
  int sum = 0;
  for(int i=start; i<stop; i++){
    sum += i;
  }
  *ans = sum;
}

int main(int argc, char *argv[]){
  if(argc < 3){
    printf("usage: %s <start> <stop> \n",argv[0]);
    return -1;
  }

  int start = atoi(argv[1]);
  int stop  = atoi(argv[2]);


  clock_t begin, end;
  double cpu_time;

  int sum1;
  begin = clock();
  sum_range1(start, stop, &sum1);
  end = clock();
  cpu_time = ((double) (end - begin)) / CLOCKS_PER_SEC;
  printf("sum_range1: %.4e secs\n",cpu_time);    

  int sum2;
  begin = clock();
  sum_range2(start, stop, &sum2);
  end = clock();
  cpu_time = ((double) (end - begin)) / CLOCKS_PER_SEC;
  printf("sum_range2: %.4e secs\n",cpu_time);  

  assert(sum1 == sum2);
  return 0;
}
