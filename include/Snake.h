#pragma once
#include "SDL2/SDL_events.h"
#include "SDL2/SDL_render.h"
#include "SDL2/SDL_mixer.h"
#include "stdbool.h"
typedef struct {
    int x, y;
} Segment;

void SnakeInput(SDL_Event *e);
int GetScore();
char *GetScoreText();
bool SnakeLogic(Mix_Chunk *bite, Mix_Chunk *lose);
void DrawSnake(SDL_Renderer **ren, SDL_Texture *head, SDL_Texture *body);
void SnakeInit();
void SnakeDestroy();
void SetScore(int z);
