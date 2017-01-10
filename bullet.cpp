#include "bullet.h"
#include "gamedata.h"
#include <iostream>

Texture Bullet::bulletTexture;
int Bullet::width, Bullet::height;

Bullet::Bullet(double x, double y, double ang, Point _pivot)
{
    pos.x = x;
    pos.y = y;
    angle = ang;
    pivot = _pivot;
    lastMovement = SDL_GetTicks();
}

bool Bullet::loadImage(const char fileName[])
{
    if (!bulletTexture.loadFromFile(fileName))
        return false;

    width = bulletTexture.getW();
    height = bulletTexture.getH();

    return true;
}

bool Bullet::render() const
{
    return bulletTexture.render(pos, angle, &pivot);
}

void Bullet::updatePos()
{
    int time = SDL_GetTicks();

    pos.x += speed * (time - lastMovement) * cos(angle / 180.0 * PI) / 1000.0;
    pos.y += speed * (time - lastMovement) * sin(angle / 180.0 * PI) / 1000.0;

    lastMovement = time;
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