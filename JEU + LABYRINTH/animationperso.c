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
          

SDL_Texture* load_texture_from_image(char  *  file_image_name, SDL_Window *window, SDL_Renderer *renderer )
{
    SDL_Surface *my_image = NULL;           // Variable de passage
    SDL_Texture* my_texture = NULL;         // La texture

    my_image = IMG_Load(file_image_name);   // Chargement de l'image dans la surface
                                            // image=SDL_LoadBMP(file_image_name); fonction standard de la SDL, 
                                            // uniquement possible si l'image est au format bmp */
    if (my_image == NULL) end_sdl(0, "Chargement de l'image impossible", window, renderer);

    my_texture = SDL_CreateTextureFromSurface(renderer, my_image); // Chargement de l'image de la surface vers la texture
    SDL_FreeSurface(my_image);                                     // la SDL_Surface ne sert que comme élément transitoire 
    if (my_texture == NULL) end_sdl(0, "Echec de la transformation de la surface en texture", window, renderer);

    return my_texture;
}


  
// Affichage d'une texture sur la totalité de la fenêtre
// void play_with_texture_1(SDL_Texture *my_texture, SDL_Window *window,
//                          SDL_Renderer *renderer) 
// {
//   SDL_Rect 
//           source_image = {0},                         // Rectangle définissant la zone de la texture à récupérer
//           window_dimensions = {0},              // Rectangle définissant la fenêtre, on n'utilisera que largeur et hauteur
//           destination = {0};                    // Rectangle définissant où la zone_source_image doit être déposée dans le renderer

//   SDL_GetWindowSize(
//       window, &window_dimensions.w,
//       &window_dimensions.h);                    // Récupération des dimensions de la fenêtre
//   SDL_QueryTexture(my_texture, NULL, NULL,
//                    &source_image.w, &source_image.h);       // Récupération des dimensions de l'image
//   destination = window_dimensions;              // On fixe les dimensions de l'affichage à  celles de la fenêtre
//   /* On veut afficher la texture de façon à ce que l'image occupe la totalité de la fenêtre */
//   SDL_RenderCopy(renderer, my_texture,
//                  &source_image,
//                  &destination);                 // Création de l'élément à afficher
//   SDL_RenderPresent(renderer);                  // Affichage
//   SDL_Delay(2000);                              // Pause en ms
//   SDL_RenderClear(renderer);                    // Effacer la fenêtre
// }

void play_with_texture_1_1(SDL_Texture *my_texture, SDL_Window *window,
                         SDL_Renderer *renderer) 
{
  SDL_Rect 
          source_image = {0},                         // Rectangle définissant la zone de la texture à récupérer
          window_dimensions = {0},              // Rectangle définissant la fenêtre, on n'utilisera que largeur et hauteur
          destination = {0};                    // Rectangle définissant où la zone_source_image doit être déposée dans le renderer

  SDL_GetWindowSize(
      window, &window_dimensions.w,
      &window_dimensions.h);                    // Récupération des dimensions de la fenêtre
  SDL_QueryTexture(my_texture, NULL, NULL,
                   &source_image.w, &source_image.h);       // Récupération des dimensions de l'image
  destination = window_dimensions;              // On fixe les dimensions de l'affichage à  celles de la fenêtre
  /* On veut afficher la texture de façon à ce que l'image occupe la totalité de la fenêtre */
  SDL_RenderCopy(renderer, my_texture,
                 &source_image,
                 &destination);                 // Création de l'élément à afficher
  SDL_RenderPresent(renderer);                  // Affichage
}



void animation_run(SDL_Texture* my_texture,SDL_Texture* mure,SDL_Texture* fond,
                            SDL_Window* window,
                            SDL_Renderer* renderer,int i,int j,int ** matrice) 
{
    SDL_Rect 
           source_fond= {0},                      // Rectangle définissant la zone de la texture à récupérer
           source_image = {0},
           window_dimensions = {0},           // Rectangle définissant la fenêtre, on n'utilisera que largeur et hauteur
           destination = {0};                 // Rectangle définissant où la zone_source_image doit être déposée dans le renderer

    SDL_GetWindowSize(window, &window_dimensions.w,&window_dimensions.h);               // Récupération des dimensions de la fenêtre
    //SDL_QueryTexture(my_texture, NULL, NULL,&source_image.w, &source_image.h);                      // Récupération des dimensions de l'image
    int nbr_img=500;
    source_image.w=48;
    source_image.h=52;
    source_image.y=0;
    // le choix de l'endroit de l'animation 48 est la taille du mur

    destination.x = i*T;
    destination.y = j*T;
    int k=0;
    // la boucle par condition d'arret : la distance a parcourir
    
    while(k<6)
    {
            source_image.x=k*source_image.w;
            float zoom = 1;                     // Facteur de zoom à appliquer    
            destination.w = T;         // La destination est un zoom de la source_image
            destination.h =T   ;    // La destination est un zoom de la source_image
            destination.x = destination.x+T/6;
            //(window_dimensions.w - destination.w) /2 -300 +3*j;     // La destination est au milieu de la largeur de la fenêtre
            // (window_dimensions.h - destination.h) / 2+63;  // La destination est au milieu de la hauteur de la fenêtre
            // play_with_texture_1_1(texture_fond, window,renderer) ;
            play_with_texture_2(mure,fond, window,
                         renderer,matrice);
            SDL_RenderPresent(renderer);
            SDL_RenderCopy(renderer, my_texture,     // Préparation de l'affichage  
                            &source_image,
                            &destination);                                                                                 
            SDL_RenderPresent(renderer);
            SDL_Delay(100);          
            
            k++;
        
    }
}  

void animation_run_back(SDL_Texture* my_texture,SDL_Texture* mure,SDL_Texture* fond,
                            SDL_Window* window,
                            SDL_Renderer* renderer,int i,int j,int ** matrice) 
{
    SDL_Rect 
           source_fond= {0},                      // Rectangle définissant la zone de la texture à récupérer
           source_image = {0},
           window_dimensions = {0},           // Rectangle définissant la fenêtre, on n'utilisera que largeur et hauteur
           destination = {0};                 // Rectangle définissant où la zone_source_image doit être déposée dans le renderer

    SDL_GetWindowSize(window, &window_dimensions.w,&window_dimensions.h);               // Récupération des dimensions de la fenêtre
    //SDL_QueryTexture(my_texture, NULL, NULL,&source_image.w, &source_image.h);                      // Récupération des dimensions de l'image
    int nbr_img=500;
    source_image.w=48;
    source_image.h=52;
    source_image.y=0;
    // le choix de l'endroit de l'animation 48 est la taille du mur

    destination.x = i*T;
    destination.y = j*T;
    int k=0;
    // la boucle par condition d'arret : la distance a parcourir
    while(k<6)
    {
            source_image.x=(6-k)*source_image.w;
            float zoom = 1;                     // Facteur de zoom à appliquer    
            destination.w =T ;         // La destination est un zoom de la source_image
            destination.h = T;         // La destination est un zoom de la source_image
            destination.x = destination.x-T/6;
            //(window_dimensions.w - destination.w) /2 -300 +3*j;     // La destination est au milieu de la largeur de la fenêtre
            // (window_dimensions.h - destination.h) / 2+63;  // La destination est au milieu de la hauteur de la fenêtre
            // play_with_texture_1_1(texture_fond, window,renderer) ;
            play_with_texture_2(mure,fond, window,
                         renderer,matrice);
            SDL_RenderPresent(renderer); 
            SDL_RenderCopy(renderer, my_texture,     // Préparation de l'affichage  
                            &source_image,
                            &destination);                                                                                
            SDL_RenderPresent(renderer);
            SDL_Delay(100);           
            
            k=k+1;
        
    }
    
} 

void animation_climb(SDL_Texture* my_texture,SDL_Texture* mure,SDL_Texture* fond,
                            SDL_Window* window,
                            SDL_Renderer* renderer,int i,int j,int ** matrice,int mouvement) 
{
    SDL_Rect 
           source_fond= {0},                      // Rectangle définissant la zone de la texture à récupérer
           source_image = {0},
           window_dimensions = {0},           // Rectangle définissant la fenêtre, on n'utilisera que largeur et hauteur
           destination = {0};                 // Rectangle définissant où la zone_source_image doit être déposée dans le renderer

    SDL_GetWindowSize(window, &window_dimensions.w,&window_dimensions.h);               // Récupération des dimensions de la fenêtre
    //SDL_QueryTexture(my_texture, NULL, NULL,&source_image.w, &source_image.h);                      // Récupération des dimensions de l'image
    int nbr_img=500;
    source_image.w=48;
    source_image.h=52;
    source_image.y=0;
    // le choix de l'endroit de l'animation 48 est la taille du mur

    destination.y = j*T;
    destination.x = i*T;
    int k=0;
    // la boucle par condition d'arret : la distance a parcourir
    if (mouvement == BAS)
    {
        while(destination.y<(j+1)*T)
        {
                source_image.x=k*source_image.w;
                float zoom = 1;                     // Facteur de zoom à appliquer    
                destination.w = T ;         // La destination est un zoom de la source_image
                destination.h = T;         // La destination est un zoom de la source_image
                destination.y= destination.y+T/6;
                //(window_dimensions.w - destination.w) /2 -300 +3*j;     // La destination est au milieu de la largeur de la fenêtre
                // (window_dimensions.h - destination.h) / 2+63;  // La destination est au milieu de la hauteur de la fenêtre
                // play_with_texture_1_1(texture_fond, window,renderer) ;
                play_with_texture_2(mure,fond, window,
                         renderer,matrice);
                SDL_RenderPresent(renderer); 
                SDL_RenderCopy(renderer, my_texture,     // Préparation de l'affichage  
                                &source_image,
                                &destination);                                                       
                SDL_SetRenderDrawColor(renderer,247,246,255,255);                          
                SDL_RenderPresent(renderer);
                SDL_Delay(100);           
                
                k++;
            
        }
    }
    else if (mouvement == HAUT)
    {
        while(destination.y>(j-1)*T)
        {
                source_image.x=k*source_image.w;
                float zoom = 1;                     // Facteur de zoom à appliquer    
                destination.w = T ;         // La destination est un zoom de la source_image
                destination.h = T;         // La destination est un zoom de la source_image
                destination.y= destination.y-T/6;
                //(window_dimensions.w - destination.w) /2 -300 +3*j;     // La destination est au milieu de la largeur de la fenêtre
                // (window_dimensions.h - destination.h) / 2+63;  // La destination est au milieu de la hauteur de la fenêtre
                // play_with_texture_1_1(texture_fond, window,renderer) ;
                play_with_texture_2(mure,fond, window,
                         renderer,matrice);
                SDL_RenderPresent(renderer);
                SDL_RenderCopy(renderer, my_texture,     // Préparation de l'affichage  
                                &source_image,
                                &destination);                                                       
                SDL_SetRenderDrawColor(renderer,247,246,255,255);                          
                SDL_RenderPresent(renderer);
                SDL_Delay(100);                           
                k++;
            
        }
    }
}


void animation_attack(SDL_Texture* my_texture,SDL_Texture* mure,SDL_Texture* fond,
                            SDL_Window* window,
                            SDL_Renderer* renderer,int i,int j,int ** matrice) 
{
    SDL_Rect 
           source_fond= {0},                      // Rectangle définissant la zone de la texture à récupérer
           source_image = {0},
           window_dimensions = {0},           // Rectangle définissant la fenêtre, on n'utilisera que largeur et hauteur
           destination = {0};                 // Rectangle définissant où la zone_source_image doit être déposée dans le renderer

    SDL_GetWindowSize(window, &window_dimensions.w,&window_dimensions.h);               // Récupération des dimensions de la fenêtre
    //SDL_QueryTexture(my_texture, NULL, NULL,&source_image.w, &source_image.h);                      // Récupération des dimensions de l'image
    int nbr_img=500;
    source_image.w=48;
    source_image.h=52;
    source_image.y=0;
    // le choix de l'endroit de l'animation 48 est la taille du mur
    destination.w = T ;         // La destination est un zoom de la source_image
    destination.h = T ; 
    destination.x = i*T;
    destination.y = j*T;
    int k=0;
    // la boucle par condition d'arret : la distance a parcourir
    while(k<6)
    {
            source_image.x=k*source_image.w;
            play_with_texture_2(mure,fond, window,
                         renderer,matrice);
            SDL_RenderPresent(renderer);
            SDL_RenderCopy(renderer, my_texture,     // Préparation de l'affichage  
                            &source_image,
                            &destination);                                                       
            SDL_SetRenderDrawColor(renderer,247,246,255,255);                          
            SDL_RenderPresent(renderer);
            SDL_Delay(100);          
            
            k++;
        
    }   
}
void animation_attack_gauche(SDL_Texture* my_texture,SDL_Texture* mure,SDL_Texture* fond,
                            SDL_Window* window,
                            SDL_Renderer* renderer,int i,int j,int ** matrice) 
{
    SDL_Rect 
           source_fond= {0},                      // Rectangle définissant la zone de la texture à récupérer
           source_image = {0},
           window_dimensions = {0},           // Rectangle définissant la fenêtre, on n'utilisera que largeur et hauteur
           destination = {0};                 // Rectangle définissant où la zone_source_image doit être déposée dans le renderer

    SDL_GetWindowSize(window, &window_dimensions.w,&window_dimensions.h);               // Récupération des dimensions de la fenêtre
    //SDL_QueryTexture(my_texture, NULL, NULL,&source_image.w, &source_image.h);                      // Récupération des dimensions de l'image
    int nbr_img=500;
    source_image.w=48;
    source_image.h=52;
    source_image.y=0;
    // le choix de l'endroit de l'animation 48 est la taille du mur
    destination.w = T ;         // La destination est un zoom de la source_image
    destination.h = T; 
    destination.x = i*T;
    destination.y = j*T;
    int k=0;
    // la boucle par condition d'arret : la distance a parcourir
    while(k<6)
    {
            source_image.x=(6-k)*source_image.w;
            play_with_texture_2(mure,fond, window,
                         renderer,matrice);
            SDL_RenderPresent(renderer); 
            SDL_RenderCopy(renderer, my_texture,     // Préparation de l'affichage  
                            &source_image,
                            &destination);                                                       
            SDL_RenderPresent(renderer);                           
            SDL_Delay(100);          
            
            k++;
        
    }   
}
void afficher_perso(SDL_Texture* my_texture,SDL_Texture* mure,SDL_Texture* fond,
                            SDL_Window* window,
                            SDL_Renderer* renderer,int i,int j,int** matrice) 
{
    SDL_Rect 
           source_fond= {0},                      // Rectangle définissant la zone de la texture à récupérer
           source_image = {0},
           window_dimensions = {0},           // Rectangle définissant la fenêtre, on n'utilisera que largeur et hauteur
           destination = {0};                 // Rectangle définissant où la zone_source_image doit être déposée dans le renderer

    SDL_GetWindowSize(window, &window_dimensions.w,&window_dimensions.h);               // Récupération des dimensions de la fenêtre
    //SDL_QueryTexture(my_texture, NULL, NULL,&source_image.w, &source_image.h);                      // Récupération des dimensions de l'image
    
    source_image.w=48;
    source_image.h=52;
    source_image.y=0;
    // le choix de l'endroit de l'animation 48 est la taille du mur

    destination.x = i*T;
    destination.y = j*T;
    source_image.x=2*source_image.w;
    // la boucle par condition d'arret : la distance a parcourir
    float zoom = 1;                     // Facteur de zoom à appliquer    
    destination.w = T ;         // La destination est un zoom de la source_image
    destination.h = T;         // La destination est un zoom de la source_image
    play_with_texture_2(mure,fond, window,
                         renderer,matrice); 
    SDL_RenderPresent(renderer); 
    SDL_RenderCopy(renderer, my_texture,     // Préparation de l'affichage  
                            &source_image,
                            &destination);                                                                                 
    SDL_RenderPresent(renderer);
             
} 