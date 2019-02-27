### hello world in 64-bit assembly. Assemble, link, run with the following:
### 
### $> as -o hello.o hello64.s
### $> ld hello.o
### $> ./a.out
### 
### NOTE: You cannot use gcc for this as we are providing our own _start 
### entry point which doesn't play well with gcc. Also there are no
### standard library calls used so it is pointless to link this with any
### additional libraries.
###
### Demonstrate 64-bit calling conventions with 'syscall', an instruction
### that was not present in original i386 32-bit architectures.  The
### system call numbers are different from the 32 bit version: 1 for write
### and 60 for exit, and the mov instructions must use 64-bit versions with 
### the "movq" quadword variant.
### 
### This versions is used with the GNU Assembler 'as' which is
### present wherever GCC is present.

.text                           # text section which contains code
.global _start                  # code position to begin execution, _start by convention

_start:                         # label to indicate a position in code, happens to be
                                # main entry point for the program
	
        ## set up system call to write data to a file handle, takes 3 arguments which are
	movq    $1,  %rax       # system call number for write: 1
	movq    $1,  %rdi       # first  arg: file handle, stdout = 1
	movq    $msg,%rsi       # second arg: address of message to write
	movq    $13, %rdx       # third  arg: message length, 13 in this case
        syscall                 # make a system call, x86-64 convention

	## After writing, call exit(0) to indicate success
	movq    $60,%rax        # system call number for exit: 60 (64-bit convention)
	movq    $0, %rdi        # first argument: exit code 0 to indicate success
        syscall                 # make a system call, x86-64 convention
	
.data                           # data section which contains... data

msg:
        .ascii "Hello world!\n" # no need to null terminate: write() syscall 
                                # takes arg of 13 bytes to write and stops there
