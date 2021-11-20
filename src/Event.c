#include "Event.h"
#include "Init.h"
#include "Snake.h"
#include <stdio.h>

static SDL_Event e;
static bool OnMainMenu = true;
static bool ProgramIsRunning = true;
static bool IsGameOver = false;

bool getProgramRunning(){
    return ProgramIsRunning;
}

bool getUserLost(){
    return IsGameOver;
}

bool getOnMainMenu(){
    return OnMainMenu;
}

void setUserLost(bool setstate){
    IsGameOver = setstate;
}

void setProgramRunning(bool setstate){
    ProgramIsRunning = setstate;
}

SDL_Event * getProgramEvent(){
    return &e;
}

void EventLoop(SDL_Event *ev){
    while(SDL_PollEvent(ev)){
        // Allow the option to quit at every part of the game just by pressing x
        if (ev->type == SDL_QUIT || ev->key.keysym.scancode == SDL_SCANCODE_X){
            printf("Exiting game...\n");
            ProgramIsRunning = false;
            break;
        }
        if (IsGameOver == false && OnMainMenu == true){
            if (ev->key.keysym.scancode == SDL_SCANCODE_P){
                printf("Playing the game\n");
                OnMainMenu = false;
                IsGameOver = false;
                break;
            }
        } else if (IsGameOver == true && OnMainMenu == false){
            if (ev->key.keysym.scancode == SDL_SCANCODE_SPACE){
                IsGameOver = false;
                SETUP();
                break;
            } else if (ev->key.keysym.scancode == SDL_SCANCODE_ESCAPE){
                IsGameOver = false;
                OnMainMenu = true;
                SETUP();
                break;
            }
        }
    }
}

void LimitFPS(Uint32 start_time, int FPS){
    if((1000/FPS)>(SDL_GetTicks()-start_time)){
        SDL_Delay((1000/FPS)-(SDL_GetTicks()-start_time));
    }
}
