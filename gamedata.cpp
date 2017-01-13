#include "gamedata.h"

GameData::GameData()
{
    keys[0][std::string("up")] = SDLK_UP;
    keys[0][std::string("down")] = SDLK_DOWN;
    keys[0][std::string("left")] = SDLK_LEFT;
    keys[0][std::string("right")] = SDLK_RIGHT;
    keys[0][std::string("fire")] = SDLK_k;

    keys[1][std::string("up")] = SDLK_w;
    keys[1][std::string("down")] = SDLK_s;
    keys[1][std::string("left")] = SDLK_a;
    keys[1][std::string("right")] = SDLK_d;
    keys[1][std::string("fire")] = SDLK_SPACE;
}

bool GameData::loadMedia()
{
    std::string s;

    tankTextures.resize(nrTankTextures);
    for (int i = 0; i < nrTankTextures; ++i)
    {
        s = std::string("sprites/tank") + std::to_string(i) + std::string(".png");
        if (!tankTextures[i].loadFromFile(s.c_str(), screenRenderer))
        {
            return false;
        }
    }

    powerUpTextures.resize(nrPowerUps);
    for (int i = 0; i < nrPowerUps; ++i)
    {
        s = std::string("sprites/powerup") + std::to_string(i) + std::string(".png");
        if (!powerUpTextures[i].loadFromFile(s.c_str(), screenRenderer))
        {
            return false;
        }
    }

    mapTextures.resize(nrMaps);

    for (int i = 0; i < nrMaps; ++i)
    {
        s = std::string("sprites/defaultmap") + std::to_string(i) + std::string(".jpg");
        if (!mapTextures[i].loadFromFile(s.c_str(), screenRenderer))
        {
            return false;
        }
    }

    bulletHit = Mix_LoadWAV("sounds/hit.wav");
    if (bulletHit == nullptr)
    {
        printf("Failed to load scratch sound effect! SDL_mixer Error: %s\n", Mix_GetError());
        return false;
    }

    fire = Mix_LoadWAV("sounds/fire.wav");
    if (bulletHit == nullptr)
    {
        printf("Failed to load scratch sound effect! SDL_mixer Error: %s\n", Mix_GetError());
        return false;
    }

    mine = Mix_LoadWAV("sounds/mine.wav");
    if (bulletHit == nullptr)
    {
        printf("Failed to load scratch sound effect! SDL_mixer Error: %s\n", Mix_GetError());
        return false;
    }

    return true;
}

GameData GD;