#include <SDL2/SDL.h>
#include <math.h>
#include <stdio.h>
#include <string.h>
void end_sdl(char ok,                                                 // fin normale : ok = 0 ; anormale ok = 1
                  char const* msg,                                    // message à afficher
                  SDL_Window* window,                                 // fenêtre à fermer
                  SDL_Renderer* renderer);
void draw_rect(SDL_Renderer* renderer,int w0,int h0);