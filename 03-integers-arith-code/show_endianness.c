// Show endiannes layout of a binary number in memory Most machines
// are little endian so bytes will print leas signficant earlier.
#include <stdio.h>

int main(){
  int bin = 0b00000000000000000001100011101001;    // 6377
  //          |   |   |   |   |   |   |   |
  printf("%d\n%x\n",bin,bin);                  // show decimal and hex representation of bin
  unsigned char *ptr = (unsigned char *) &bin; // pointer to beginning of bin
  for(int i=0; i<4; i++){                      // print bytes of bin from low to high
    printf("%x ", ptr[i]);                     // memory address 
  }
  printf("\n");
  return 0;
}
