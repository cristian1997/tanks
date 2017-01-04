#include "bullet.h"
#include <iostream>

Texture Bullet::bulletTexture;
int Bullet::width, Bullet::height;

Bullet::Bullet(double x, double y, double ang)
{
    xPos = x;
    yPos = y;
    angle = ang;
    lastMovement = SDL_GetTicks();
}

bool Bullet::loadImage(const char fileName[], SDL_Renderer * renderer)
{
    return bulletTexture.loadFromFile(fileName, renderer);
}

bool Bullet::render(SDL_Renderer *& dest)
{
    return bulletTexture.render(dest, xPos, yPos, angle);
}

void Bullet::updatePos()
{
    int time = SDL_GetTicks();

    xPos += speed * (time - lastMovement) * cos(angle / 180.0 * acos(-1)) / 1000.0;
    yPos += speed * (time - lastMovement) * sin(angle / 180.0 * acos(-1)) / 1000.0;

    lastMovement = time;
}

Bullet::~Bullet()
{
    
}
