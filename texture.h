#pragma once
#include <SDL2/SDL_image.h>

class Texture
{
private:
    SDL_Texture *texture;
    int width, height;

public:
    Texture() { texture = nullptr; }
    bool loadFromFile(const char fileName[], SDL_Renderer *renderer);
    bool render(SDL_Renderer *&dest, double xPos, double yPos, double angle);
    double getW();
    double getH();
    ~Texture();
};
