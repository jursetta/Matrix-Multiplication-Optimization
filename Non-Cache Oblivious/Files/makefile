# Compiler
CC = gcc
# Flags
LFLAGS = -Wall

# Libraries
LibsM = -lmath

# define the C source files
Heads = main.c createMat.h
OBJS = main.c createMat.c
SRC = main.o createMat.o


naive_mm: $(SRC)
	$(CC) -o $@ $^ -lm -pg

main.o: $(Heads)
	$(CC) -c $< -pg

createMat.o: createMat.c createMat.h
	$(CC) -c $< -pg

.phony: clean
clean:
	rm -f *.o
