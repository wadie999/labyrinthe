#include"rendu.h"

/*********************************************************************************************************************/
/*                              Programme d'exemple de création de rendu + dessin                                    */
/*********************************************************************************************************************/
//gcc  rendu.c -o prog -lSDL2 -lSDL2_gfx -lSDL2_image -lSDL2_ttf -lSDL2_mixer -lSDL2_net

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

            
void draw_rect(SDL_Renderer* renderer,int w0,int h0){
  SDL_Rect rectangle; 
  SDL_SetRenderDrawColor(renderer,                                
                            50, 0, 0,                               // mode Red, Green, Blue (tous dans 0..255)
                            255);
  rectangle.x = 0;                                                    // x haut gauche du rectangle
  rectangle.y = 0;                                                    // y haut gauche du rectangle
  rectangle.w = 100;                                                  // sa largeur (w = width)
  rectangle.h = 100;
  int i = 0;
  int signe_x = 1;
  int signe_y = 1;
  int r =255,g=0,b=0;               //rgb
  for(i=0;i<500;i++){
    SDL_SetRenderDrawColor(renderer,                                
                            r, g, b,                               // mode Red, Green, Blue (tous dans 0..255)
                            255);
    rectangle.x = rectangle.x +signe_x*10 ;                                                    // x haut gauche du rectangle
    rectangle.y = rectangle.y +signe_y*10;
    if(rectangle.x==0){
      r=255;
      g=165;
      b=0;
      
      signe_x = 1 ;
    }  
    if(rectangle.y==0){
      r=255;
      g=255;
      b=0;
      
      signe_y = 1 ;
    }
    if(rectangle.x== w0-100){
      r=0;
      g=128;
      b=0;
      
      signe_x = -1 ;
    }
    if(rectangle.y== h0-100){
      r=0;
      g=0;
      b=255;
      
      signe_y=-1;
    }                                               
    SDL_RenderFillRect(renderer, &rectangle);
    SDL_RenderPresent(renderer);                                        // affichage
    SDL_Delay(100);
    SDL_SetRenderDrawColor(renderer,255,255,255,255);
    SDL_RenderClear(renderer);
  }
}

int main(int argc, char** argv) {
  (void)argc;
  (void)argv;

  SDL_Window* window = NULL;
  SDL_Renderer* renderer = NULL;
  
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
                            SDL_WINDOWPOS_CENTERED, screen.w ,
                            screen.h ,
                            SDL_WINDOW_OPENGL);
  if (window == NULL) end_sdl(0, "ERROR WINDOW CREATION", window, renderer);
  
  /* Création du renderer */
  renderer = SDL_CreateRenderer(
           window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
  if (renderer == NULL) end_sdl(0, "ERROR RENDERER CREATION", window, renderer);

  /*********************************************************************************************************************/
  /*                                     On dessine dans le renderer                                                   */
                                                      // appel de la fonction qui crée l'image  
  int w;
  int h;
  SDL_GetWindowSize(window,&w,&h);

  
  draw_rect(renderer,w,h);

  SDL_RenderPresent(renderer);                                        // affichage
  SDL_Delay(5000);                                                    // Pause exprimée en ms

  /*********************************************************************************************************************/
  /* on referme proprement la SDL */
  end_sdl(1, "Normal ending", window, renderer);
  return EXIT_SUCCESS;
}
