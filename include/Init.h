#pragma once
#include <stdio.h>
#include "SDL2/SDL.h"
#include "SDL2/SDL_ttf.h"
#include "SDL2/SDL_image.h"
#include "SDL2/SDL_video.h"
#include "SDL2/SDL_render.h"
#include <SDL2/SDL_mixer.h>

#define Width 640
#define Height 480

void INIT(const char *title, int width, int height, SDL_Window **Window, SDL_Renderer **Renderer);
void SETUP();
void QUIT(SDL_Window **Window, SDL_Renderer **Renderer);
