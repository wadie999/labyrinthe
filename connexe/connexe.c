#include "connexe.h"



int ** matriceadjac(int taille)
{
    int** matrice = NULL;
    matrice = malloc(taille*sizeof(int*));
    srand(time(NULL));
    for (int i=0;i<taille;i++)
    {
        matrice[i] = malloc(taille*sizeof(int));
    }
    int rnd ;
    for (int i=0;i<taille;i++)
    {
        for (int j=0;j<taille;j++)
        {
            
            matrice[i][j] = rand() % 2;
            matrice[j][i] = matrice[i][j];

        }
    }
    return matrice;

}
void Affichermatrice(int** matrice, int taille)
{
    for (int i=0;i<taille;i++)
    {
        printf("[ ");
        for (int j=0;j<taille;j++)
        {
            printf("%d ", matrice[i][j]);
        }
        printf("]\n");
    }
}



int main(void)
{
    int ** m = matriceadjac(6);
    Affichermatrice(m,6);
    return 0;
}