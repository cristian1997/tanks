#include "menu.h"
#include "gamedata.h"
#include "gameplay.h"

#include <SDL.h>
#include <SDL_image.h>
#include <vector>
#include <stdio.h>

bool init();
bool loadMedia();
void close();

Menu menu;
GamePlay gamePlay;
//Options options;

bool init()
{
    if (SDL_Init(SDL_INIT_VIDEO) < 0)
    {
        printf("SDL could not initialize! SDL_Error: %s\n", SDL_GetError());
        return false;
    }

    GD.window = SDL_CreateWindow("SDL Tutorial", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, GD.SCREEN_WIDTH, GD.SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
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

    return true;
}

bool loadMedia()
{
    if (!menu.loadMedia())
    {
        printf("Couldn't load menu media\n");
        return false;
    }

    if (!GD.playerText->loadFromFile("sprites/blue tank.png", GD.screenRenderer))
    {
        printf("Couldn't load tank\n");
        return false;
    }

    if (!Bullet::loadImage("sprites/bullet.png"))
    {
        printf("Unable to load image sprites/bullet.png! SDL Error: %s\n", SDL_GetError());
        return false;
    }

    return true;
}

void close()
{
    SDL_DestroyWindow(GD.window);
    GD.window = nullptr;

    SDL_Quit();
}

int main(int argc, char* args[])
{
    int frames;
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
            auto currentScene = GD.MENU;
            bool quit = false;
            do
            {
                switch (currentScene)
                {
                    case GD.MENU:
                        currentScene = menu.run();
                        break;
                    case GD.OPTIONS:
                        //currentScene = optiuni.run();
                        quit = true;
                        break;
                    case GD.GAMEPLAY:
					{
						GD.nrLevel = 0;
						currentScene = gamePlay.run();
						break;
					}
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
