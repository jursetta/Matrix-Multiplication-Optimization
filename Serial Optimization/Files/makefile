# Compiler
CC = gcc
# Flags
LFLAGS = -Wall

# Libraries
LibsM = -lmath

# define the C source files
Heads = main.c createMat.h matCalc.h
OBJS = main.c createMat.c matCalc.c
SRC = main.o createMat.o matCalc.o


mat_mult: $(SRC)
	$(CC) -O3 -o $@ $^ -lm -pg

main.o: $(Heads)
	$(CC) -c $< -pg

createMat.o: createMat.c createMat.h
	$(CC) -c $< -pg

matCalc.o: matCalc.c matCalc.h createMat.h
	$(CC) -c $< $(LibsM) -pg


.phony: clean
clean:
	rm -f *.o
