CC = gcc
OPT = -lSDL2 -lSDL2_image 
OBJ = animation.o
animation : $(OBJ)
	$(CC) $(OBJ) $(OPT) -o animation
animation.o: animation.c 
	$(CC) $(OPT) -c animation.c
clean :
	rm $(OBJ)