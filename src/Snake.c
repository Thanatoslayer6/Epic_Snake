#include "Snake.h"
#include "Event.h"
#include "Food.h"
#include "Init.h"
#include "SDL2/SDL_events.h"
#include "SDL2/SDL_mixer.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Snake src and dest
SDL_Rect snkDest = { 0, 0, 20, 20 };
SDL_Rect snkSrc = { 0, 0, 20, 20 };

Segment Snake[1000];

// Important variables
static int dx, dy, snakeLength = 3;
static char currDir;
static bool userStarted = false;
static char Points[32];

int GetScore(){
    return (snakeLength - 3);
}

char *GetScoreText(){
    sprintf(Points, "Score: %d", (snakeLength - 3));
    return Points;
}

void SetScore(int z){
    snakeLength = z;
}

// Snake starting position
void SnakeInit(){
    Snake[0].x = Width/2 - 20, Snake[0].y = Height/2 - 20;
    Snake[1].x = Width/2 - 40, Snake[1].y = Height/2 - 20;
    Snake[2].x = Width/2 - 60, Snake[2].y = Height/2 - 20;
}

void SnakeDestroy(){
    dx = 0;
    dy = 0;
    currDir = 0;
    userStarted = false;
    for (int i = 0; i < sizeof(Snake)/8; i++){
        Snake[i].x = 0;
        Snake[i].y = 0;
    }
}

void DrawSnake(SDL_Renderer **ren, SDL_Texture *head, SDL_Texture *body){
    for (int i = 0; i < sizeof(Snake)/8; i++){
        snkDest.x = Snake[i].x;
        snkDest.y = Snake[i].y;
        if (i == 0){ // Head
            SDL_RenderCopy(*ren, head, &snkSrc, &snkDest);
        } else if (Snake[i].x == 0 && Snake[i].y == 0) {
            continue;
        } else { // Body
            SDL_RenderCopy(*ren, body, &snkSrc, &snkDest);
        }
    }
}

bool SnakeLogic(Mix_Chunk *bite, Mix_Chunk *lose){
    if (userStarted){
        for (int i = snakeLength - 1; i > 0; i--){
            while(Snake[i].x == GetFoodCoordinates().x && Snake[i].y == GetFoodCoordinates().y) {
                GenFoodLocation();
                break;
            }
            if (Snake[0].x == Snake[i].x && Snake[0].y == Snake[i].y){
                Mix_PlayChannel(-1, lose, 0);
                return false;
            }
            // Make sure tail follows the head
            Snake[i].x = Snake[i - 1].x;
            Snake[i].y = Snake[i - 1].y;
        }
    }

    // If snake eats the food
    if (Snake[0].x == GetFoodCoordinates().x && Snake[0].y == GetFoodCoordinates().y){
        GenFoodLocation();
        Mix_PlayChannel(-1, bite, 0);
        snakeLength++;
    }
    // If snake goes over the boundary
    if(Snake[0].x + 20 > Width || Snake[0].x < 0 || Snake[0].y + 20 > Height || Snake[0].y < 0){
        Mix_PlayChannel(-1, lose, 0);
        return false;
    }

    // Always add dx and dy to head
    Snake[0].x += dx;
    Snake[0].y += dy;
    return true;
}

void SnakeInput(SDL_Event *e, bool *pause){
    while(SDL_PollEvent(e)){
        if (*pause == false){
            switch(e->key.state){
                case 'a': case 'h':
                    if (currDir == 'r' || currDir == 0) break;
                    currDir = 'l';
                    dx = -20;
                    dy = 0;
                    break;
                case 'd': case 'l':
                    if (currDir == 'l') break;
                    currDir = 'r';
                    dx = 20;
                    dy = 0;
                    userStarted = true;
                    break;
                case 's': case 'j':
                    if (currDir == 'u') break;
                    currDir = 'd';
                    dx = 0;
                    dy = 20;
                    userStarted = true;
                    break;
                case 'w': case 'k':
                    if (currDir == 'd') break;
                    currDir = 'u';
                    dx = 0;
                    dy = -20;
                    userStarted = true;
                    break;
            }
        }
        // Pause
        if (*pause == false && e->key.state == 'p' && userStarted == true){
            *pause = true;
            break;
        }
        // Unpause
        if (*pause == true && e->key.state == 'p'){
            *pause = false;
            break;
        }
        // Exit the game
        if (*pause == true && e->key.state == 'x' ){
            setProgramRunning(false);
            break;
        }
    }
}
