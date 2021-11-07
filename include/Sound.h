#pragma once
#include "SDL2/SDL_mixer.h"
void INITMIXER();
Mix_Music *LoadMusic(const char *FileLocation);
Mix_Chunk *LoadSFX(const char *FileLocation);

