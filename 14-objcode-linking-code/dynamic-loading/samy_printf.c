// SOURCE: http://fluxius.handgrep.se/2011/10/31/the-magic-of-ld_preload-for-userland-rootkits/

#define _GNU_SOURCE

#include <stdio.h>
#include <dlfcn.h>
#include <stdlib.h>
#include <stdarg.h>
#include <unistd.h>

void print_extra(){
  typeof(puts) *old_puts;
  old_puts = dlsym(RTLD_NEXT, "puts");
  old_puts("... but most of all, Samy is my hero.");
}
  
int puts(const char *s){
  typeof(puts) *old_puts;
  old_puts = dlsym(RTLD_NEXT, "puts");
  old_puts(s);
  print_extra();
  return 0;
}


int printf(const char *fmt, ...) {
  typeof(vfprintf) *old_vfp;
  old_vfp = dlsym(RTLD_NEXT, "vfprintf");
  va_list myargs;                        // declare a va_list type variable 
  va_start(myargs, fmt);                 // initialise the va_list variable with the ... after fmt 
  int ret = old_vfp(stdout,fmt,myargs);  // forward the '...' to vfprintf()
  print_extra();                         // print the extra message
  va_end(myargs);                        // clean up the va_list
  return ret;
}
