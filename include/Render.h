#pragma once
#include "SDL2/SDL_render.h"
#include "SDL2/SDL_image.h"
#include <SDL2/SDL_pixels.h>
#include <SDL2/SDL_ttf.h>
#include <stdio.h>
#include <string.h>

SDL_Texture *LoadTexture(const char *path, SDL_Renderer **ren);
SDL_Texture *LoadTextTexture(TTF_Font *Font, const char *Text, SDL_Rect *src, SDL_Renderer **ren);
TTF_Font *LoadFont(const char *fontLocation, const int fontSize);
void drawBackground(SDL_Renderer **ren, SDL_Texture *tex);
void drawText(SDL_Texture *tex, SDL_Rect src, SDL_Renderer **ren);

