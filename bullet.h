#pragma once
#include "texture.h"
#include "geometry.h"

#include <SDL2\SDL.h>
#include <SDL2\SDL_image.h>
#include <vector>
#include <algorithm>

class Bullet
{
private:
    static Texture bulletTexture;
    static int width, height;
    int dmg;
    int lastMovement;
    Point pos, pivot;
    double angle;
    static constexpr double speed = 300.0;

    bool outOfScreen();

public:
    bool isDestroyed;

    Bullet(double x, double y, double ang, Point _pivot, int _dmg);
    static bool loadImage(const char fileName[]);
    bool render() const;
    void applyPhysics();
    static double getW();
    static double getH();
    Point getPos() const;
    std::vector<Point> getPolygon() const;
    int getDmg() const;
};