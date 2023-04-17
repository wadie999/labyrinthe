#ifndef IMAGE
#define IMAGE
#include <math.h>
#include <stdio.h>
#include <SDL2/SDL.h>
#include <string.h>
#include <SDL2/SDL_image.h> 
#include <stdbool.h>
#include "image.h"
#include "matrice.h"
#include "animationperso.h"

void end_sdl(char ok,char const* msg,SDL_Window* window,SDL_Renderer* renderer);

void play_with_texture_1(SDL_Texture *texture_back, SDL_Window *window,
                         SDL_Renderer *renderer);
void play_with_texture_2(SDL_Texture *my_texture,SDL_Texture *texture_back, SDL_Window*window,SDL_Renderer *renderer,int** ); 
#endif
