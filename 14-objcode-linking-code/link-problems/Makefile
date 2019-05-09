PROGRAMS = \
	x_bad1 \
	x_bad2 \
	x_main \
	x_main_bad \
	func_int \


all : $(PROGRAMS)

# Example of global variable problems


x_bad1 : x_int.o x_long.o
	gcc -o x_bad1 x_int.o x_long.o  # int def first

x_bad2 : x_int.o x_long.o
	gcc -o x_bad2 x_long.o x_int.o  # long def first

x_int.o : x_int.c
	gcc -c $<

x_long.o : x_long.c
	gcc -c $<

# Avoid problems with header
x_main : x_main.o x_to_neg8.o
	gcc -o $@ $^

x_main.o : x_main.c x_to_neg8.h
	gcc -c $<

x_to_neg8.o : x_to_neg8.c x_to_neg8.h
	gcc -c $<

x_main_bad : x_main_bad.o x_to_neg8.o
	gcc -o $@ $^

x_main_bad.o : x_main_bad.c x_to_neg8.h
	gcc -c $<


# Example of function prototype problems
func_int : func_int.o func_long.o
	gcc -o $@ $^

func_int.o : func_int.c
	gcc -c $<

func_long.o : func_long.c
	gcc -c $<


clean : 
	rm -f *.o $(PROGRAMS)

