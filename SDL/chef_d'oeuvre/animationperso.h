#ifndef ANIMATION
#define ANIMATION
#include <math.h>
#include <stdio.h>
#include <SDL2/SDL.h>
#include <string.h>
#include <SDL2/SDL_image.h> 
#include <stdbool.h>
#include "image.h"
#include "matrice.h"
#include "animationperso.h"

#define BAS 1
#define HAUT 2
SDL_Texture* load_texture_from_image(char  *  file_image_name, SDL_Window *window, SDL_Renderer *renderer);

void play_with_texture_1_1(SDL_Texture *my_texture, SDL_Window *window,
                         SDL_Renderer *renderer);
void animation_run(SDL_Texture* my_texture,SDL_Texture* mure,SDL_Texture* fond,
                            SDL_Window* window,
                            SDL_Renderer* renderer,int i,int j,int ** matrice);
void animation_attack(SDL_Texture* my_texture,SDL_Texture* mure,SDL_Texture* fond,
                            SDL_Window* window,
                            SDL_Renderer* renderer,int i,int j,int ** matrice);

void animation_climb(SDL_Texture* my_texture,SDL_Texture* mure,SDL_Texture* fond,
                            SDL_Window* window,
                            SDL_Renderer* renderer,int i,int j,int ** matrice,int mouvement);
void animation_run_back(SDL_Texture* my_texture,SDL_Texture* mure,SDL_Texture* fond,
                            SDL_Window* window,
                            SDL_Renderer* renderer,int i,int j,int ** matrice);                                              
void afficher_perso(SDL_Texture* my_texture,SDL_Texture* mure,SDL_Texture* fond,
                            SDL_Window* window,
                            SDL_Renderer* renderer,int i,int j,int ** matrice);
void animation_attack_gauche(SDL_Texture* my_texture,SDL_Texture* mure,SDL_Texture* fond,
                            SDL_Window* window,
                            SDL_Renderer* renderer,int i,int j,int ** matrice) ;

#endif