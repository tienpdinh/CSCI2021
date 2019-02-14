#include <stdio.h>

int main(){
  // Logical vs Bitwise AND,OR,XOR,NOT
  {
    int xl = 12 || 10; // truthy (Logical OR)
    int xb = 12 |  10; // 14     (Bitwise OR)
    printf("xl: %d  xb: %d\n",xl,xb);

    int yl = 12 && 10; // truthy (Logical AND)
    int yb = 12 &  10; // 8      (Bitwise AND)
    printf("yl: %d  yb: %d\n",yl,yb);

    int zb = 12 ^  10; // 8      (Bitwise XOR)
    printf("zb: %d\n",zb);

    int wl = !12;      // falsey (Logical NOT)
    int wb = ~12;      // 6      (Bitwise NOT/INVERT)
    printf("wl: %d  wb: %d\n",wl,wb);
  }

  // Left/Right Shift operations
  {
    //         76543210
    char x = 0b00010111; // 23
    char y = x << 2;     // left shift by 2
    //   y = 0b01011100; // 92
    //   x = 0b00010111; // not changed
    printf("x: %d\ny = x << 2;\ny: %d\n",x,y);

    char z = x >> 3;     // right shift by 2
    //   z = 0b00000010; // 2
    //   x = 0b00010111; // not changed
    printf("x: %d\nz = x >> 3;\nz: %d\n",x,z);

    char n = 0b10000000; // -128, signed
    char s = n >> 4;     // right shift by 4
    //   s = 0b11111000; // -8, sign extension
    //   right shift >> is "arithmetic"
    printf("n: %d\ns = n >> 4;\ns: %d\n",n,s);
  }

  // Multiplication/Division tricks with shift and add/subtract
  {
    //          76543210
    char  x = 0b00001010;  // 10
    char x2 = x << 1;      // 10*2
    //   x2 = 0b00010100;  // 20
    printf("x: %d\nx2 = x << 1;\nx2: %d\n",x,x2);

    char x4 = x << 2;      // 10*4
    //   x4 = 0b00101000;  // 40
    printf("x: %d\nx4 = x << 2;\nx4: %d\n",x,x4);

    char x7 = (x << 3)-x;  // 10*7
    //   x7 = (x * 8)-x;   // 10*7
    //   x7 = 0b01000110;  // 70
    //          76543210
    printf("x: %d\nx7 = (x << 3)-x;\nx7: %d\n",x,x7);

    //          76543210
    char y  = 0b01101110;  // 110
    char y2 = y >> 1;      // 110/2
    //   y2 = 0b00110111;  // 55
    printf("y: %d\ny2 = y >> 1;\ny2: %d\n",y,y2);

    char y4 = y >> 2;      // 110/4
    //   y4 = 0b00011011;  // 27
    printf("y: %d\ny4 = y >> 2;\ny4: %d\n",y,y4);

    char z  = 0b10101100;  // -84
    char z2 = z >> 2;      // -84/4
    //   z2 = 0b11101011;  // -21
    //   right shift sign extension
    printf("z: %d\nz2 = z >> 2;\nz2: %d\n",z,z2);
  }

  return 0;
}

