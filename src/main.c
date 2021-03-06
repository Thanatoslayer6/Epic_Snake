#include "Init.h"
#include "Event.h"
#include "Render.h"
#include "Snake.h"
#include "Food.h"
#include "Sound.h"

SDL_Window *Window = NULL;
SDL_Renderer *Renderer = NULL;

// Score
int temp = 0;
SDL_Rect scrSrc = { 5, 5, 0, 0 };
// Gameover
SDL_Rect gmSrc = { (Width/2) - 130, (Height/2) - 100, 0, 0 };
SDL_Rect trySrc = { (Width/2) - 120, (Height/2), 0, 0 };
SDL_Rect gomenuSrc = { (Width/2) - 140, (Height/2) + 20, 0, 0 };
SDL_Rect quitSrc = { (Width/2) - 70, (Height/2) + 40, 0, 0 };
// Pause
SDL_Rect unpauseSrc = { (Width/2) - 100, (Height/2) + 100, 0, 0 };
SDL_Rect pauseSrc = { (Width/2) - 165, (Height/2) - 100, 0, 0 };
// Main Menu
SDL_Rect menuSrc = { (Width/2) - 180, (Height/2) - 100, 0, 0 };
SDL_Rect playSrc = { (Width/2) - 100, (Height/2) + 30, 0, 0 };
SDL_Rect exitSrc = { (Width/2) - 100, (Height/2) + 60, 0, 0 };

static bool paused = false;

int main(int argc, char **argv){
    // Initialize a window and a renderer
    INIT("Epic Snake", Width, Height, &Window, &Renderer);
    // Initialize audio and sound effects
    INITMIXER();

    // Load resources
    TTF_Font *ScoreFont = LoadFont("res/ttf/m6x11.ttf", 16);
    TTF_Font *GameOverFont = LoadFont("res/ttf/AvenuePixelStroke-Regular.ttf", 100);
    TTF_Font *TryFont = LoadFont("res/ttf/AnonymiceNerd.ttf", 18);
    TTF_Font *MainMenuFont = LoadFont("res/ttf/AvenuePixelStroke-Regular.ttf", 120);
    TTF_Font *MainMenuFont_1 = LoadFont("res/ttf/m6x11.ttf", 24);
    SDL_Texture *Score = NULL;
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
    SDL_Texture *Pause_Text = LoadTextTexture(GameOverFont, "Game Paused", &pauseSrc, &Renderer);
    SDL_Texture *Unpause_Text = LoadTextTexture(TryFont, "Press 'p' to unpause", &unpauseSrc, &Renderer);
    Mix_Music *BGM = LoadMusic("res/sfx/bgm.mp3");
    Mix_Chunk *Lose = LoadSFX("res/sfx/lose.wav");
    Mix_Chunk *Bite = LoadSFX("res/sfx/bite.wav");

    // Load Snake default values and some important variables
    SETUP();
    // Load music
    Mix_PlayMusic(BGM, -1);
    while(getProgramRunning()){
        Uint32 frameStart = SDL_GetTicks();
        if (getOnMainMenu()){ // On main menu
            EventLoop(getProgramEvent()); // Input
            SDL_SetRenderDrawColor(Renderer, 50, 100, 50, 255);
            SDL_RenderClear(Renderer);
            drawText(MainMenu_Text, menuSrc, &Renderer);
            drawText(Play_Text, playSrc, &Renderer);
            drawText(Quit_Text_1, exitSrc, &Renderer);
        } else if (getUserLost()){ // If user looses
            EventLoop(getProgramEvent()); // Input
            drawText(GameOver_Text, gmSrc, &Renderer);
            drawText(TryAgain_Text, trySrc, &Renderer);
            drawText(GoToMainMenu_Text, gomenuSrc, &Renderer);
            drawText(Quit_Text, quitSrc, &Renderer);
        } else { // Game is running
            SnakeInput(getProgramEvent(), &paused); // Input

            // Score handler if score resets create texture
            if (temp == 0 && Score == NULL){
                Score = LoadTextTexture(ScoreFont, GetScoreText(), &scrSrc, &Renderer);
            }
            // If snake eats food, update new texture by destroying and creating again
            if (temp < GetScore() && Score != NULL){
                SDL_DestroyTexture(Score);
                Score = NULL;
                Score = LoadTextTexture(ScoreFont, GetScoreText(), &scrSrc, &Renderer);
                temp++;
            }

            if (paused == false) { // If game is playing
                // Draw
                drawBackground(&Renderer, Grass);
                drawText(Score, scrSrc, &Renderer);
                DrawFood(&Renderer, SnakeFood);
                DrawSnake(&Renderer, SnakeHead, SnakeBody);

                // Logic
                if (!SnakeLogic(Bite, Lose)){
                    // Reset score and destroy texture
                    temp = 0;
                    SDL_DestroyTexture(Score);
                    Score = NULL;
                    setUserLost(true);
                }
            } else { // If game is paused...
                drawText(Pause_Text, pauseSrc, &Renderer);
                drawText(Unpause_Text, unpauseSrc, &Renderer);
                drawText(GoToMainMenu_Text, gomenuSrc, &Renderer);
                drawText(Quit_Text, quitSrc, &Renderer);
            }
        
        }

        SDL_RenderPresent(Renderer);
        LimitFPS(frameStart, 15);
    }

    // Quit the program
    QUIT(&Window, &Renderer);
    return 0;
}
