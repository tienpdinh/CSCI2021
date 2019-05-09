all : main_func

main_func.o : main_func.c
	gcc -c $<

clean : 
	rm -f *.o main_func

func_01.o : func_01.c
	gcc -c $<

func_02.o : func_02.c
	gcc -c $<

main_func : main_func.o func_01.o
	gcc -o $@ $^

funcs_12.o : func_01.o func_02.o
	ld -r func_01.o func_02.o -o funcs_12.o

