// Simple program to sum a data array with variable stride

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>                  // for clock() and other functions
#include <stdio.h>
#include <sys/time.h>

int *data;                         // global pointer for data

// Simple version
int test(int len, int stride) {
  int sum = 0;
  for(int i = 0; i < len; i += stride) {
    sum += data[i];     
  }
  return sum;
}

// From Bryant/O'Hallaron
int test_bh(int elems, int stride)
{
    int i, sx2 = stride*2, sx3 = stride*3, sx4 = stride*4;
    int acc0 = 0, acc1 = 0, acc2 = 0, acc3 = 0;
    int length = elems;
    int limit = length - sx4;

    /* Combine 4 elements at a time */
    for (i = 0; i < limit; i += sx4) {
	acc0 = acc0 + data[i];     
        acc1 = acc1 + data[i+stride];
	acc2 = acc2 + data[i+sx2]; 
        acc3 = acc3 + data[i+sx3];
    }

    /* Finish any remaining elements */
    for (; i < length; i += stride) {
	acc0 = acc0 + data[i];
    }
    return ((acc0 + acc1) + (acc2 + acc3));
}

int main(int argc, char *argv[]){

  if(argc < 3){
    printf("usage: %s <length> <stridemax>\n",argv[0]);
    return 1;
  }

  int length = atoi(argv[1]);
  int stridemax = atoi(argv[2]);

  data = malloc(length*sizeof(int)); // initialize
  for(int i=0; i<length; i++){
    data[i] = i;
  }


  int TRIALS = 100;
  clock_t begin, end;
  struct timeval tv1, tv2;
  double cpu_time, wall_time, throughput;

  int grand_total = 0;

  for(int stride=1; stride <= stridemax; stride++){
    // warm the cache


    // TEST the simple loop version
    test(length,stride);             // warm cache
    gettimeofday(&tv1, NULL);        // get time of day
    begin = clock();                 // get current moment
    for(int t=0; t<TRIALS; t++){
      grand_total += test(length,stride);           // run test
    }
    end = clock();                   // get later moment to compare to start
    gettimeofday(&tv2, NULL);

    cpu_time = ((double) (end - begin)) / CLOCKS_PER_SEC;
    wall_time = 
      ((double) (tv2.tv_usec - tv1.tv_usec) / 1000000) +
      ((double) (tv2.tv_sec - tv1.tv_sec));
    cpu_time  /= TRIALS;
    wall_time /= TRIALS;
    throughput = ((double) length) / stride / cpu_time;

    printf("SIMPLE: stride: %3d   CPU time: %.2e sec   Throughput: %12.0f adds/sec SIMPLE\n",
           stride,cpu_time,throughput);

    // // test the Bryant/O'Hallaron add4 version
    // test_bh(length,stride);          // warm cache
    // gettimeofday(&tv1, NULL);        // get time of day
    // begin = clock();                 // get current moment
    // for(int t=0; t<TRIALS; t++){
    //   grand_total += test_bh(length,stride);           // run test
    // }
    // end = clock();                   // get later moment to compare to start
    // gettimeofday(&tv2, NULL);

    // cpu_time = ((double) (end - begin)) / CLOCKS_PER_SEC;
    // wall_time = 
    //   ((double) (tv2.tv_usec - tv1.tv_usec) / 1000000) +
    //   ((double) (tv2.tv_sec - tv1.tv_sec));
    // cpu_time  /= TRIALS;
    // wall_time /= TRIALS;
    // throughput = ((double) length) / stride / cpu_time;

    // printf("ADD4:   stride: %3d   CPU time: %.2e sec   Throughput: %12.0f adds/sec ADD4\n",
    //        stride,cpu_time,throughput);



  }    


  return grand_total;
}
