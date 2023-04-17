#include <math.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <SDL2/SDL.h>
#include "jeuvie.h"
#include "matrice.h"
//gcc  jeuvie.c matrice.c -o prog -lSDL2 -lSDL2_gfx -lSDL2_image -lSDL2_ttf -lSDL2_mixer -lSDL2_net
void end_sdl(char ok,                                                 // fin normale : ok = 0 ; anormale ok = 1
                  char const* msg,                                    // message à afficher
                  SDL_Window* window,                                 // fenêtre à fermer
                  SDL_Renderer* renderer) {                           // renderer à fermer
  char msg_formated[255];                                         
  int l;                                                          

  if (!ok) {                                                      
         strncpy(msg_formated, msg, 250);                                 
         l = strlen(msg_formated);                                        
         strcpy(msg_formated + l, " : %s\n");                     

         SDL_Log(msg_formated, SDL_GetError());                   
  }                                                               

  if (renderer != NULL) SDL_DestroyRenderer(renderer);                            
  if (window != NULL)   SDL_DestroyWindow(window);                                        

  SDL_Quit();                                                     

  if (!ok) {                                                      
         exit(EXIT_FAILURE);                                              
  }                                                               
}

void  affiche_matrice(SDL_Renderer* renderer,int** matrice,int ligne,int colonne){
    SDL_Rect rectangle;                                             
    SDL_SetRenderDrawColor(renderer,                                
                                0, 0, 0,                               // mode Red, Green, Blue (tous dans 0..255)
                                255);                                   // 0 = transparent ; 255 = opaque                                                   // y haut gauche du rectangle
    rectangle.w = 20;                                                  // sa largeur (w = width)
    rectangle.h = 20;
    int i,j;
    for (i=0;i<ligne;i++){
        for(j=0;j<colonne;j++){
          if (matrice[i][j]==1){
            rectangle.x = 20*j;                                                    // x haut gauche du rectangle
            rectangle.y = 20*i;
            SDL_RenderFillRect(renderer, &rectangle);
          }
        }
    }
    SDL_RenderPresent(renderer);                                        // affichage
    SDL_Delay(100);                                                    // Pause exprimée en ms

}
void draw(SDL_Renderer* renderer,int** matrice,int ligne,int colonne){
  int i,j;
  int** tmp =cree(ligne,colonne);
  while(1){
    affiche_matrice(renderer,matrice,ligne,colonne);
    SDL_SetRenderDrawColor(renderer,255,255,255,255);
    SDL_RenderClear(renderer);
    copie(matrice,tmp,ligne,colonne);
    for (i=0;i<ligne;i++){
          for(j=0;j<colonne;j++){
            if (matrice[i][j]==1){
              if(voisin(matrice,ligne,colonne,i,j)!=2 && voisin(matrice,ligne,colonne,i,j)!=3){
                tmp[i][j]=0;
                
              }
            }
            else{
              if(voisin(matrice,ligne,colonne,i,j)==3){
                tmp[i][j]=1;
                
          
              }
            }
          }
      }
    copie(tmp,matrice,ligne,colonne);
  }
}



int main(int argc, char** argv) {
  (void)argc;
  (void)argv;

  SDL_Window* window = NULL;
  SDL_Renderer* renderer = NULL;
  int h = 200;
  int w =200;
  SDL_DisplayMode screen;

/*********************************************************************************************************************/  
/*                         Initialisation de la SDL  + gestion de l'échec possible                                   */
  if (SDL_Init(SDL_INIT_VIDEO) != 0) end_sdl(0, "ERROR SDL INIT", window, renderer);

  SDL_GetCurrentDisplayMode(0, &screen);
  printf("Résolution écran\n\tw : %d\n\th : %d\n", screen.w,
              screen.h);

  /* Création de la fenêtre */
  window = SDL_CreateWindow("Premier dessin",
                            SDL_WINDOWPOS_CENTERED,
                            SDL_WINDOWPOS_CENTERED, 800,
                            800,
                            SDL_WINDOW_OPENGL);
  if (window == NULL) end_sdl(0, "ERROR WINDOW CREATION", window, renderer);

  /* Création du renderer */
  renderer = SDL_CreateRenderer(
           window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
  if (renderer == NULL) end_sdl(0, "ERROR RENDERER CREATION", window, renderer);

  /*********************************************************************************************************************/
  /*                                     On dessine dans le renderer                                                   */
                                                      // appel de la fonction qui crée l'image  

int** matrice =cree(40,40);
fill_matrix(matrice,40,40);
insert(matrice,30,30);
insert(matrice,31,31);
insert(matrice,32,29);
insert(matrice,32,30);
insert(matrice,32,31);
draw(renderer,matrice,40,40);


SDL_RenderPresent(renderer);                                        // affichage
SDL_Delay(5000);                                                    // Pause exprimée en ms

  /*********************************************************************************************************************/
  /* on referme proprement la SDL */
  end_sdl(1, "Normal ending", window, renderer);
  return EXIT_SUCCESS;
}