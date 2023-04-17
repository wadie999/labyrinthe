CC = gcc
OPT = -lSDL2 -lSDL2_gfx -lSDL2_image -lSDL2_ttf -lSDL2_mixer -lSDL2_net
OBJ = jeuvie.o matrice.o 
jeuvie : $(OBJ)
	$(CC) $(OBJ) $(OPT) -o jeuvie
jeuvie.o : jeuvie.c matrice.c matrice.h jeuvie.h
	$(CC) $(OPT) -c jeuvie.c
matrice.o : matrice.c matrice.h
	$(CC) $(OPT) -c matrice.c

clean :
	rm $(OBJ)