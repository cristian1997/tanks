#include "bullet.h"
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

bool Bullet::loadImage(const char fileName[], SDL_Renderer * renderer)
{
    return bulletTexture.loadFromFile(fileName, renderer);
}

bool Bullet::render(SDL_Renderer *& dest)
{
    return bulletTexture.render(dest, pos, angle, &pivot);
}

void Bullet::updatePos()
{
    int time = SDL_GetTicks();

    pos.x += speed * (time - lastMovement) * cos(angle / 180.0 * acos(-1)) / 1000.0;
    pos.y += speed * (time - lastMovement) * sin(angle / 180.0 * acos(-1)) / 1000.0;

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

Bullet::~Bullet()
{
    
}
