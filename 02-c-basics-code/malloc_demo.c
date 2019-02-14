// Demonstrate ins/outs of malloc
#include <stdio.h>
#include <stdlib.h>             // malloc()/free()

int main(){
  printf("how many ints: ");
  int len;
  scanf(" %d",&len);

  int *nums = malloc(sizeof(int)*len); 
  // allocate bytes: sizeof() usually gives
  // 4 bytes per int. malloc() returns a void*
  // to bytes allocated or NULL if space could not
  // be found.

  printf("initializing to 0\n"); // malloc'ed bytes are
  for(int i=0; i<len; i++){      // may be anything 
    nums[i] = 0;                 // calloc() initializes its data
  }

  printf("enter %d ints: ",len);
  for(int i=0; i<len; i++){     // read data into the allocated
    scanf(" %d",&nums[i]);      // array
  }

  printf("nums are:\n");
  for(int i=0; i<len; i++){
    printf("[%d]: %d\n",i,nums[i]);
  }

  free(nums);                   // free() memory or risk a leak
  return 0;                     // on finishing, OS reclaims all memory
                                // used by a program but while the program
}                               // runs, it may leak memory

