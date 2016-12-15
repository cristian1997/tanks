#include "tank.h"
#include <SDL2\SDL.h>
#include <SDL2\SDL_image.h>

#include <stdio.h>

const int SCREEN_HEIGHT = 480;
const int SCREEN_WIDTH = 640;

bool init();
bool loadMedia();
void close();

SDL_Window* gWindow = nullptr;
SDL_Surface* gScreenSurface = nullptr;
tank player;

bool init()
{
    if (SDL_Init(SDL_INIT_VIDEO) < 0)
    {
        printf("SDL could not initialize! SDL_Error: %s\n", SDL_GetError());
        return false;
    }
    
    gWindow = SDL_CreateWindow("SDL Tutorial", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
    if (gWindow == nullptr)
    {
        printf("Window could not be created! SDL_Error: %s\n", SDL_GetError());
        return false;
    }
    
    gScreenSurface = SDL_GetWindowSurface(gWindow);
    if (gScreenSurface == nullptr)
    {
        printf("Surface could not be created! SDL_Error: %s\n", SDL_GetError());
    }

    return true;
}

bool loadMedia()
{
    if(!player.loadImage("sprites/blue tank.png"))
    {
        printf("Unable to load image sprites/blue tank.png! SDL Error: %s\n", SDL_GetError());
        return false;
    }

    return true;
}

void close()
{
    SDL_DestroyWindow(gWindow);
    gWindow = nullptr;

    SDL_Quit();
}

int main(int argc, char* args[])
{
    int frames;

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
            player.setPos(10, 10);

            if(!player.render(gScreenSurface))
                printf("Error\n");

            SDL_UpdateWindowSurface(gWindow);

            bool quit = false;
            SDL_Event e;
            frames = 0;
            int start = SDL_GetTicks();

            while (!quit)
            {
                if (SDL_PollEvent(&e))
                {
                    if (e.type == SDL_QUIT)
                    {
                        quit = true;
                    }
                    else player.handleEvent(e);
                }

                player.updatePos();
                if (player.hasMoved())
                {
                    if (!player.render(gScreenSurface))
                        printf("Error\n");

                    SDL_UpdateWindowSurface(gWindow);
                }

                ++frames;

                if (SDL_GetTicks() - start >= 1000)
                {
                    printf("%d\n", frames);
                    frames = 0;
                    start = SDL_GetTicks();
                }
            }
        }
    }

    close();

    return 0;
}
