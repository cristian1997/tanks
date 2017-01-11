#pragma once
#include "texture.h"
#include "geometry.h"

#include <SDL2\SDL.h>
#include <SDL2\SDL_image.h>
#include <vector>

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
    bool isDestroyed;

    Bullet(double x, double y, double ang, Point _pivot);
    static bool loadImage(const char fileName[]);
    bool render() const;
    void updatePos();
    static double getW();
    static double getH();
    std::vector<Point> getPolygon() const;
};