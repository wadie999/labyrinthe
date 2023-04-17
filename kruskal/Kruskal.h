#include <stdlib.h>
#include <stdio.h>

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
partition_t initialisation(int taille);
void Affichage_partition(partition_t partition);
int trouveracine(partition_t partition,int x);
void fusion(partition_t* partition,int x, int y);
int * lister_composantes(partition_t partition, int pere);
int existe(int * liste,int taille,int element);
int nombre_racine(partition_t  partition);
graphe_t initialisationgraphe(int taille);
void affichergraphe(graphe_t graphe);
partition_t partitiondegraphe(graphe_t graphe);
void lister_partition(partition_t partition);
void lister_classe(partition_t partition,int racine);
graphe_t kruskal(graphe_t graphe);
graphe_t generation_aleatoire (int nombrenoeud);




