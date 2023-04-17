#ifndef MATRICE
#define MATRICE
#include <math.h>
#include <stdio.h>
#include <SDL2/SDL.h>
#include <string.h>
#include <stdbool.h>


int** cree(int ligne,int colonne);
void fill_matrix(int** matrice,int ligne,int clonne);
void afficher(int** matrice,int ligne, int colonne);
void copie(int**origine,int**destination,int ligne, int colonne);
int voisin(int**matrice,int ligne,int colonne,int x,int y);
void insert(int**matrice,int x,int y);
int voisin(int**matrice,int ligne,int colonne,int x,int y);

#endif