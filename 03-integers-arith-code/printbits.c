// Prints the bit representation of a decimal number specified on the
// command line. Makes use of right shift >> operator and bitwise and
// & operator to accomplish this.
//
// usage: a.out <number>
//
// Examples:
// > gcc printbits.c
// > a.out 5
//  3         2         1         0 tens index
// 10987654321098765432109876543210 ones index
// 00000000000000000000000000000101 bits for 5
// > a.out 1024
//  3         2         1         0 tens index
// 10987654321098765432109876543210 ones index
// 00000000000000000000010000000000 bits for 1024
// > a.out 1808
//  3         2         1         0 tens index
// 10987654321098765432109876543210 ones index
// 00000000000000000000011100010000 bits for 1808
// > a.out -1
//  3         2         1         0 tens index
// 10987654321098765432109876543210 ones index
// 11111111111111111111111111111111 bits for -1
// > a.out -1808
//  3         2         1         0 tens index
// 10987654321098765432109876543210 ones index
// 11111111111111111111100011110000 bits for -1808

#include <stdio.h>
#include <stdlib.h>

void print_header(int num_bits);       // function declaration; definition below main()

int main(int argc, char *argv[]){      // main entry point takes # and string command args
  if(argc < 2){
    printf("usage: %s <number>\n",     // print a usage message
           argv[0]);                   // program name is always argv[0]
    return 1;
  }
  print_header(32);

  int decimal = atoi(argv[1]);

  char bitstring[33];
  bitstring[32] = '\0';                // terminate string with the 0 character: null

  for(int i=0; i<32; i++){
    int shifted = decimal >> i;        // shift number bits right by given amount
    int is_set = shifted & 1;          // check if shifted bit is set
    int index = 32 - i - 1;            // right to left placement of digits
    if(is_set){
      bitstring[index] = '1';          // is_set truthy so put a 1 in the output string 
    }
    else{
      bitstring[index] = '0';          // no set, put a 0 in output string
    }
  }
  printf("%s bits for %d\n",           // print bits and decimal
         bitstring, decimal);

  return 0;
}

// Function: prints "headers" to the screen to make it easier to
// identify positions in a bit string. Parameter num_bits is the
// number of bits in the string, commonly 32 for integers.
void print_header(int num_bits){
                                       // print tens index of bit, high index on left, low on right
  for(int i=num_bits-1; i>=0; i--){
    if(i % 10 == 0){
      int index = i / 10;              // div 10 to get tens digit
      printf("%d", index);             // print digit
    }
    else{                              // not divisible by ten so
      printf(" ");                     // print a filler space
    }
  }
  printf(" tens index\n");
                                       // print ones index of bit, high index on left, low on right
  for(int i=num_bits-1; i>=0; i--){
    int index = i % 10;                // modulo 10 to get ones digit
    printf("%d", index);               // print ones digit
  }
  printf(" ones index\n");

  return;
}
