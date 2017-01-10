#include "tank.h"
#include "gamedata.h"

#include <iostream>
#include <cmath>


Tank::Tank()
{
    lastMovement = SDL_GetTicks();
    lastFire = -10000;

    maxTurnSpeed = 144;
    maxSpeed = 100;
    angle = 0.0;
    fireRate = 2.0;

    keys[std::string("up")] = SDLK_UP;
    keys[std::string("down")] = SDLK_DOWN;
    keys[std::string("left")] = SDLK_LEFT;
    keys[std::string("right")] = SDLK_RIGHT;
    keys[std::string("fire")] = SDLK_SPACE;
}

bool Tank::loadImage(const char * fileName, SDL_Renderer *renderer)
{
    return tankTexture.loadFromFile(fileName, renderer);
}

void Tank::setPos(double x, double y, double _angle)
{
    pos.x = x;
    pos.y = y;
    angle = _angle;

    lastMovement = SDL_GetTicks();
    lastFire = -10000;

    speed = 0;
    turnSpeed = 0;
    shouldFire = false;
}

bool Tank::render(SDL_Renderer* &renderer) const
{
    return tankTexture.render(renderer, pos, angle);
}

void Tank::updatePos()
{
    int time = SDL_GetTicks();

    pos.x += speed * (time - lastMovement) * cos(angle / 180.0 * PI) / 1000.0;
    pos.y += speed * (time - lastMovement) * sin(angle / 180.0 * PI) / 1000.0;

    if (pos.x < 0) pos.x = 0;
    if (pos.x + width > GD.SCREEN_WIDTH) pos.x = GD.SCREEN_WIDTH - width;

    if (pos.y < 0) pos.y = 0;
    if (pos.y + height > GD.SCREEN_HEIGHT) pos.y = GD.SCREEN_HEIGHT - height;

    angle += turnSpeed * (time - lastMovement) / 1000.0;

    lastMovement = time;
}

double Tank::getX() const
{
    return pos.x;
}

double Tank::getY() const
{
    return pos.y;
}

double Tank::getW() const
{
    return tankTexture.getW();
}

double Tank::getH() const
{
    return tankTexture.getH();
}

double Tank::getAngle() const
{
    return angle;
}

void Tank::handleEvent(const SDL_Event &e)
{
    auto sym = e.key.keysym.sym;

    switch (e.type)
    {
        case SDL_KEYDOWN:
            if (sym == keys[std::string("up")]) speed = maxSpeed;
            else if (sym == keys[std::string("down")]) speed = -maxSpeed;
            else if (sym == keys[std::string("left")]) turnSpeed = -maxTurnSpeed;
            else if (sym == keys[std::string("right")]) turnSpeed = maxTurnSpeed;
            else if (sym == keys[std::string("fire")])
            {
                int time = SDL_GetTicks();

                if (time - lastFire > 1000.0 / fireRate)
                {
                    lastFire = time;
                    shouldFire = true;
                }
            }
            break;
        
        case SDL_KEYUP:
            if (sym == keys[std::string("up")]) { if (speed > 0) speed = 0; }
            else if (sym == keys[std::string("down")]) { if (speed < 0) speed = 0; }
            else if (sym == keys[std::string("left")]) { if (turnSpeed < 0) turnSpeed = 0; }
            else if (sym == keys[std::string("right")]) { if (turnSpeed > 0) turnSpeed = 0; }
            break;
    }
}

Tank::~Tank()
{
    tankTexture.~Texture();
}
