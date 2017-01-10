#pragma once
#include "geometry.h"
#include "gamedata.h"

#include <SDL2/SDL_image.h>

class Texture
{
private:
    SDL_Texture *texture;
    int width, height;

public:
    Texture() { texture = nullptr; }
    bool loadFromFile(const char fileName[]);
    bool render(Point pos, double angle, const Point *pivot = nullptr) const;
    int getW() const;
    int getH() const;
    ~Texture();
};
