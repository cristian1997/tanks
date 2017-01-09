#pragma once

#include "SDL2/SDL.h"

class GameData
{
public:
    const int SCREEN_WIDTH = 800;
    const int SCREEN_HEIGHT = 600;

    enum Scene
    {
        MENU,
        GAMEPLAY,
        OPTIONS,
        QUIT
    };

    SDL_Window *window = nullptr;
    SDL_Renderer *screenRenderer = nullptr;
};

extern GameData GD;
extern double constexpr PI = M_PI;