#include "tank.h"
#include <iostream>
#include <cmath>

const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;


Tank::Tank()
{
    lastMovement = lastFire = SDL_GetTicks();

    maxTurnSpeed = 144;
    maxSpeed = 100;
    angle = 0.0;
    fireRate = 2.0;
}

bool Tank::loadImage(const char * fileName, SDL_Renderer *renderer)
{
    return tankTexture.loadFromFile(fileName, renderer);
}

void Tank::setPos(double x, double y)
{
    pos.x = x;
    pos.y = y;
}

bool Tank::render(SDL_Renderer* &renderer)
{
    return tankTexture.render(renderer, pos, angle);
}

void Tank::updatePos()
{
    int time = SDL_GetTicks();

    pos.x += speed * (time - lastMovement) * cos(angle / 180.0 * acos(-1)) / 1000.0;
    pos.y += speed * (time - lastMovement) * sin(angle / 180.0 * acos(-1)) / 1000.0;

    if (pos.x < 0) pos.x = 0;
    if (pos.x + width > SCREEN_WIDTH) pos.x = SCREEN_WIDTH - width;

    if (pos.y < 0) pos.y = 0;
    if (pos.y + height > SCREEN_HEIGHT) pos.y = SCREEN_HEIGHT - height;

    angle += turnSpeed * (time - lastMovement) / 1000.0;

    lastMovement = time;
}

double Tank::getX()
{
    return pos.x;
}

double Tank::getY()
{
    return pos.y;
}

double Tank::getW()
{
    return tankTexture.getW();
}

double Tank::getH()
{
    return tankTexture.getH();
}

double Tank::getAngle()
{
    return angle;
}

bool Tank::fire()
{
    int time = SDL_GetTicks();

    if (time - lastFire > 1000.0 / fireRate)
    {
        lastFire = time;
        return true;
    }

    return false;
}

void Tank::handleEvent(const SDL_Event &e)
{
    switch (e.type)
    {
        case SDL_KEYDOWN:
            switch (e.key.keysym.sym)
            {
                case SDLK_UP: speed = maxSpeed; break;
                case SDLK_DOWN: speed = -maxSpeed; break;
                case SDLK_LEFT: turnSpeed = -maxTurnSpeed; break;
                case SDLK_RIGHT: turnSpeed = maxTurnSpeed; break;
            }
            break;
        
        case SDL_KEYUP:
            switch (e.key.keysym.sym)
            {
                case SDLK_UP: if (speed > 0) speed = 0; break;
                case SDLK_DOWN: if (speed < 0) speed = 0; break;
                case SDLK_LEFT: if (turnSpeed < 0) turnSpeed = 0; break;
                case SDLK_RIGHT: if (turnSpeed > 0) turnSpeed = 0; break;
            }
            break;
    }
}

Tank::~Tank()
{
    tankTexture.~Texture();
}
