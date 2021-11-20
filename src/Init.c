#include "Init.h"
#include "Food.h"
#include "Snake.h"

void INIT(const char *title, int width, int height, SDL_Window **Window, SDL_Renderer **Renderer){
    // Initialize sdl, img, and ttf
    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) != 0){
        printf("Error SDL_Init\n");
    }
    if (IMG_Init(IMG_INIT_PNG) == 0){
        printf("Error IMG_Init\n");
    }
    if (TTF_Init() != 0 ){
        printf("Error TTF_Init\n");
    }
    // Create window and renderer
    *Window = SDL_CreateWindow(title, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, SDL_WINDOW_OPENGL);
    if (Window == NULL){
        printf ("Error Creating window...\n");
    }

    *Renderer = SDL_CreateRenderer(*Window, -1, SDL_RENDERER_ACCELERATED);
    if (Renderer == NULL){
        printf("Error creating renderer...\n");
    }
}

void SETUP(){
    GenFoodLocation();
    SetScore(3);
    SnakeDestroy();
    SnakeInit();
}

void QUIT(SDL_Window **Window, SDL_Renderer **Renderer){
    SDL_DestroyWindow(*Window);
    SDL_DestroyRenderer(*Renderer);
    IMG_Quit();
    TTF_Quit();
    Mix_Quit();
    SDL_Quit();
}


