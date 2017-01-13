#include "menu.h"
#include "gamedata.h"
#include "gameplay.h"
#include "mapselection.h"
#include "gamemodeselection.h"

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_mixer.h>
#include <vector>

bool init();
bool loadMedia();
void close();

Menu menu;
GamePlay gamePlay;
MapSelection mapSelection;
GameModeSelection gameModeSelection;
Mix_Music *music = nullptr;


bool init()
{
    if (SDL_Init(SDL_INIT_VIDEO) < 0)
    {
        printf("SDL could not initialize! SDL_Error: %s\n", SDL_GetError());
        return false;
    }

    GD.window = SDL_CreateWindow("Tanks", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, GD.SCREEN_WIDTH, GD.SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
    if (GD.window == nullptr)
    {
        printf("Window could not be created! SDL_Error: %s\n", SDL_GetError());
        return false;
    }

    GD.screenRenderer = SDL_CreateRenderer(GD.window, -1, SDL_RENDERER_ACCELERATED);
    if (GD.screenRenderer == nullptr)
    {
        printf("Renderer could not be created! SDL_Error: %s\n", SDL_GetError());
    }

    if (TTF_Init() == -1)
    {
        printf("SDL_ttf could not initialize! SDL_ttf Error: %s\n", TTF_GetError());
        return false;
    }

    if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0)
    {
        printf("SDL_mixer could not initialize! SDL_mixer Error: %s\n", Mix_GetError());
        return false;
    }

    return true;
}

bool loadMedia()
{
    if (!menu.loadMedia())
    {
        printf("Couldn't load menu media\n");
        return false;
    }

    if (!Bullet::loadImage("sprites/bullet.png"))
    {
        printf("Unable to load image sprites/bullet.png! SDL Error: %s\n", SDL_GetError());
        return false;
    }

    if (!GD.loadMedia())
    {
        printf("Unable to load media for gamedata! %s\n", SDL_GetError());
        return false;
    }

    GD.font = TTF_OpenFont("fonts/font.ttf", 28);
    if (GD.font == NULL)
    {
        printf("Failed to load lazy font! SDL_ttf Error: %s\n", TTF_GetError());
        return false;
    }

    if (!mapSelection.loadMedia())
    {
        printf("Couldn't load map selection media\n%s\n", SDL_GetError());
        return false;
    }

    if (!gameModeSelection.loadMedia())
    {
        printf("Couldn't load map selection media\n%s\n", SDL_GetError());
        return false;
    }

    music = Mix_LoadMUS("sounds/menu.mp3");
    if (music == nullptr)
    {
        printf("Failed to load beat music! SDL_mixer Error: %s\n", Mix_GetError());
        return false;
    }

    return true;
}

void close()
{
    SDL_DestroyWindow(GD.window);
    GD.window = nullptr;

    SDL_DestroyRenderer(GD.screenRenderer);
    GD.screenRenderer = nullptr;

    Mix_FreeMusic(music);

    SDL_Quit();
}

int main(int argc, char* args[])
{
    int currentScene = 4;
    bool quit = 1;


    if (!init())
    {
        printf("Failed to initialize!\n");
    }
    else
    {
        if (!loadMedia())
        {
            printf("Failed to load media!\n");
        }
        else
        {
            Mix_PlayMusic(music, -1);

            auto currentScene = GD.MENU;
            bool quit = false;
            do
            {
                switch (currentScene)
                {
                    case GD.MENU:
                        currentScene = menu.run();
                        break;
                    case GD.MAPSELECTION:
                        currentScene = mapSelection.run();
                        break;
                    case GD.GAMEMODESELECTION:
                        currentScene = gameModeSelection.run();
                        break;
                    case GD.GAMEPLAY:
                        currentScene = gamePlay.run();
                        break;
                    case GD.QUIT:
                        quit = true;
                        break;
                }
            } while (!quit);
        }
    }

    close();

    return 0;
}
