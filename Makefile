CC= gcc

CFLAGS= -c -ansi -pedantic -Wall
GLFLAGS= -lGL -lGLU -lglut -lm
 
all: run

run: main.o p.o 
	$(CC) -o run main.o p.o $(GLFLAGS)
main.o: main.c
	$(CC) $(CFLAGS) main.c

p.o: p.c
	$(CC) $(CFLAGS) p.c

clean: 
	rm -rf *o run



