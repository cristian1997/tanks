#include "tank.h"
#include <iostream>
#include <cmath>

const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;


Tank::Tank()
{
    lastMovement = SDL_GetTicks();

    maxTurnSpeed = 144;
    maxSpeed = 100;
    angle = 0.0;
}

bool Tank::loadImage(const char * fileName, SDL_Renderer *renderer)
{
    return tankTexture.loadFromFile(fileName, renderer);
}

void Tank::setPos(double x, double y)
{
    xPos = x;
    yPos = y;
}

bool Tank::render(SDL_Renderer* &renderer)
{
    return tankTexture.render(renderer, (int)xPos, (int)yPos, angle);
}

void Tank::updatePos()
{
    int time = SDL_GetTicks();

    xPos += speed * (time - lastMovement) * cos(angle / 180.0 * acos(-1)) / 1000.0;
    yPos += speed * (time - lastMovement) * sin(angle / 180.0 * acos(-1)) / 1000.0;

    if (xPos < 0) xPos = 0;
    if (xPos + width > SCREEN_WIDTH) xPos = SCREEN_WIDTH - width;

    if (yPos < 0) yPos = 0;
    if (yPos + height > SCREEN_HEIGHT) yPos = SCREEN_HEIGHT - height;

    angle += turnSpeed * (time - lastMovement) / 1000.0;

    lastMovement = time;
}

double Tank::getX()
{
    return xPos;
}

double Tank::getY()
{
    return yPos;
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
