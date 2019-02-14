/* Function showbits prints the bits of integers to the screen as well
   as the hexadecimal representation. Run the program like
   
   a.out 5
   a.out 1024

*/

#include <stdlib.h>
#include <stdio.h>

#define INT_BITS 32

/* Count ones */
void count_ones(int x){
  int i; 
  int mask = 0x1;
  int ones_count = 0;
  for(i=0; i<INT_BITS; i++){
    int shifted_mask = mask << i;
    if(shifted_mask & x){
      ones_count++;
    } 
  }
  /* Equivalent short version */
  //    (x&(1<<i)) ? putchar('1'): putchar('0');
}


/* Print the most signficant (right-most) to least signficant bit in
   the integer passed in */
void showbits(int x){
  int mask = 0x1;
  for(int i=INT_BITS-1; i>=0; i--){
    int shifted_mask = mask << i;
    if(shifted_mask & x){
      printf("1");
    } else {
      printf("0");
    }
  }
  /* Equivalent short version */
  //    (x&(1<<i)) ? putchar('1'): putchar('0');
}

int main(int argc, char **argv){
  if(argc < 2){
    printf("Argument dummy\n");
    return 1;
  }
  printf("%-32s %-8s %s\n","Binary","Hex","Decimal");
  int i;
  for(i=1; i<argc; i++){
    int num = atoi(argv[i]);
    showbits(num);
    printf(" %8X %d\n",num,num);
  }
  printf("%-32s %-8s %s\n","Binary","Hex","Decimal");
  return 0;
}
