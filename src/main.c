#include "Init.h"
#include "Event.h"
#include "Render.h"
#include "Snake.h"
#include "Food.h"
#include "Sound.h"
#include <SDL2/SDL_mixer.h>

SDL_Window *Window = NULL;
SDL_Renderer *Renderer = NULL;
// Score
SDL_Rect scrSrc = { 5, 5, 0, 0 };
// Gameover
SDL_Rect gmSrc = { (Width/2) - 130, (Height/2) - 100, 0, 0 };
SDL_Rect trySrc = { (Width/2) - 120, (Height/2), 0, 0 };
SDL_Rect gomenuSrc = { (Width/2) - 140, (Height/2) + 20, 0, 0 };
SDL_Rect quitSrc = { (Width/2) - 70, (Height/2) + 40, 0, 0 };
// Main Menu
SDL_Rect menuSrc = { (Width/2) - 180, (Height/2) - 100, 0, 0 };
SDL_Rect playSrc = { (Width/2) - 100, (Height/2) + 30, 0, 0 };
SDL_Rect exitSrc = { (Width/2) - 100, (Height/2) + 60, 0, 0 };

int main(int argc, char **argv){
    // Initialize a window and a renderer
    INIT("Epic Snake", Width, Height, &Window, &Renderer);
    INITMIXER();

    // Load resources
    TTF_Font *ScoreFont = LoadFont("res/ttf/m6x11.ttf", 16);
    TTF_Font *GameOverFont = LoadFont("res/ttf/AvenuePixelStroke-Regular.ttf", 100);
    TTF_Font *TryFont = LoadFont("res/ttf/AnonymiceNerd.ttf", 18);
    TTF_Font *MainMenuFont = LoadFont("res/ttf/AvenuePixelStroke-Regular.ttf", 120);
    TTF_Font *MainMenuFont_1 = LoadFont("res/ttf/m6x11.ttf", 24);
    SDL_Texture *Grass = LoadTexture("res/Grass.png", &Renderer);
    SDL_Texture *SnakeHead = LoadTexture("res/snakehead.png", &Renderer);
    SDL_Texture *SnakeBody = LoadTexture("res/snakebody.png", &Renderer);
    SDL_Texture *SnakeFood = LoadTexture("res/snakefood.png", &Renderer);
    SDL_Texture *GameOver_Text = LoadTextTexture(GameOverFont, "Game Over", &gmSrc, &Renderer);
    SDL_Texture *TryAgain_Text = LoadTextTexture(TryFont, "Press Space to try again", &trySrc, &Renderer);
    SDL_Texture *GoToMainMenu_Text = LoadTextTexture(TryFont, "Press ESC to go in Main Menu", &gomenuSrc, &Renderer);
    SDL_Texture *Quit_Text = LoadTextTexture(TryFont, "Press 'x' to quit", &quitSrc, &Renderer);
    SDL_Texture *MainMenu_Text = LoadTextTexture(MainMenuFont, "Epic Snake", &menuSrc, &Renderer);
    SDL_Texture *Play_Text = LoadTextTexture(MainMenuFont_1, "Press 'p' to play", &playSrc, &Renderer);
    SDL_Texture *Quit_Text_1 = LoadTextTexture(MainMenuFont_1, "Press 'x' to exit", &exitSrc, &Renderer);
    Mix_Music *BGM = LoadMusic("res/sfx/bgm.mp3");

    // Load Snake default values and some important variables
    SETUP();
    // Load music
    Mix_PlayMusic(BGM, -1);
    while(getProgramRunning()){
        Uint32 frameStart = SDL_GetTicks();
        // Input
        EventLoop(getProgramEvent());
        if (getOnMainMenu()){
            SDL_SetRenderDrawColor(Renderer, 50, 100, 50, 255);
            SDL_RenderClear(Renderer);
            drawText(MainMenu_Text, menuSrc, &Renderer);
            drawText(Play_Text, playSrc, &Renderer);
            drawText(Quit_Text_1, exitSrc, &Renderer);
        } else if (getUserLost()){
            drawText(GameOver_Text, gmSrc, &Renderer);
            drawText(TryAgain_Text, trySrc, &Renderer);
            drawText(GoToMainMenu_Text, gomenuSrc, &Renderer);
            drawText(Quit_Text, quitSrc, &Renderer);           
        } else {
            // Score
            char *Points;
            sprintf(Points, "Score: %d", GetScore());
            SDL_Texture *Score = LoadTextTexture(ScoreFont, Points, &scrSrc, &Renderer);

            // Draw 
            drawBackground(&Renderer, Grass);
            drawText(Score, scrSrc, &Renderer);
            DrawFood(&Renderer, SnakeFood);
            DrawSnake(&Renderer, SnakeHead, SnakeBody);

            // Logic
            SnakeInput(getProgramEvent());
            if (!SnakeLogic()){
                setUserLost(true);
            }
        }

        SDL_RenderPresent(Renderer);
        LimitFPS(frameStart, 15);
    }

    // Quit the program
    QUIT(&Window, &Renderer);
}
