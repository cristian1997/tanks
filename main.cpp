#include "tank.h"
#include "bullet.h"
#include "geometry.h"
#include "gamedata.h"
#include <SDL2\SDL.h>
#include <SDL2\SDL_image.h>

#include <vector>
#include <stdio.h>


bool init();
bool loadMedia();
void close();

SDL_Window* window = nullptr;
SDL_Renderer* screenRenderer = nullptr;
Tank player;
std::vector<Bullet> bullets;

bool init()
{
    if (SDL_Init(SDL_INIT_VIDEO) < 0)
    {
        printf("SDL could not initialize! SDL_Error: %s\n", SDL_GetError());
        return false;
    }
    
    window = SDL_CreateWindow(
        "SDL Tutorial",
        SDL_WINDOWPOS_UNDEFINED,
        SDL_WINDOWPOS_UNDEFINED,
        GD.SCREEN_WIDTH,
        GD.SCREEN_HEIGHT,
        SDL_WINDOW_SHOWN
    );

    if (window == nullptr)
    {
        printf("Window could not be created! SDL_Error: %s\n", SDL_GetError());
        return false;
    }
    
    screenRenderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (screenRenderer == nullptr)
    {
        printf("Renderer could not be created! SDL_Error: %s\n", SDL_GetError());
    }

    return true;
}

bool loadMedia()
{
    if(!player.loadImage("sprites/blue tank.png", screenRenderer))
    {
        printf("Unable to load image sprites/blue tank.png! SDL Error: %s\n", SDL_GetError());
        return false;
    }

    if (!Bullet::loadImage("sprites/bullet.png", screenRenderer))
    {
        printf("Unable to load image sprites/bullet.png! SDL Error: %s\n", SDL_GetError());
        return false;
    }

    return true;
}

void close()
{
    SDL_DestroyWindow(window);
    window = nullptr;

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

            if(!player.render(screenRenderer))
                printf("Error rendering player\n");

            SDL_UpdateWindowSurface(window);

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
                    else if (e.type == SDL_KEYDOWN && e.key.keysym.sym == SDLK_SPACE)
                    {
                        if (!player.fire()) continue;

                        double x = player.getX() + player.getW() + 5.0;
                        double y = player.getY() + (player.getH() - Bullet::getH()) / 2.0;
                        double x0 = player.getX() + player.getW() / 2;
                        double y0 = player.getY() + player.getH() / 2;

                        Point ret = Geometry::rotatePoint(Point(x, y), Point(x0, y0), player.getAngle());
                        Bullet bullet(ret.x, ret.y, player.getAngle(), Point(0, 0));
                        bullets.push_back(bullet);
                    }
                    else player.handleEvent(e);
                }
                SDL_RenderClear(screenRenderer);
                player.updatePos();
                
                if (!player.render(screenRenderer))
                    printf("Error\n");

                for (auto b : bullets)
                {
                    b.updatePos();
                    if (!b.render(screenRenderer))
                    {
                        printf("Error rendering bullet\n");
                        printf("%s\n", SDL_GetError());
                    }
                }

                SDL_RenderPresent(screenRenderer);

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

    /*

    auto currentScene = GD.MENU;
    bool quit = false;

    do
    {
        switch(currentScene)
        {
            case GD.MENU:
                currentScene = Menu.run();
                break;
            case GD.OPTIONS:
                currentScene = Options.run();
                break;
            case GD.GAMEPLAY:
                currentScene = Gameplay.run();
                break;
            case GD.QUIT:
                quit = true;
                break;
        }
    } while(!quit);

    */

    close();

    return 0;
}
