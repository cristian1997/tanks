#include "tank.h"
#include <iostream>

tank::tank()
{
    tankSurface = nullptr;
    boolHasMoved = false;
    lastMovement = SDL_GetTicks();

    xVel = 100;
    yVel = 100;
    dx = dy = 0.0;
}

bool tank::loadImage(const char * fileName)
{
    return (tankSurface = IMG_Load(fileName));
}

void tank::setPos(float x, float y)
{
    xPos = x;
    yPos = y;
}

bool tank::render(SDL_Surface* &dest)
{
    SDL_Rect pos = {(int)xPos, (int)yPos};

    boolHasMoved = false;
    return !SDL_BlitSurface(tankSurface, nullptr, dest, &pos);
}

void tank::updatePos()
{
    int time = SDL_GetTicks();

    xPos += dx * (time - lastMovement) / 1000.0;
    yPos += dy * (time - lastMovement) / 1000.0;

    lastMovement = time;
    boolHasMoved = (dx != 0.0 || dy != 0.0);
}

bool tank::hasMoved()
{
    return boolHasMoved;
}

void tank::handleEvent(const SDL_Event &e)
{
    switch (e.type)
    {
        case SDL_KEYDOWN:
            switch (e.key.keysym.sym)
            {
                case SDLK_UP: dy = -yVel; break;
                case SDLK_DOWN: dy = yVel; break;
                case SDLK_LEFT: dx = -xVel; break;
                case SDLK_RIGHT: dx = xVel; break;
            }
            break;
        
        case SDL_KEYUP:
            switch (e.key.keysym.sym)
            {
                case SDLK_UP: if (dy < 0) dy = 0; break;
                case SDLK_DOWN: if (dy > 0) dy = 0; break;
                case SDLK_LEFT: if (dx < 0) dx = 0; break;
                case SDLK_RIGHT: if (dx > 0) dx = 0; break;
            }
            break;
    }
}

tank::~tank()
{
    SDL_FreeSurface(tankSurface);
    tankSurface = nullptr;
}
