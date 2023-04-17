#include <math.h>
#include <stdio.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <string.h>
#include <SDL2/SDL_image.h> 
#include <stdbool.h>
#include "image.h"
#include "matrice.h"
#include "animationperso.h"
#define N 1
#define E 2
#define S 4
#define O 8
#define T 21
//mure = 48*48

// gcc  *.c -o jeu -lSDL2 -lSDL2_gfx -lSDL2_image -lSDL2_ttf -lSDL2_mixer -lSDL2_net -lm 
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
void AfficherGrille(int** grille, int lig, int col)
{
    for (int i=0;i<lig;i++)
    {
        printf("[ ");
        for (int j=0;j<col;j++)
        {
            printf("%d ", grille[i][j]);
        }
        printf("]\n");
    }
}

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



int * arreter_composantes(partition_t partition, int pere)
{
    int * arrete_composantes=malloc(sizeof(int));
    //int *tableau=malloc(partition.taille*sizeof(int));
    int k=1;
    for (int i=0;i<partition.taille;i++)
        {
            if (partition.pere[i]==pere)
               {  
                arrete_composantes[k]=i;
                k++; 
                arrete_composantes=(int*)realloc(arrete_composantes,k*sizeof(int));
               }      

        }
    arrete_composantes[0]=k;
    return arrete_composantes;
}


int existe(int * arrete,int taille,int element)
{
    int code=0;
    for (int i=0;i<taille;i++)
    {
        if (arrete[i]==element)
             code=1;
    }
    return code;
}

int nombre_racine(partition_t  partition)
{
    int nombrepere;
    int * arretepere=malloc(partition.taille*sizeof(int));
    for(int i=0;i<partition.taille;i++)
    {
        if  (!existe(arretepere,i,partition.pere[i]))
            nombrepere++;
        arretepere[i]=partition.pere[i];  
    }
    free(arretepere);
    return nombrepere;
}


graphe_t initialisationgraphe(int taille)
{
    graphe_t graphe;
    graphe.nombrenoeud=taille;
    graphe.nombrearrete=taille;
    graphe.arrete=malloc(taille*sizeof(arrete_t));

    // for (int k=0;k<graphe.nombrenoeud;k++)
    // {
    //     (graphe.arrete[k]).i=k;
    //     (graphe.arrete[k]).j=k;
    // }
    return graphe;
}

void affichergraphe(graphe_t graphe)
{
    printf("votre graphe est constitue par la arrete des arretes suivante : \n \n ");
    for (int k=0; k<graphe.nombrearrete;k++)
    {
        printf("(%d ,%d) |",graphe.arrete[k].i,graphe.arrete[k].j);
    }
    printf("\n ----------------- \n");
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


void arreter_partition(partition_t partition)
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

void arreter_classe(partition_t partition,int racine)     // Etiquette de classe.        
		                                 
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

void echanger(int *i,int *j)
{
    int tmp=*i;
    *i=*j;
    *j=tmp;
}

graphe_t Ficher_yate(graphe_t graphe)
{
    graphe_t ficher;
    int h;
    for (int l=graphe.nombrearrete-1;l>0;l--)
    {
        h=rand() % l;
        echanger(&graphe.arrete[l].i,&graphe.arrete[h].i);
        echanger(&graphe.arrete[l].j,&graphe.arrete[h].j);
    }
    ficher=graphe;
    return ficher;
}



graphe_t kruskal(graphe_t graphe)
 {
    partition_t partition = initialisation(graphe.nombrenoeud); // 1- creation d une partition dont les elements sont les noeuds du graphe
    graphe_t A=initialisationgraphe(graphe.nombrenoeud); // creation d'une arrete d'arretes vide
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
    int n=rand()% 2*nombrenoeud  ; // le nombre d'arrete est aleatoire aussi
    graphe_aleatoire.nombrearrete=n;
    int k;
    for (int l=0;l<n;l++)
    {
        k=rand() % nombrenoeud ;
        graphe_aleatoire.arrete[l].i=k;
        k=rand() % nombrenoeud;
        graphe_aleatoire.arrete[l].j=k;
    } 
    return graphe_aleatoire;
}

// aij=a11+p(i-1)+(j-1)
graphe_t generation_graphe(int n)
{
    graphe_t graphe=initialisationgraphe(n*n);
    graphe.nombrearrete=2*n*n;
    for (int k=0;k<n;k++)
    {
        for (int h=0;h<n;h++)
        {
            graphe.arrete[n*k+h].i= n*k+h;
            graphe.arrete[n*k+h].j= n*k+h+1;
        }
    }
    return graphe;
}
//taille+1 = taille matrice 
graphe_t generation_grille(int taille){
    taille--;
    graphe_t graphe=initialisationgraphe(4*taille +2*(taille-1)*taille);  
    int a,b;
    int cpt =0;
    for(int k =0;k<(taille+1)*(taille+1);k++){
        a = k+taille+1;
        b = k+1;
        if((k+1)%(taille+1)==0 && a<(taille+1)*(taille+1)){
            // printf("{%d - %d} -> |\n",k,a); // les case a droites
            graphe.arrete[cpt].i=k;
            graphe.arrete[cpt].j=a;
            cpt++;
        }
        if(taille>=(taille+1)*(taille+1)-k-1 && b<(taille+1)*(taille+1)){
            // printf("{%d - %d} -> --\n",k,b); //// les case en bas
            graphe.arrete[cpt].i=k;
            graphe.arrete[cpt].j=b;
            cpt++;
        }

        else if ( (k+1)%(taille+1)!=0 ){
            graphe.arrete[cpt].i=k;
            graphe.arrete[cpt].j=a;
            cpt++;
            graphe.arrete[cpt].i=k;
            graphe.arrete[cpt].j=b;
            cpt++;
            // printf("{%d - %d} -> |\n",k,a);
            // printf("{%d - %d} -> --\n",k,b);
        }          
    }
    return graphe;
}
int ** generer_matrice(int taille){
    int ** matrice=malloc(taille*sizeof(int*));
    for(int k=0;k<taille;k++){
        matrice[k]=malloc(taille*sizeof(int));
        for(int l=0;l<taille;l++){
            matrice[k][l]=N+S+O+E;
    } 
    }
    return matrice;
}
int** graph_en_matrice(int taille){
    graphe_t graphe= generation_grille(taille);
    graphe = Ficher_yate(graphe);
    graphe = Ficher_yate(graphe);
    graphe = Ficher_yate(graphe);
    graphe = kruskal(graphe);

    int ligne,colonne;
    int **matrice =generer_matrice(taille);
    for(int k =0;k<=graphe.nombrearrete;k++){
       colonne = (graphe.arrete[k].i)%taille;
       ligne = (graphe.arrete[k].i)/taille;
       
       if(colonne<taille && (graphe.arrete[k].i)+1==(graphe.arrete[k].j)){
           matrice[ligne][colonne]-=E;
           matrice[ligne][colonne+1]-=O;
       }
       if(ligne<taille && (graphe.arrete[k].i)+taille==(graphe.arrete[k].j) ){
           matrice[ligne][colonne]-=S;
           matrice[ligne+1][colonne]-=N;
       }
    }
    return matrice;
}
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
            if(i==0 || j==0 || i ==(ligne-1) || j==(colonne-1)){
                matrice[i][j]=1;
            }
            
        }
    }
}
//matrice 1 si mure 0 sinon
int **matrice_a_dessiner(int** matrice,int taille){
    int t = taille*2+1;
    int ** final =cree(t,t);
    int k ,l;
    fill_matrix(final,t,t);
    for(int i =0;i<taille;i++){
        for(int j=0;j<taille;j++){
            k = 2*i +1;
            l = 2*j +1;
            if(matrice[i][j] & E){
                final[k][l+1]=1;

            }
            if(matrice[i][j] & S){
                final[k+1][l]=1;
            }
            final[k+1][l+1]=1;
        }
    }
    return final;
}




int main(int argc, char* argv[]) 
{    
    int t = T*2+1;
    if(SDL_Init(SDL_INIT_VIDEO) < 0)     
    {         
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "[DEBUG] > %s", SDL_GetError());         
        return EXIT_FAILURE;     
    }    
    SDL_Texture  * texture1 = NULL; 
    SDL_Texture  * texture3 = NULL; 
    SDL_Texture  * texture2 = NULL;
    SDL_Texture  * texture4 = NULL;    
    SDL_Texture  * texture5 = NULL;
    SDL_Texture  * texture6 = NULL; 
    SDL_Texture  * texture7 = NULL;
    SDL_Texture  * texture8 = NULL;
    SDL_Texture  * texture9 = NULL; 
    SDL_Texture  * texture10 = NULL;      
    SDL_Window   * pWindow;  
    SDL_Renderer * pRenderer; 
    pWindow = SDL_CreateWindow("rendu",SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, t*T, t*T, SDL_WINDOW_SHOWN);
    if (pWindow == NULL)     
    {         
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "[DEBUG] > %s", SDL_GetError());         
        SDL_Quit();         
        return EXIT_FAILURE;     
    }  
    pRenderer = SDL_CreateRenderer(pWindow, -1, SDL_RENDERER_ACCELERATED);       
    if (pRenderer == NULL)     
    {         
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "[DEBUG] > %s", SDL_GetError());         
        SDL_Quit();         
        return EXIT_FAILURE;     
    }  
    texture3=load_texture_from_image("Punk_climb.png",pWindow,pRenderer);
    texture1=load_texture_from_image("Punk_run.png",pWindow, pRenderer);   /*     creation de la  texture qui contient l'image    */
    texture2=load_texture_from_image("Punk_attack3.png",pWindow, pRenderer);
    texture4=load_texture_from_image("Punk_run_back.png",pWindow, pRenderer);
    texture5=load_texture_from_image("Punk_attack3_back.png",pWindow, pRenderer);
    texture6=load_texture_from_image("mur.png",pWindow, pRenderer);
    texture7=load_texture_from_image("Back.png",pWindow, pRenderer);
    texture8=load_texture_from_image("atack_haut_bas.png",pWindow, pRenderer);
    texture9=load_texture_from_image("game_over.jpg",pWindow, pRenderer);
    texture10=load_texture_from_image("win.jpg",pWindow, pRenderer);
    SDL_SetRenderDrawColor(pRenderer,247,246,255,255);
    SDL_RenderClear(pRenderer);    
    SDL_bool lancer_prog = SDL_TRUE;
    SDL_bool paused = SDL_FALSE;
    int i =1,j=1;
    int** matrice = graph_en_matrice(T);
    matrice=matrice_a_dessiner(matrice,T);
    matrice[t-1][t-2]=0;
    int marteau = 5;
    int code = 1;
    int fin = 0;
    afficher_perso(texture2,texture6,texture7,pWindow,pRenderer,i,j,matrice);
    
    while(lancer_prog)
    {
        
    SDL_Event event;
    while(SDL_PollEvent(&event) && lancer_prog)
    {
        switch(event.type)
        {
            case SDL_QUIT :
                lancer_prog = SDL_FALSE;
                break;
            case SDL_KEYDOWN :
                code = 1;
                switch (event.key.keysym.sym) 
                {
                case SDLK_LEFT:
                    if (!matrice[i-1][j]){
                        animation_run_back(texture4,texture6,texture7,pWindow,pRenderer,i,j,matrice);
                        i--;
                    }                               // 'p'                            // 'SPC'                                             // basculement pause/unpause
                    break;
                case SDLK_RIGHT:                                // 'p'                            // 'SPC'
                    if (!matrice[i+1][j]){
                        if(i==t-2 && j == t-2){
                            animation_run(texture1,texture6,texture7,pWindow,pRenderer,i,j,matrice);
                            play_with_texture_1_1(texture10,pWindow,pRenderer);
                            SDL_Delay(2000);
                            lancer_prog = SDL_FALSE;
                            
                        }
                        else{
                        animation_run(texture1,texture6,texture7,pWindow,pRenderer,i,j,matrice);
                        i++;
                        }
                    }
                                             // basculement pause/unpause
                    break;
                case SDLK_UP:
                    if (!matrice[i][j-1]){
                        animation_climb(texture3,texture6,texture7,pWindow,pRenderer,i,j,matrice,HAUT);
                        j--;
                    }                                // 'p'                            // 'SPC'
                                             // basculement pause/unpause
                    break;
                case SDLK_DOWN:
                    if (!matrice[i][j+1]){
                        animation_climb(texture3,texture6,texture7,pWindow,pRenderer,i,j,matrice,BAS);
                        j++;
                    }                                   // 'p'                            // 'SPC'
                                             // basculement pause/unpause
                    break;
                case SDLK_f:
                    animation_attack(texture2,texture6,texture7,pWindow,pRenderer,i,j,matrice);
                    if (matrice[i+1][j] && (i+1)!=19){
                        matrice[i+1][j]=0;
                        marteau--;
                    } 
                    
                    break;
                case SDLK_s:
                    animation_attack_gauche(texture5,texture6,texture7,pWindow,pRenderer,i,j,matrice);
                    if (matrice[i-1][j] && (i-1)!=0  ){
                        matrice[i-1][j]=0;
                        marteau--;
                    } 
                    break;
                case SDLK_e:
                    animation_attack(texture8,texture6,texture7,pWindow,pRenderer,i,j,matrice);
                    if (matrice[i][j-1] && (j-1)!=0){
                        matrice[i][j-1]=0;
                        marteau--;
                    } 
                    
                    break;
                case SDLK_d:
                    animation_attack(texture8,texture6,texture7,pWindow,pRenderer,i,j,matrice);
                    if (matrice[i][j+1] && (j+1)!=19){
                        matrice[i][j+1]=0;
                        marteau--;
                    } 
                    
                    break;
                case SDLK_ESCAPE:
                case SDLK_q :
                    lancer_prog = SDL_FALSE;
                    break;
                default :
                    break;    
                }
                
                break;
            default :
                code =0;
                break;
        }
    if (code){
        afficher_perso(texture2,texture6,texture7,pWindow,pRenderer,i,j,matrice);        
        if(!marteau){
            play_with_texture_1_1(texture9,pWindow,pRenderer);
            SDL_Delay(2000);
            lancer_prog = SDL_FALSE;
        }
    }  
    }
    }

    SDL_DestroyRenderer(pRenderer);      
    SDL_DestroyWindow(pWindow);
    SDL_Quit();
    
    
    return EXIT_SUCCESS;    
}