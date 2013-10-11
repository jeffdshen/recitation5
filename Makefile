CC=gcc

#results dumped by cilkview objects
VIEWS = main

CFLAGS= -std=gnu99 -Wall -O3 -fcilkplus
LDFLAGS= -ldl -lcilkrts
INCLUDES = -I/afs/csail.mit.edu/proj/courses/6.172/cilkutil/include

all: main

main : main.c Makefile
	$(CC) $(CFLAGS) $@.c $(LDFLAGS) -o $@

clean :
	rm -f main *~

