#pragma once

#include "texture.h"

#include <SDL2/SDL.h>
#include <map>
#include <vector>
#include <string>

class GameData
{
public:
    GameData();

    static const int SCREEN_WIDTH = 800;
    static const int SCREEN_HEIGHT = 600;

    static const int SPRITE_WIDTH = 25;
    static const int SPRITE_HEIGHT = 25;

    int nrLevel;
    bool mapTextureTypeVector[SCREEN_HEIGHT / SPRITE_HEIGHT][SCREEN_WIDTH / SPRITE_WIDTH];

    enum Scene
    {
        MENU,
        GAMEPLAY,
        OPTIONS,
        QUIT
    };

    static const int nrPowerUps = 3;
    enum PowerUps
    {
        HP,
        FIRE_RATE,
        DMG
    };

    SDL_Window *window = nullptr;
    SDL_Renderer *screenRenderer = nullptr;
    TTF_Font *font = nullptr;

    static const int nrMaxTanks = 4;

    SDL_Color colors[nrMaxTanks] = {{255, 0, 0}, {0, 255, 0}};

    Texture *playerText;
    std::vector<Texture> powerUpTextures;
    std::map<std::string, decltype(SDLK_0)> keys[nrMaxTanks];

    bool loadMedia();
};

extern GameData GD;
extern double constexpr PI = M_PI;