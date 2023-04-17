#include <math.h>
#include <stdio.h>
#include <SDL2/SDL.h>
#include <string.h>
#include <stdbool.h>
#include "matrice.h"

int** cree(int ligne,int colonne){
    int ** matrice = NULL;
    matrice = malloc(ligne*sizeof(int*));
    int i = 0; 
    for(i=0;i<ligne;i++){
        matrice[i]=malloc(colonne*sizeof(int));
    }
    return matrice;
}
void fill_matrix(int** matrice,int ligne,int colonne){
    int i,j;
    for (i=0;i<ligne;i++){
        for(j=0;j<colonne;j++){
            matrice[i][j]=0;
        }
    }
}
void afficher(int** matrice,int ligne, int colonne){
    int i,j;
    for (i=0;i<ligne;i++){
        for(j=0;j<colonne;j++){
            printf("%d ",matrice[i][j]);
        }
        printf("\n");
    }
}
void copie(int**origine,int**destination,int ligne, int colonne){
    int i,j;
    for (i=0;i<ligne;i++){
        for(j=0;j<colonne;j++){
            destination[i][j]=origine[i][j];
        }
    }
}
void insert(int**matrice,int x,int y){
    matrice[x-1][y-1]=1;
}
int voisin(int**matrice,int ligne,int colonne,int x,int y){
    int result =0;
    int j =-1;
    int k =-1;

    int contour_voisin=0;
    for (j=-1;j<2;j++){
        for (k=-1;k<2;k++){
            result += matrice[(x+j+ligne)%ligne][(y+k+colonne)%colonne];            
        }
    }
    result -=matrice[(x+ligne)%ligne][(y+colonne)%colonne];
    return result;
}


// int main(){
//     int** matrice =cree(5,5);
//     fill_matrix(matrice,5,5);
//     insert(matrice,1,1);
//     insert(matrice,2,2);
//     insert(matrice,3,1);
//     insert(matrice,3,2);
//     insert(matrice,3,3);
//     afficher(matrice,5,5);
//     int i,j,k;
//     int ligne=5;
//     int colonne=5;
//     // int** tmp =cree(ligne,colonne);
//     // copie(matrice,tmp,ligne,colonne);
//     // printf("----------\n");
    
//     // tmp[4][4]=5;
//     // afficher(tmp,ligne,colonne);
//     // copie(tmp,matrice,ligne,colonne);
//     // afficher(matrice,5,5);
//     int** tmp =cree(ligne,colonne);
//     copie(matrice,tmp,ligne,colonne);
//     for (i=0;i<ligne;i++){
//         for(j=0;j<colonne;j++){
//             if (matrice[i][j]==1){
//             if(voisin(matrice,ligne,colonne,i,j)!=2 && voisin(matrice,ligne,colonne,i,j)!=3){
//                 tmp[i][j]=0;
                
//             }
//             }
//             else{
//             if(voisin(matrice,ligne,colonne,i,j)==3){
//                 tmp[i][j]=1;
                
        
//             }
//             }
//         }
//     }
//     printf("---------------------\n");
//     copie(tmp,matrice,ligne,colonne);
//     afficher(tmp,5,5);
//     return 0;
// }