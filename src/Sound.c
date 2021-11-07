#include "Sound.h"
#include <SDL2/SDL_mixer.h>
#include <stdio.h>

void INITMIXER(){
    if(Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, MIX_DEFAULT_CHANNELS, 2048) < 0){
        printf("Error initializing mixer!\n");
    }
}

Mix_Music *LoadMusic(const char *FileLocation){
    return Mix_LoadMUS(FileLocation);
}

Mix_Chunk *LoadSFX(const char *FileLocation){
    return Mix_LoadWAV(FileLocation);
}
