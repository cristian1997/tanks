#pragma once

#include "texture.h"

#include <SDL.h>
#include <map>

class GameData
{
public:
    GameData();

    const int SCREEN_WIDTH = 800;
    const int SCREEN_HEIGHT = 600;

	int GDtextureTypeVector[16] = { 0,1,2,4,5,6,7,8,9,10,11,12,13,14,15 };
	int mapTextureTypeVector[(800 / 25)*(600 / 25)];
	int nrLevel;

    const int nrMaxTanks = 4;

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
    std::map<std::string, decltype(SDLK_0)> keys[4];
};

extern GameData GD;
extern double constexpr PI = M_PI;