#include "tas.h"

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

int main()
{
    tas_t* tas = malloc(sizeof(tas_t));
    tas->capacity = 6;
    tas->taille = 6;
    tas->tab = malloc(tas->taille*sizeof(int));
    int tableau[6] = {7, 2, 9, 4, 5, 3};
    int tab12[6] = {7, 2, 9, 4, 5, 3};
    for (int i=0;i<6;i++)
    {
        tas->tab[i] = tableau[i];
        printf("%d ", tas->tab[i]);
    }
    printf("\n\n");

    Build_Min_Heap(tas);

    for (int i=0;i<6;i++)
    {
        printf("%d ", tas->tab[i]);
    }
    printf("\n");

    Heapsort(tas);

    for (int i=0;i<6;i++)
    {
        printf("%d ", tas->tab[i]);
    }

    return 0;
}