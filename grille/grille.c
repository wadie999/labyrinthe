#include "grille.h"

void genaration_arretes(int taille){
    int a,b;
    for(int i =0;i<(taille+1)*(taille+1);i++){
        a = i+taille+1;
        b = i+1;
        if((i+1)%(taille+1)==0 && a<(taille+1)*(taille+1)){
            printf("{%d - %d} -> |\n",i,a); // les case a droites
        }
        if(taille>=(taille+1)*(taille+1)-i-1 && b<(taille+1)*(taille+1)){
            printf("{%d - %d} -> --\n",i,b); //// les case en bas
        }
        if (taille<(taille+1)*(taille+1)-i-1 && b<(taille+1)*(taille+1) && (i+1)%(taille+1)!=0 ){
            printf("{%d - %d} -> |\n",i,a);
            printf("{%d - %d} -> --\n",i,b);
        }        
        
    }
}

int main()
{
    
    genaration_arretes(4);
    return 0;
}