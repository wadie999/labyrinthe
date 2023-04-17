CC = gcc
OPT = -lSDL2 
OBJ = rendu.o
rendu : $(OBJ)
	$(CC) $(OBJ) $(OPT) -o rendu
rendu.o: rendu.c rendu.h
	$(CC) $(OPT) -c rendu.c

clean :
	rm $(OBJ)