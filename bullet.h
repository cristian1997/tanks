#pragma once

#include <SDL2\SDL.h>
#include <SDL2\SDL_image.h>
#include "texture.h"
#include "geometry.h"

class Bullet
{
private:
    static Texture bulletTexture;
    static int width, height;
    int lastMovement;
    Point pos, pivot;
    double angle;
    static constexpr double speed = 200.0;

public:

    Bullet(double x, double y, double ang, Point _pivot);
    static bool loadImage(const char fileName[], SDL_Renderer *renderer);
    bool render(SDL_Renderer *&dest);
    void updatePos();
    static double getW();
    static double getH();

    ~Bullet();
};