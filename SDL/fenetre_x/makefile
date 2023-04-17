CC = gcc
OPT = -lSDL2 -lm
OBJ = fenetre_x.o 
fenetre : $(OBJ)
	$(CC) $(OBJ) $(OPT) -o fenetre_x
fenetre_x.o : fenetre_x.c fenetre_x.h
	$(CC) $(OPT) -c fenetre_x.c

clean :
	rm $(OBJ)