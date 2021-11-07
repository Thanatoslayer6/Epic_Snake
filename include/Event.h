#pragma once
#include "SDL2/SDL_events.h"
#include "SDL2/SDL_timer.h"
#include "stdbool.h"
#include "stdio.h"

void EventLoop(SDL_Event *e);
void LimitFPS(Uint32 start_time, int FPS);
bool getProgramRunning();
bool getUserLost();
bool getOnMainMenu();
void setOnMainMenu(bool setstate);
void setProgramRunning(bool setstate);
void setUserLost(bool setstate);
SDL_Event * getProgramEvent();



