// Optional: Bitfields and use to examine specific parts of float
// structure

#include <stdio.h>

// Structs allow bitfield specifications: how many bits for each
// field. These are packed into as small a sane quantity as possible
// and with the right tricks can get them to lign up with the parts of
// a float.
typedef struct{
  unsigned int mant:23;         // lowest order bits
  unsigned int expo:8;          // middle bits
  unsigned int sign:1;          // highest order bits
} flfields_t;                   // total 32 bits, should have size 4 bytes

int main(){
  printf("sizeof(flfields_t): %d\n", sizeof(flfields_t));

  flfields_t fields;
  float *x = (float *) &fields; // caste to convince compiler


  fields.sign = 0x01;           // negative
  fields.expo = 0x7F;           // 127 - 127 = 0
  fields.mant = 0x000000;       // 0000 mantissa, leading 1 implied

  printf("x: %+f\n",*x);         // -1.0

  fields.mant = 0x400000;       // 1000.. mantissa, leading 1 implied, 1+1/2
  printf("x: %+f\n",*x);         // -1.5


  fields.sign = 0x00;           // positive
  fields.expo = 0x80;           // 128 - 127 = 1: mant * 2^1
  printf("x: %+f\n",*x);        // Double last result: 3.0


  // combine bifield with union: overlay a flfields_t with a float so
  // they reside in the same memory.
  union {
    flfields_t fields;
    float fl;
  } y;
  
  y.fields.sign = 0x01;         // negative
  y.fields.expo = 0x81;         // 129 - 127 = 2; man * 2^2
  y.fields.mant = 0x200000;     // 1.0100 = 1.25 * 2^2 = 5.0

  printf("y.fl: %+f\n",y.fl);   // print float interpretation of y's bits

  return 0;
}
