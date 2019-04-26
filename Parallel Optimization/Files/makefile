# Compiler
CC = mpicc
# Flags
LFLAGS = -Wall

# Libraries
LibsM = -lmath

# define the C source files
Heads = main.c createMat.h matCalc.h initMatLoc.h
OBJS = main.c createMat.c matCalc.c initMatLoc.c
SRC = main.o createMat.o matCalc.o initMatLoc.o


mat_mult: $(SRC)
	$(CC) -O3 -o $@ $^ -lm -pg

main.o: $(Heads)
	$(CC) -c $< -pg

createMat.o: createMat.c createMat.h
	$(CC) -c $< -pg

matCalc.o: matCalc.c matCalc.h createMat.h
	$(CC) -c $< -lm -pg
    
initMatLoc.o: initMatLoc.c initMatLoc.h
	$(CC) -c $< -lm -pg


.phony: clean
clean:
	rm -f *.o
