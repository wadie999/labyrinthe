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
//mure = 48*48

// gcc  *.c -o jeu -lSDL2 -lSDL2_gfx -lSDL2_image -lSDL2_ttf -lSDL2_mixer -lSDL2_net -lm 
int main(int argc, char* argv[]) 
{     
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
    pWindow = SDL_CreateWindow("rendu",SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 20*48, 20*48, SDL_WINDOW_SHOWN);
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
    int i =1,j=17;
    int** matrice =cree(20,20);
    fill_matrix(matrice,20,20);
    for(int k=1;k<=20;k++){
        insert(matrice,k,k);
        insert(matrice,k,1);
        insert(matrice,1,k);
        insert(matrice,k,20);
        insert(matrice,20,k);
        insert(matrice,21-k,k);

    }
    matrice[19][10]=0;
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
                        if(i==18 && j == 10){
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