// free_twice.c: demonstrates how heap-malloc()'d data is invalidated
// when free() is called on it. 

#include <stdlib.h>
#include <stdio.h>

// allocate an array of given length, fill it 1's and return a pointer
// to it; contains a bug
int *ones_array(int len){
  int *arr = malloc(sizeof(int)*len);
  for(int i=0; i<len; i++){
    arr[i] = 1;
  }
  free(arr);                    // should not free an array being returned
  return arr;
}

int main(){
  int *ones = ones_array(5);
  for(int i=0; i<5; i++){       
    printf("ones[%d] is %d\n",i,ones[i]);
  }

  free(ones);                   // 2nd free
  return 0;
}

// Behavior on most linux systems:
// 
// > gcc free_twice.c
// > ./a.out
// ones[0] is 0          # zero'd due to first call to free
// ones[1] is 0          # remove first free() to fix
// ones[2] is 1
// ones[3] is 1
// ones[4] is 1
//
// Compile and debug via valgrind:
//
// > gcc -g free_twice.c          # -g includes debug information
// 
// > valgrind ./a.out             # run under valgrind memory checker
// 
// ==8248== Memcheck, a memory error detector
// ==8248== Copyright (C) 2002-2017, and GNU GPL'd, by Julian Seward et al.
// ==8248== Using Valgrind-3.14.0 and LibVEX; rerun with -h for copyright info
// ==8248== Command: ./a.out
// ==8248== 
// ==8248== Invalid read of size 4                              # MEMORY ERROR
// ==8248==    at 0x1091ED: main (free_twice.c:22)
// ==8248==  Address 0x4a3a040 is 0 bytes inside a block of size 20 free'd
// ==8248==    at 0x48389AB: free (vg_replace_malloc.c:530)
// ==8248==    by 0x1091B3: ones_array (free_twice.c:14)
// ==8248==    by 0x1091CB: main (free_twice.c:20)
// ==8248==  Block was alloc'd at
// ==8248==    at 0x483777F: malloc (vg_replace_malloc.c:299)
// ==8248==    by 0x109174: ones_array (free_twice.c:10)
// ==8248==    by 0x1091CB: main (free_twice.c:20)
// ==8248== 
// ones[0] is 1
// ones[1] is 1
// ones[2] is 1
// ones[3] is 1
// ones[4] is 1
// ==8248== Invalid free() / delete / delete[] / realloc()       # MEMORY ERROR
// ==8248==    at 0x48389AB: free (vg_replace_malloc.c:530)
// ==8248==    by 0x10921A: main (free_twice.c:25)
// ==8248==  Address 0x4a3a040 is 0 bytes inside a block of size 20 free'd
// ==8248==    at 0x48389AB: free (vg_replace_malloc.c:530)
// ==8248==    by 0x1091B3: ones_array (free_twice.c:14)
// ==8248==    by 0x1091CB: main (free_twice.c:20)
// ==8248==  Block was alloc'd at
// ==8248==    at 0x483777F: malloc (vg_replace_malloc.c:299)
// ==8248==    by 0x109174: ones_array (free_twice.c:10)
// ==8248==    by 0x1091CB: main (free_twice.c:20)
// ==8248== 
// ==8248== 
// ==8248== HEAP SUMMARY:
// ==8248==     in use at exit: 0 bytes in 0 blocks
// ==8248==   total heap usage: 2 allocs, 3 frees, 1,044 bytes allocated
// ==8248== 
// ==8248== All heap blocks were freed -- no leaks are possible
// ==8248== 
// ==8248== For counts of detected and suppressed errors, rerun with: -v
// ==8248== ERROR SUMMARY: 6 errors from 2 contexts (suppressed: 0 from 0)
// > 
