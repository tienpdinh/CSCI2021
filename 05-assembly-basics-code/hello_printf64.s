### Hello World in x86-64 assembly. 
### Calls printf() to print a message to the string
###
### Based on the following SO article discussing 64-bit Linux ABI
### https://stackoverflow.com/questions/38335212/calling-printf-in-x86-64-using-gnu-assembler/38335743
### 
### WITH GCC:  Statically linked executable
### > gcc -static hello_printf64.s
### > a.out
### 
### WITH GCC: Dynamically linked executable
### > gcc -no-pie hello_printf64.s
### > a.out
### 
### MANUALLY WITH LOW-LEVEL tools
### ASSEMBLE: Use GNU Assembler (as) to generate binary
### > as -o hello_printf64.o hello_printf64.s
### LINK: Complex as the standard C library must be linked manually which involves several files
### > ld -o hello -dynamic-linker /lib/ld-linux-x86-64.so.2 /usr/lib/crt1.o /usr/lib/crti.o /usr/lib/libc.so hello_printf64.o /usr/lib/crtn.o
### RUN:
### > ./hello
.extern printf                  # declare that printf is out there, like #include <stdio.h>
.global main                    # global symbol main

.section .text                  # code (text) section
main:                           # main() in a C program
        movq $msg, %rdi         # first arg to printf()
        movq $0,   %rax         # 0 extra arguments for vararg printf
	push %rbx               # align the stack prior to a function call:
	                        # stack already has 8 byte return address on it
                                # push any 8-byte register to get 16-byte alignment
        call printf
	pop %rbx                # restore the stack
        movq $0, %rax           # return value of 0
        ret                     # return from main()
        
        
.section .data	                # data section
msg:                            # labels location of a messge
        .asciz "Hello world!\n" # null terminated message, essential for printf()
