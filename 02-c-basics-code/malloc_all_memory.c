// Explore how much memory your system has
#include <stdio.h>
#include <stdlib.h>

int main(){
  long n=1;                     // int too small to hold max bytes
  while(1){			// Loop until fail/break
    printf("%12ld bytes: ",n);	// %lf used for printing longs 
    void *mem = malloc(n);      // Try to allocate memory 
    if(mem==NULL){              // Failed 
      printf("Failure\n");
      n /= 2;			// Back n up one step 
      break;                    // pop out of loop
    }
    printf("Success\n");
    free(mem);			// Free the memory so we can ask for more 
    n *= 2;			// Next time, ask for 2 times as much 
  }
  long kb = n / 1024;		// Conversions 
  long mb = kb / 1024;
  long gb = mb / 1024;
  
  printf("\n");
  printf("%12ld byte limit\n",n);
  printf("%12ld KB limit\n",  kb);
  printf("%12ld MB limit\n",  mb);
  printf("%12ld GB limit\n",  gb);

  return 0;
}
