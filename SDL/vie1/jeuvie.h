#ifndef JEUVIE
#define JEUVIE
#include <math.h>
#include <stdio.h>
#include <SDL2/SDL.h>
#include <string.h>
#include <stdbool.h>
#include "matrice.h"

void end_sdl(char ok,                                                 // fin normale : ok = 0 ; anormale ok = 1
                  char const* msg,                                    // message à afficher
                  SDL_Window* window,                                 // fenêtre à fermer
                  SDL_Renderer* renderer);                           // renderer à fermer
void  affiche_matrice(SDL_Renderer* renderer,int** matrice,int ligne,int colonne);
void draw(SDL_Renderer* renderer,int** matrice,int ligne,int colonne);
#endif 