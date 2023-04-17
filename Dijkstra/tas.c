#include "tas.h"
#include <time.h>

void Exchange(int* a, int* b)
{
    int tmp;
    tmp = *a;
    *a = *b;
    *b = tmp;
}

int Parent(int i)
{
    if (!i) return (i-1)/2;
}

int Left(int i)
{
    return 2*i + 1;
}

int Right(int i)
{
    return 2*i + 2;
}

void Min_Heapify(tas_t* tas, int i)
{
    int l = Left(i), r = Right(i), min = i;

    if ((l < tas->taille) && (tas->tab[l] < tas->tab[i])) min = l;
    if ((r < tas->taille) && (tas->tab[r] < tas->tab[min])) min = r;
    if (min != i)
    {
        Exchange(&tas->tab[i], &tas->tab[min]);
        Min_Heapify(tas, min);
    }
}

void Build_Min_Heap(tas_t* tas)
{
    int i=(tas->taille)/2 - 1;
    for (i=(tas->taille)/2 - 1;i>=0;i--) Min_Heapify(tas, i); 
}

void Heapsort(tas_t* tas)
{
    Build_Min_Heap(tas);
    for (int i = tas->taille - 1;i>=0;i--)
    {
        Exchange(&tas->tab[i],&tas->tab[0]);
        tas->taille = i;
        Min_Heapify(tas, 0);
    }
}

int intComparator ( const void * first, const void * second ) {
    int firstInt = * (const int *) first;
    int secondInt = * (const int *) second;
    return firstInt - secondInt;
}

int main()
{

 tas_t* tas = malloc(sizeof(tas_t));
 tas->capacity = 20;
 tas->taille = 20;
 tas->tab = malloc(tas->taille*sizeof(int));
 int tableau[20] = {7, 2, 9, 4, 5, 3,10,8,22,14,32,15,54,1,11,16,39,87,88,100};
 int tab12[20] = {7, 2, 9, 4, 5, 3,10,8,22,14,32,15,54,1,11,16,39,87,88,100};
 for (int i=0;i<20;i++)
 {
 tas->tab[i] = tableau[i];
 printf("%d ", tas->tab[i]);
 }
 printf("\n\n");

 Heapsort(tas);
 for (int i=0;i<20;i++)
 {
 printf("%d ", tas->tab[i]);
 }
 printf("\n");


 clock_t
 temps_initial, 
 temps_final; /* Temps final en micro-secondes */
 float temps_cpu; /* Temps total en secondes */
 temps_initial =clock();
 Heapsort(tas);
 temps_final =clock();
 temps_cpu= (temps_final-temps_initial);
 printf("le temps du tri par tas est : %f \n",temps_cpu);
 temps_initial =clock();
 qsort( tableau,20, sizeof(int),intComparator);
 temps_final =clock();
 temps_cpu= (temps_final-temps_initial);
 printf("le tempsdu tri par qsort est : %f \n",temps_cpu);
 
 for (int i=0;i<6;i++)
 {
 printf("%d ", tas->tab[i]);
 }

 return 0;
}