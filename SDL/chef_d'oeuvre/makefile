CC = gcc
OPT = -lSDL2 -lSDL2_image -lm
OBJ = mainanimperso.o matrice.o image.o animationperso.o
jeu : $(OBJ)
	$(CC) $(OBJ) $(OPT) -o jeu
mainanimperso.o : mainanimperso.c matrice.c matrice.h image.c image.h animationperso.c animationperso.h
	$(CC) $(OPT) -c mainanimperso.c
matrice.o : matrice.c matrice.h
	$(CC) $(OPT) -c matrice.c
image.o : image.c image.h
	$(CC) $(OPT) -c image.c
animationperso.o : animationperso.c animationperso.h
	$(CC) $(OPT) -c animationperso.c
clean :
	rm $(OBJ)