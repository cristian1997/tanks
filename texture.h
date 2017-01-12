#pragma once
#include "geometry.h"

#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <string>

class Texture
{
private:
    SDL_Texture *texture;
    int width, height;

public:
    Texture() { texture = nullptr; }
    bool loadFromFile(const char fileName[], SDL_Renderer *renderer);
    bool loadFromText(const std::string text, SDL_Renderer *renderer, TTF_Font *font, SDL_Color &color);
    bool render(SDL_Renderer *&dest, Point pos, double angle, const Point *pivot = nullptr) const;
    bool render(SDL_Renderer *&dest, const SDL_Rect &rect) const;
    int getW() const;
    int getH() const;
    ~Texture();
};
