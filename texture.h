#pragma once
#include "geometry.h"

#include <SDL_image.h>

class Texture
{
private:
    SDL_Texture *texture;
    int width, height;

public:
    Texture() { texture = nullptr; }
    bool loadFromFile(const char fileName[], SDL_Renderer *renderer);
    bool render(SDL_Renderer *&dest, Point pos, double angle, const Point *pivot = nullptr) const;
    int getW() const;
    int getH() const;
    ~Texture();
};
