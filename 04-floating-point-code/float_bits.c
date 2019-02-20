// Show binary layout of a float value in IEEE-754 format
#include <stdio.h>
#include <math.h>   // macros for infinity

void showbits(void *xp);

int main(){
  float fl;                     // floating point value
  int *fp = (int *) &fl;        // pointer to float memory
  // *fp = 0xC378C000;             // assign specific bits to float
  // *fp = 0b11000011011110001100000000000000;
  //         |   |   |   |   |   |   |   |   
  printf("%.4f\n",fl);
  showbits(&fl);


  fl = 0xC378C000;              // compiler converts constatnt int to
  printf("%.4f\n",fl);          // float which produces a large value
  showbits(&fl);

  // Creat value 1.0 with bits
  //0b0 01111111 000 0000 0000 0000 0000 0000;
  //  s:exponent:mantissa (implied leading 1)

  *fp = 0b00111111100000000000000000000000;
  printf("%.4f\n",fl);
  showbits(&fl);


  // Special values: exponent bits are all 1s 

  // Playing with infinity
  float pinf =  INFINITY;
  float ninf = -INFINITY;
  float odz  = 1.0 / 0.0;
  printf("%f %f %f\n",pinf,ninf,odz);
  showbits(&pinf);
  showbits(&ninf);
  showbits(&odz);
  
  // NaN: not a number
  float nan = NAN;
  float odo = 0.0 / 0.0;
  float imi = INFINITY - INFINITY;
  printf("%f %f %f\n",nan,odo,imi);
  showbits(&nan);
  showbits(&odo);
  showbits(&imi);
  
  // Denormalized: very small numbers, exponent bits are all 0s
  float sm = 3.0;
  for(int i=0; i<127; i++){     
    sm /= 2.0;                  // divide by 2 126 times
  }
  printf("%e\n",sm);            // 3 * 2^-126 =~= 1.763242e-38
  showbits(&sm);                // shows all 0s exponent, 3 in mantissa

  return 0;
}

#define INT_BITS 32

/* Print the most signficant (right-most) to least signficant bit in
   the integer passed in */
void showbits(void *xp){
  int x = *((int *) xp);
  int mask = 0x1;
  for(int i=INT_BITS-1; i>=0; i--){
    int shifted_mask = mask << i;
    if(shifted_mask & x){
      printf("1");
    } else {
      printf("0");
    }
  }
  printf("\n");
}
