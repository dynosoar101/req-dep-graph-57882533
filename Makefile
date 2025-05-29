CC = gcc
CFLAGS = -Wall -std=c11 -Iinclude

SRC = src
INCLUDE = include
OBJ = obj

OBJS = $(OBJ)/main.o $(OBJ)/fileIO.o $(OBJ)/deps.o

all: rdgg

rdgg: $(OBJS)
	$(CC) $(CFLAGS) -o rdgg $(OBJS)

$(OBJ)/main.o: $(SRC)/main.c $(INCLUDE)/fileIO.h $(INCLUDE)/deps.h
	$(CC) $(CFLAGS) -c $(SRC)/main.c -o $(OBJ)/main.o

$(OBJ)/fileIO.o: $(SRC)/fileIO.c $(INCLUDE)/fileIO.h
	$(CC) $(CFLAGS) -c $(SRC)/fileIO.c -o $(OBJ)/fileIO.o

$(OBJ)/deps.o: $(SRC)/deps.c $(INCLUDE)/deps.h
	$(CC) $(CFLAGS) -c $(SRC)/deps.c -o $(OBJ)/deps.o

clean:
	rm -f $(OBJ)/*.o rdgg