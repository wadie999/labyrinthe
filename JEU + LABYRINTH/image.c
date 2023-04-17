#include <math.h>
#include <stdio.h>
#include <SDL2/SDL.h>
#include <string.h>
#include <SDL2/SDL_image.h> 
#include <stdbool.h>
#include "image.h"
#include "matrice.h"
#include "animationperso.h"
#define T 21
/* 

La fonction loadImage doit charger une image et renvoyer la texture correspondante. Elle doit donc charger l’image dans une surface, 
convertir cette surface en texture et renvoyer cette texture sans oublier de vérifier les retours des fonctions employées. 

    1- on crée une surface (type de données SDL1)
    2- on charge l'image dans la SDL_Surface,
    3- on transforme la surface en texture (type de données correspondant en SDL2)
   
*/

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


void play_with_texture_1(SDL_Texture *texture_back, SDL_Window *window,
                         SDL_Renderer *renderer) {
  SDL_Rect 
          source = {0},                         // Rectangle définissant la zone de la texture à récupérer
          window_dimensions = {0},              // Rectangle définissant la fenêtre, on n'utilisera que largeur et hauteur
          destination = {0};                    // Rectangle définissant où la zone_source doit être déposée dans le renderer

  SDL_GetWindowSize(
      window, &window_dimensions.w,
      &window_dimensions.h);                    // Récupération des dimensions de la fenêtre
  SDL_QueryTexture(texture_back, NULL, NULL,
                   &source.w, &source.h);       // Récupération des dimensions de l'image

  destination = window_dimensions;              // On fixe les dimensions de l'affichage à  celles de la fenêtre

  /* On veut afficher la texture de façon à ce que l'image occupe la totalité de la fenêtre */

  SDL_RenderCopy(renderer, texture_back,
                 &source,
                 &destination);
               // Création de l'élément à afficher
                   // Affichage

}


  
// Affichage d'une texture sur la totalité de la fenêtre
void play_with_texture_2(SDL_Texture *my_texture,SDL_Texture *texture_back, SDL_Window *window,
                         SDL_Renderer *renderer,int** matrice) 
{
  SDL_Rect 
          source_image = {0},                          // Rectangle définissant la zone de la texture à récupérer
          window_dimensions = {0},              // Rectangle définissant la fenêtre, on n'utilisera que largeur et hauteur
          destination = {0};                    // Rectangle définissant où la zone_source_image doit être déposée dans le renderer

  SDL_GetWindowSize(
      window, &window_dimensions.w,
      &window_dimensions.h);                    // Récupération des dimensions de la fenêtre
  SDL_QueryTexture(my_texture, NULL, NULL,
                   &source_image.w, &source_image.h);       // Récupération des dimensions de l'image
  
  destination.h = T;
  destination.w = T;
  
  
  play_with_texture_1_1(texture_back,window,
                        renderer);
  SDL_RenderPresent(renderer);                                  
  int i,j;
  for (i=0;i<2*T+1;i++){
      for(j=0;j<2*T+1;j++){
        if (matrice[i][j]==1){
          destination.x = i*T;          
          destination.y = j*T;
          SDL_RenderCopy(renderer, my_texture,
                &source_image,
                &destination);
        }
      }
  }
  SDL_RenderPresent(renderer);                                        // affichage

                                                                       // Pause exprimée en ms


}