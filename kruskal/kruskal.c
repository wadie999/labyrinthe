#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include "Kruskal.h"

//dot -Tpng graphe_avant.dot -o graphe_avant.png
/* ----------------------------------------------------------------------------------------------

    Trouver la classe d’un élément se fait en temps constant, mais fusionner deux classes prend
    un temps O(n), puisqu’il faut parcourir tout le tableau pour repérer les éléments dont il faut
    changer la classe. Une deuxième solution, que nous détaillons maintenant, consiste à choisir un
    représentant dans chaque classe. Fusionner deux classes revient alors à changer de représentant
    pour les éléments de la classe fusionnée. Il apparaı̂t avantageux de représenter la partition par
    une forêt. Chaque classe de la partition constitue un arbre de cette forêt. La racine de l’arbre
    est le représentant de sa classe.

 */

/* ----------------------------------------------------------------------------------------------
   DANS L IMPLEMENTATION ARBROESCENTE , ON UTILISE LA HAUTEUR QUI SERA PRINCIPALEMENT UTILISE DANS LA FUSION  */

partition_t initialisation(int taille)
{       
        partition_t partition;
        partition.taille=taille;
        partition.pere=malloc(taille*sizeof(int));
        partition.hauteur=malloc(taille*sizeof(int));
        for (int i = 0; i < partition.taille ; i++)
             {
                  partition.pere[i] = i;
                  partition.hauteur[i]=1;                   // LA HAUTEUR EST 1 INITIALEMENT
             }
        return partition ;    
}

/* ----------------------------------------------------------------------------------------------
   AFFICHAGE DES ELEMENTS DE L ENSEMBLE AVEC LEUR PERE ASSOCIE  */

void Affichage_partition(partition_t partition)
{
    printf("Les elements :");
    for (int i=0; i<partition.taille;i++)
        printf("%d ",i);
    printf("\n");    
    printf("Leur peres   :");    
    for (int i=0; i<partition.taille;i++)
        printf("%d ",partition.pere[i]);
    printf("\n -----------------------");
    printf("\n");    
}

/* ----------------------------------------------------------------------------------------------
   Chercher le représentant de la classe contenant un élément donné X revient à trouver la racine de
   l’arbre contenant un noeud donné. Ceci se fait par la méthode suivante :   */

int trouveracine(partition_t partition,int x)

{
    while (x != partition.pere[x])
        x = partition.pere[x];
    return x;
}

/* ----------------------------------------------------------------------------------------------
    Chacune des deux méthodes est de complexité O(h), où h
    est la hauteur l’arbre (la plus grande des hauteurs des deux arbres). En fait, on peut améliorer
    l’efficacité de l’algorithme par la règle suivante 
    
    
    Lors de l’union de deux arbres, la racine de l’arbre de moindre taille devient fils de la
    racine de l’arbre de plus grande taille.  */


void fusion(partition_t* partition,int x, int y)
{
    int r = trouveracine(*partition,x);                           // on cherche la racine de x et de y
    int s = trouveracine(*partition,y);
    if ((*partition).hauteur[r] >(*partition).hauteur[s] && r!=s)       
    {
        (*partition).pere[s] = r;
        (*partition).hauteur[s]=0;   
    }
    else if ((*partition).hauteur[r] < (*partition).hauteur[s]  && r!=s )
    {
        (*partition).pere[r] = s;
        (*partition).hauteur[r]=0;
    }
    else if ( (*partition).hauteur[r] == (*partition).hauteur[s]  && r!=s)
    {
        (*partition).pere[s] = r;
        (*partition).hauteur[s]=0;
        (*partition).hauteur[r]=(*partition).hauteur[r]+1;
    }
}



int * lister_composantes(partition_t partition, int pere)
{
    int * liste_composantes=malloc(sizeof(int));
    //int *tableau=malloc(partition.taille*sizeof(int));
    int k=1;
    for (int i=0;i<partition.taille;i++)
        {
            if (partition.pere[i]==pere)
               {  
                liste_composantes[k]=i;
                k++; 
                liste_composantes=(int*)realloc(liste_composantes,k*sizeof(int));
               }      
        }
    liste_composantes[0]=k;
    return liste_composantes;
}


int existe(int * liste,int taille,int element)
{
    int code=0;
    for (int i=0;i<taille;i++)
    {
        if (liste[i]==element)
             code=1;
    }
    return code;
}

int nombre_racine(partition_t  partition)
{
    int nombrepere;
    int * listepere=malloc(partition.taille*sizeof(int));
    for(int i=0;i<partition.taille;i++)
    {
        if  (!existe(listepere,i,partition.pere[i]))
            nombrepere++;
        listepere[i]=partition.pere[i];  
    }
    free(listepere);
    return nombrepere;
}


graphe_t initialisationgraphe(int taille)
{
    graphe_t graphe;
    graphe.nombrenoeud=taille;
    graphe.arrete=malloc(taille*sizeof(arrete_t));
    for (int k=0;k<graphe.nombrenoeud;k++)
    {
        (graphe.arrete[k]).i=k;
        (graphe.arrete[k]).j=k;
    }
    return graphe;
}

void affichergraphe(graphe_t graphe)
{
    printf("votre graphe est constitue par la liste des arretes suivante : \n \n ");
    for (int k=0; k<graphe.nombrearrete;k++)
    {
        printf("(%d ,%d) |",graphe.arrete[k].i,graphe.arrete[k].j);
    }
    printf("\n ----------------- \n");
}

void tracer_graphe(graphe_t graphe, char* fichier)
{
    FILE* fic = NULL;
    fic = fopen(fichier, "w");
    if (fic != NULL)
    {
        fprintf(fic, "graph G {\n");
        for (int k=0; k<graphe.nombrearrete;k++)
        {
            fprintf(fic,"%d--%d;\n",graphe.arrete[k].i,graphe.arrete[k].j);
        }
        fprintf(fic, "}\n");
    }
}
partition_t partitiondegraphe(graphe_t graphe)
{
    partition_t partition=initialisation(graphe.nombrenoeud);
    for (int k=0;k<(partition.taille);k++)
    {
        if (trouveracine(partition,graphe.arrete[k].i)!=trouveracine(partition,graphe.arrete[k].j) ) // s'il ne sont pas dans la meme classe
            fusion(&partition,graphe.arrete[k].i, graphe.arrete[k].j);
    }
    return partition;
}    


void lister_partition(partition_t partition)
{
   printf(" \n Dans votre partition, les classes sont les suivant : ")  ;
   int i;
   for(i = 0; i < partition.taille; i++)
    {
        if(partition.pere[i] == i)                            // Les étiquettes de classes correspondent aux racines.
        printf("%d ", i);
    }
   printf("\n "); 
}

void lister_classe(partition_t partition,int racine)     // Etiquette de classe.        
		                                 
{
    int classe;
    printf("la classe %d est l'ensemble :",racine);
    printf("{");
    for(int i = 0; i < partition.taille; i++)
    {
       classe= trouveracine(partition,partition.pere[i]);
       if(classe == racine)
         printf(" %d ", i);
    }
    printf("}"); 
}

 graphe_t kruskal(graphe_t graphe)
 {
    partition_t partition = initialisation(graphe.nombrenoeud); // 1- creation d une partition dont les elements sont les noeuds du graphe
    graphe_t A=initialisationgraphe(graphe.nombrenoeud); // creation d'une liste d'arretes vide
    A.nombrearrete=0;
    for (int k=0;k<graphe.nombrearrete;k++)
    {
        if (trouveracine(partition,graphe.arrete[k].i)!=trouveracine(partition,graphe.arrete[k].j))
        {
            fusion(&partition,graphe.arrete[k].i,graphe.arrete[k].j);
            A.nombrearrete++;
            A.arrete[A.nombrearrete-1].i=graphe.arrete[k].i;
            A.arrete[A.nombrearrete-1].j=graphe.arrete[k].j;
        }
    }
    return A;
 }

graphe_t generation_aleatoire (int nombrenoeud)
{
    graphe_t graphe_aleatoire=initialisationgraphe(nombrenoeud);
    int n=rand()% 2*nombrenoeud; // le nombre d'arrete est aleatoire aussi
    int k;
    for (int l=0;l<n;l++ )
    {
        k=rand() % nombrenoeud ;
        graphe_aleatoire.arrete[l].i=k;
        k=rand() % nombrenoeud ;
        graphe_aleatoire.arrete[l].j=k;
    }
    graphe_aleatoire.nombrearrete=n;
    return graphe_aleatoire;
}

int main ()
{
      graphe_t graphe=generation_aleatoire(10);
      tracer_graphe(graphe, "aleatoire.dot");
      graphe_t A=kruskal(graphe);
      tracer_graphe(A, "kruskal.dot");

    // graphe_t graphe;
    // graphe=initialisationgraphe(5);
    // graphe.nombrearrete=5;
    // (graphe.arrete[0]).i=0;
    // (graphe.arrete[0]).j=1;

    // (graphe.arrete[1]).i=1;
    // (graphe.arrete[1]).j=2;

    // (graphe.arrete[2]).i=3;
    // (graphe.arrete[2]).j=3;

    // (graphe.arrete[3]).i=3;
    // (graphe.arrete[3]).j=4;

    // (graphe.arrete[4]).i=5;
    // (graphe.arrete[4]).j=5;

    // affichergraphe(graphe);

    // partition_t partition1;
    // partition_t partition2;
    // graphe_t A;

    // A=kruskal(graphe);    
    // affichergraphe(A);
    // partition1=partitiondegraphe(A);
    // Affichage_partition(partition1);
    // lister_partition(partition1);
    // lister_classe(partition1,0);
    // lister_classe(partition1,3);




 }


