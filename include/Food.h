#pragma once
#include "SDL2/SDL_render.h"
#include "SDL2/SDL_rect.h"
#include "stdlib.h"
#include "time.h"

void FoodLogic();
void DrawFood(SDL_Renderer **ren, SDL_Texture *food);
void GenFoodLocation();
SDL_Rect GetFoodCoordinates();
