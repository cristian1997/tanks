#pragma once
#include <SDL2/SDL_image.h>
#include "geometry.h"

class Texture
{
private:
    SDL_Texture *texture;
    int width, height;

public:
    Texture() { texture = nullptr; }
    bool loadFromFile(const char fileName[], SDL_Renderer *renderer);
    bool render(SDL_Renderer *&dest, Point pos, double angle, Point *pivot = nullptr);
    double getW();
    double getH();
    ~Texture();
};
