# -pg for profiling
# -no-pie for a gcc bug fix: https://bugs.debian.org/cgi-bin/bugreport.cgi?bug=854704
CC = gcc -pg -g -Og -no-pie	

DATAFILE = craft-67.txt
# DATAFILE = The-Time-Machine.txt

# dictionry application to demonstrate profiling
dictionary: dictionary.c 
	$(CC) -o $@ dictionary.c 

demo: dictionary
	# first run using inefficient sorting
	rm -f gmon.out
	./dictionary < $(DATAFILE)
	gprof -b dictionary

	# second run using quicksort
	rm -f gmon.out
	./dictionary -quicksort 1 < $(DATAFILE)
	gprof -b dictionary

clean:
	rm -f dictionary gmon.out
