#include "bullet.h"
#include <iostream>

Bullet::Bullet(float x, float y, float ang)
{
    std::cout << "Bullet\n";
    xPos = x;
    yPos = y;
    angle = ang;
    lastMovement = SDL_GetTicks();
}

bool Bullet::loadImage(SDL_Renderer * renderer)
{
    return bulletTexture.loadFromFile("sprites/bullet.png", renderer);
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
    bulletTexture.~Texture();
}
