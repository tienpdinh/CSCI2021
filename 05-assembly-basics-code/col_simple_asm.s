### Compute Collatz sequence starting at 10 in assembly.  This version
### is a very direct translation so can be optized heavily by
### replacing division with equivalent shift/compare operations
### 
### COMPILE:
### > gcc -g collatz.s   # compile with gcc, debug symbols on
### > ./a.out            # run program, no output
### > echo $?            # echo return value of prog: # of steps
### > gdb -tui ./a.out   # run debugger with assembly 
### gdb> break main      # set a breakpoint
### gdb> layout reg      # show registers
### gdb> run             # run in debugger

.section        .text
.globl  main
main:
        movl    $0,  %ebx       # int steps = 0;   
        movl    $10, %ecx       # int n = 10;
.LOOP:
        cmpl    $1,  %ecx       # while(n > 1){ // immediate must be first
        jle     .END            #   n <= 1 exit loop
        movl    %ecx,%eax       #   prep for division: must use edx:eax
        cqto                    #   extend sign from eax to edx
        movl    $2,  %esi       #   divisor in esi
        idivl   %esi            #   divide edx:eax by esi
                                #   eax has quotient, edx remainder
        cmpl    $1,%edx         #   if(n % 2 == 1) {
        jne     .EVEN           #     not equal, go to even case
.ODD:
        imull   $3, %ecx, %ecx  #     n = n * 3
        incl    %ecx            #     n = n + 1
        jmp     .UPDATE         #   }
.EVEN:                          #   else{
        sarl    %ecx            #     n = n / 2; via right shift
.UPDATE:                        #   }
        incl    %ebx            #   steps++;
        jmp     .LOOP           # }
.END:
        movl    %ebx, %eax      # ebx is steps, move to eax for return value
        ret
