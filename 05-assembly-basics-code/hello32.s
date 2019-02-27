### hello world in 32-bit assembly. Assemble, link, run with the following:
### 
### $> as -o hello.o hello32.s
### $> ld hello.o
### $> ./a.out
### 
### See notes in hello64.s on why gcc won't work.
### 
### Demonstrate 32-bit calling conventions with 'int $0x80' which
### "traps" to the kernel after setting up arguments in registers.
### System call numbers are 4 for write and 1 for exit and make use
### of the 32 bit registers like %eax.
### 
### This versions is used with the GNU Assembler 'as' which is
### present wherever GCC is present.

.text                           # text section which contains code
.global _start                  # code position to begin execution, _start by convention

_start:                         # label to indicate a position in code, happens to be
                                # main entry point for the program
	
        ## set up system call to write data to a file handle, takes 3 arguments which are
	movl    $4,  %eax       # system call number for write: 4, 
	movl    $1,  %ebx       # first  arg: file handle, stdout = 1
	movl    $msg,%ecx       # second arg: address of message to write
	movl    $13, %edx       # third  arg: message length, 13 in this case
	int     $0x80           # interrupt to call kernel

	## After writing, call exit(0) to indicate success
	movl    $1,%eax         # system call number for exit: 1
	movl    $0,%ebx         # first argument: exit code 0 to indicate success
	int     $0x80           # call kernel
	
.data                           # data section which contains... data

msg:
        .ascii "Hello world!\n" # no need to null terminate: write() syscall 
                                # takes arg of 13 bytes to write and stops there

