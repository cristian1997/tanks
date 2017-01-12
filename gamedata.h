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

    const int INF = 1000000000;

    int nrLevel = 0;

    enum Scene
    {
        NONE,
        MENU,
        GAMEPLAY,
        MAPSELECTION,
        OPTIONS,
        QUIT
    };

    static const int nrPowerUps = 6;
    enum PowerUps
    {
        HP,
        FIRE_RATE,
        DMG,
        SPEED,
        BEER,
        ONE_SHOT
    };

    SDL_Window *window = nullptr;
    SDL_Renderer *screenRenderer = nullptr;
    TTF_Font *font = nullptr;

    static const int nrMaxTanks = 4;

    const int nrMaps = 2;

    SDL_Color colors[nrMaxTanks] = {{255, 0, 0}, {0, 255, 0}};

    Texture *playerText;
    std::vector<Texture> mapTextures;
    std::vector<Texture> powerUpTextures;
    std::map<std::string, decltype(SDLK_0)> keys[nrMaxTanks];
    std::vector<Point> obstacles;

    bool loadMedia();
};

extern GameData GD;
extern double constexpr PI = M_PI;