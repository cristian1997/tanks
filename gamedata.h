#pragma once

#include "texture.h"

#include <SDL2/SDL.h>
#include <map>

class GameData
{
public:
    GameData();

    const int SCREEN_WIDTH = 800;
    const int SCREEN_HEIGHT = 600;

    static const int nrMaxTanks = 4;

    enum Scene
    {
        MENU,
        GAMEPLAY,
        OPTIONS,
        QUIT
    };

    SDL_Window *window = nullptr;
    SDL_Renderer *screenRenderer = nullptr;

    int nrTanks;

    Texture *playerText;
    std::map<std::string, decltype(SDLK_0)> keys[nrMaxTanks];
};

extern GameData GD;
extern double constexpr PI = M_PI;