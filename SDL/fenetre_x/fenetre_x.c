#include"fenetre_x.h"

/************************************/
          /*  fenetre_x  */
/************************************/

/* Cette fonction calcul la largeur et la hauteur de l'ecran 
Entree :
    Tableau a 2 cases , la premiere pour la largeur et la deuuxieme pour la hauteur
Sortie : 
    Void 
*/
void   largeur_hauteur(int*l_h){
    int i;

    SDL_DisplayMode current;

    for(i = 0; i < SDL_GetNumVideoDisplays(); ++i){

      int should_be_zero = SDL_GetCurrentDisplayMode(i, &current);

      if(should_be_zero != 0)
        // en cas d'erreur
        SDL_Log("Could not get display mode for video display #%d: %s", i, SDL_GetError());

      else
        // en cas de succes
        l_h[0]=current.w;
        l_h[1]=current.h;

    }
    // sortie du programme
    SDL_Quit();
}
int main(int argc, char **argv) {
  (void)argc;
  (void)argv; 
  int nb_fenetres =50; // choix du nombre de fenetre a afficher 
  SDL_Window **window = (SDL_Window **) malloc(nb_fenetres*sizeof(SDL_Window*));         

  /* Initialisation de la SDL  + gestion de l'échec possible */
  if (SDL_Init(SDL_INIT_VIDEO) != 0) {
    SDL_Log("Error : SDL initialisation - %s\n", SDL_GetError());      // l'initialisation de la SDL a échoué 
    exit(EXIT_FAILURE);
  }
  int *l=malloc(2*sizeof(int));
  largeur_hauteur(l);
  int weidth =l[0];
  int heith = l[1];
  /* Création des premieres fenetres descendantes*/
  int i =0 ;
  for ( i = 0; i < nb_fenetres; i++)
  {
        /* Création de la fenêtre  */
        window[i] = SDL_CreateWindow(
            "Fenêtre ",                    // codage en utf8, donc accents possibles
            i*(weidth/nb_fenetres),i*(heith/nb_fenetres),                                  
            100, 100,                              // largeur = 100, hauteur = 100
            SDL_WINDOW_RESIZABLE);                 // redimensionnable

        if (window[i] == NULL) {
            SDL_Log("Error : SDL window 1 creation - %s\n", SDL_GetError());   // échec de la création de la fenêtre
            SDL_Quit();
            exit(EXIT_FAILURE);
        }

  }
  for ( i = nb_fenetres; i >0; i--)
  {
        /* Création de la fenêtre  */
        window[i] = SDL_CreateWindow(
            "Fenêtre ",                    // codage en utf8, donc accents possibles
            i*(weidth/nb_fenetres),heith-i*(heith/nb_fenetres),                                  
            100, 100,                              // largeur = 100, hauteur = 100
            SDL_WINDOW_RESIZABLE);                 // redimensionnable

        if (window[i] == NULL) {
            SDL_Log("Error : SDL window 1 creation - %s\n", SDL_GetError());   // échec de la création de la fenêtre
            SDL_Quit();
            exit(EXIT_FAILURE);
        }

  }
  

  SDL_Delay(2000);                           // Pause exprimée  en ms



  SDL_Quit();
  return 0;
}