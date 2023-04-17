#include <stdio.h>
#include <stdlib.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

void ErrorExit(const char* message)
{
    SDL_Log("ERREUR : %s - %s\n", message, SDL_GetError());
    SDL_Quit();
    exit(EXIT_FAILURE);
}

int main(int argc, char** argv)
{
    SDL_Window* fenetre = NULL;
    SDL_Renderer* rendu = NULL;
    SDL_Surface* image = NULL;
    SDL_Texture* texture = NULL;
    SDL_Texture* background = NULL;
    int fini = 0;
    //SDL_Rect sauv;

    int code = 0, on = 1;

    if (SDL_Init(SDL_INIT_VIDEO) != 0) ErrorExit("Initialisation");

    fenetre = SDL_CreateWindow("Animation", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 1920, 1080, SDL_WINDOW_OPENGL);

    if (fenetre == NULL) ErrorExit("Creation de la fenetre");

    rendu = SDL_CreateRenderer(fenetre, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);

    image = IMG_Load("Vulture_attack.png");

    if (image == NULL) ErrorExit("Chargement de l'image");

    texture = SDL_CreateTextureFromSurface(rendu, image);
    SDL_FreeSurface(image);

    if (texture == NULL) ErrorExit("Chargement de la texture");

    image = IMG_Load("house.jpg");

    if (image == NULL) ErrorExit("Chargement de l'image");

    background = SDL_CreateTextureFromSurface(rendu, image);
    SDL_FreeSurface(image);

    if (background == NULL) ErrorExit("Chargement de la texture");


    SDL_Rect source = {0}, fenetre_dimensions = {0}, destination = {0};
    SDL_Rect sourcefont = {0};

    SDL_GetWindowSize(fenetre, &fenetre_dimensions.w, &fenetre_dimensions.h); // recuperation des dimensions de la fenetre (stocké dans un rectangle fenetre_dimensions)               
    SDL_QueryTexture(texture, NULL, NULL, &source.w, &source.h); // recuperation des dimensions de la texture (stocké dans un rectangle source) 
    SDL_QueryTexture(background, NULL, NULL, &sourcefont.w, &sourcefont.h);

    destination.h = fenetre_dimensions.h/2;
    destination.w = fenetre_dimensions.w/5;
    destination.y = fenetre_dimensions.h/2 - destination.h/2;
    destination.x = fenetre_dimensions.w - destination.w + 400;
    int sau = source.w;
    source.w = source.w/4;

    while (!fini)
    {
        if (SDL_SetRenderDrawColor(rendu, 255, 255, 255, 255) != 0) ErrorExit("Changement de couleur echoue");
        SDL_RenderClear(rendu);

        SDL_RenderCopy(rendu, background, &sourcefont, &fenetre_dimensions);
        SDL_RenderCopy(rendu, texture, &source, &destination);
        SDL_RenderPresent(rendu);
        SDL_Delay(100);

        source.x = (source.x + source.w) % sau;

        if (destination.x < -400) destination.x = fenetre_dimensions.w - destination.w + 400;

        destination.x -= 100;
    }

    SDL_DestroyTexture(texture);
    SDL_DestroyRenderer(rendu);
    SDL_DestroyWindow(fenetre);
    SDL_Quit();
    return EXIT_SUCCESS;
}