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

    const int XDIM = SCREEN_WIDTH / SPRITE_WIDTH;
    const int YDIM = SCREEN_HEIGHT / SPRITE_HEIGHT;

    const int INF = 1000000000;

    int nrLevel = 0;
    int gameMode;

    enum Scene
    {
        NONE,
        MENU,
        GAMEPLAY,
        GAMEMODESELECTION,
        MAPSELECTION,
        QUIT
    };

    static const int nrPowerUps = 8;
    enum PowerUps
    {
        HP = 4,
        FIRE_RATE = 5,
        DMG = 6,
        SPEED = 7,
        BEER = 8,
        ONE_SHOT = 9,
        REVERSE = 10,
        BOMB = 11
    };

    SDL_Window *window = nullptr;
    SDL_Renderer *screenRenderer = nullptr;
    TTF_Font *font = nullptr;

    const int nrTankTextures = 3;
    static const int nrMaxTanks = 4;

    const int nrMaps = 4;

    SDL_Color colors[nrMaxTanks] = {{255, 0, 0}, {0, 255, 0}};

    std::vector<Texture> mapTextures, powerUpTextures, tankTextures;
    std::map<std::string, decltype(SDLK_0)> keys[nrMaxTanks];

    bool loadMedia();
};

extern GameData GD;
extern double constexpr PI = M_PI;