#include "Render.h"
#include "Init.h"
#include "Snake.h"
#include <SDL2/SDL_rect.h>

// Colors
SDL_Color White = {255, 255, 255};
SDL_Color Transparent = { 0, 0, 0, 80 };
// Background
SDL_Rect bgSrc = { 0, 0, 20, 20 };
SDL_Rect bgDest = { 0, 0, 20, 20 };

SDL_Texture *LoadTexture(const char *path, SDL_Renderer **ren){
    SDL_Surface *Loader = NULL;
    SDL_Texture *Tex = NULL;
    Loader = IMG_Load(path);
    Tex = SDL_CreateTextureFromSurface(*ren, Loader);
    SDL_FreeSurface(Loader);
    return Tex;
}

void drawBackground(SDL_Renderer **ren, SDL_Texture *tex){
    for (int i = 0; i <= (Width/2)/10; i++){
        for (int k = 0; k <= (Height/2)/10; k++){
            bgDest.x = i * 20;
            bgDest.y = k * 20;
            SDL_RenderCopy(*ren, tex, &bgSrc, &bgDest);
        }
    }
}

TTF_Font *LoadFont(const char *fontLocation, const int fontSize){
    TTF_Font *Font = TTF_OpenFont(fontLocation, fontSize);
    return Font;
}

SDL_Texture *LoadTextTexture(TTF_Font *Font, const char *Text, SDL_Rect *src, SDL_Renderer **ren){
    SDL_Surface *Loader = TTF_RenderText_Blended(Font, Text, White);
    SDL_Texture *Tex = SDL_CreateTextureFromSurface(*ren, Loader);

    src->w = Loader->w;
    src->h = Loader->h;

    SDL_FreeSurface(Loader);
    return Tex;
}

void drawText(SDL_Texture *tex, SDL_Rect src, SDL_Renderer **ren){
    SDL_RenderCopy(*ren, tex, NULL, &src);
}

