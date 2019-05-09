all : hello_static hello_dynamic

hello_static : hello.c
	gcc -o hello_static -static hello.c

hello_dynamic : hello.c
	gcc -o hello_dynamic hello.c

hello_pause : hellopause.c
	gcc -o hello_pause hellopause.c

clean : 
	rm -f *.o hello_*

