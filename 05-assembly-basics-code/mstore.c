// Bryant/O'Hallaron section 3.2.2 example
// Compile to assembly with
// > gcc -Og -S mstore.c
long mult2(long a, long b);
void multstore(long x, long y, long *dest){
  long t = mult2(x, y);
  *dest = t;
}

