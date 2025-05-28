CFLAGS = -Wall -std=c11

all: main 

clean: 
	rm -f main *.o
	
main: main.o fileIO.o deps.o
	gcc $(CFLAGS) -lm fileIO.o deps.o -o main 

main.o: main.c fileIO.h deps.h
	gcc $(CFLAGS) -c main.c -o main.o

fileIO.o: fileIO.c fileIO.h 
	gcc $(CFLAGS) -c fileIO.c -o fileIO.o

deps.o: deps.c deps.h fileIO.h
	gcc $(CFLAGS) -c deps.c -o deps.o