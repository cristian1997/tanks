#include "bullet.h"
#include "gamedata.h"
#include <iostream>

Texture Bullet::bulletTexture;
int Bullet::width, Bullet::height;

bool Bullet::outOfScreen()
{
    double xmin = GD.SCREEN_WIDTH, xmax = -1, ymin = GD.SCREEN_HEIGHT, ymax = -1;

    for (const auto p : getPolygon())
    {
        xmin = std::min(xmin, p.x);
        xmax = std::max(xmax, p.x);
        ymin = std::min(ymin, p.y);
        ymax = std::max(ymax, p.y);
    }

    return xmax < 0 || xmin >= GD.SCREEN_WIDTH || ymax < 0 || ymin >= GD.SCREEN_HEIGHT;
}

Bullet::Bullet(double x, double y, double ang, Point _pivot, int _dmg)
{
    pos.x = x;
    pos.y = y;
    angle = ang;
    pivot = _pivot;
    isDestroyed = false;
    lastMovement = SDL_GetTicks();

    dmg = _dmg;
}

bool Bullet::loadImage(const char fileName[])
{
    if (!bulletTexture.loadFromFile(fileName, GD.screenRenderer))
        return false;

    width = bulletTexture.getW();
    height = bulletTexture.getH();

    return true;
}

bool Bullet::render() const
{
    return bulletTexture.render(GD.screenRenderer, pos, angle, &pivot);
}

void Bullet::applyPhysics()
{
    int time = SDL_GetTicks();

    pos.x += speed * (time - lastMovement) * cos(angle / 180.0 * PI) / 1000.0;
    pos.y += speed * (time - lastMovement) * sin(angle / 180.0 * PI) / 1000.0;

    lastMovement = time;

    if (outOfScreen()) isDestroyed = true;
}

double Bullet::getW()
{
    return bulletTexture.getW();
}

double Bullet::getH()
{
    return bulletTexture.getH();
}

std::vector<Point> Bullet::getPolygon() const
{
    Point pivot(pos.x, pos.y), p;
    std::vector<Point> ret;

    p = pos;
    ret.push_back(Geometry::rotatePoint(p, pivot, angle));

    p = pos; p.x += width;
    ret.push_back(Geometry::rotatePoint(p, pivot, angle));

    p = pos; p.x += width; p.y += height;
    ret.push_back(Geometry::rotatePoint(p, pivot, angle));

    p = pos; p.y += height;
    ret.push_back(Geometry::rotatePoint(p, pivot, angle));

    return ret;
}

int Bullet::getDmg() const
{
    return dmg;
}
