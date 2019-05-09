demo: samy_printf.c hello.c
	## compile shared library
	gcc -shared -fPIC -Wl,-soname -Wl,libsamy_printf.so -o libsamy_printf.so samy_printf.c -ldl
	## Compile executable
	gcc -o hello hello.c
	## Run hello program normally
	./hello
	## Run with alternative samy_printf()
	export LD_PRELOAD=$$PWD/libsamy_printf.so; \
	./hello

