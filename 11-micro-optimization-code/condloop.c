// condloop.c: Measure time differences in a loop involving a
// condition and equivalent code that doesn't have the condition.
#include <assert.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>               // for clock() and other functions
#include <stdio.h>
#include <sys/time.h>

// Conditional version
long sum_evensA(long start, long stop){
  long sum=0;
  for(int i=start; i<stop; i++){
    if((i & 0x01) == 0){
      sum += i;
    }
  }
  return sum;
}

// Straigh-line version, uses bit tricks to avoid conditional
long sum_evensB(long start, long stop){
  long sum=0;
  for(int i=start; i<stop; i++){
    int odd = i & 0x01;
    // 1 for odd, 0 for even
    int even_mask = odd - 1;
    // 0x00000000 for odd
    // 0xFFFFFFFF for even
    sum += even_mask & i;
  }
  return sum;
}

int main(int argc, char *argv[]){
  if(argc < 3){
    printf("usage: %s <start> <stop> \n",argv[0]);
    return -1;
  }

  long start = atol(argv[1]);
  long stop  = atol(argv[2]);

  clock_t begin, end;
  double cpu_time;

  begin = clock();
  long sumA = sum_evensA(start,stop);
  end = clock();
  cpu_time = ((double) (end - begin)) / CLOCKS_PER_SEC;
  printf("sum_evensA: %.4e secs\n",cpu_time);    

  begin = clock();
  long sumB = sum_evensB(start,stop);
  end = clock();
  cpu_time = ((double) (end - begin)) / CLOCKS_PER_SEC;
  printf("sum_evensB: %.4e secs\n",cpu_time);    
  // printf("sum_evensA: %ld\n",sumA);
  // printf("sum_evensB: %ld\n",sumB);
  assert(sumA==sumB);
  return 0;
}
