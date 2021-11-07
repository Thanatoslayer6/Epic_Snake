#include "Food.h"
#include "Snake.h"
#include <stdio.h>
#include <stdlib.h>

SDL_Rect FoodSrc = { 0, 0, 20, 20 };
SDL_Rect FoodDst = { 0, 0, 20, 20 };

void DrawFood(SDL_Renderer **ren, SDL_Texture *food){
    SDL_RenderCopy(*ren, food, &FoodSrc, &FoodDst);
}

void GenFoodLocation(){
    srand((unsigned)time(0));
    FoodDst.x = (rand() % 32) * 20;
    FoodDst.y = (rand() % 24) * 20;
}

SDL_Rect GetFoodCoordinates(){
    return FoodDst;
}
