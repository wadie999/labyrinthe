#ifndef MATRICE
#define MATRICE
#include <math.h>
#include <stdio.h>
#include <SDL2/SDL.h>
#include <string.h>
#include <stdbool.h>
#include "image.h"
#include "matrice.h"
#include "animationperso.h"

typedef struct arrete
{
    int i     ;
    int j     ;
    int poids ;
}arrete_t;

typedef struct graphe 
{
    int        nombrenoeud;
    int        nombrearrete;
    arrete_t * arrete     ;
}graphe_t;

typedef struct partition
{

    int   taille  ;
    int * hauteur ;
    int * pere    ;
}partition_t;
int** cree(int ligne,int colonne);
void fill_matrix(int** matrice,int ligne,int clonne);
void afficher(int** matrice,int ligne, int colonne);
void copie(int**origine,int**destination,int ligne, int colonne);
int voisin(int**matrice,int ligne,int colonne,int x,int y);
void insert(int**matrice,int x,int y);
int voisin(int**matrice,int ligne,int colonne,int x,int y);

#endif