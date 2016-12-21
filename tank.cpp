#include "tank.h"
#include <iostream>
#include <cmath>

const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;

SDL_Texture * Tank::loadTexture(const char fileName[], SDL_Renderer *renderer)
{
    SDL_Surface *tempSurface;
    SDL_Texture *retTexture;

    tempSurface = IMG_Load(fileName);
    if (tempSurface == nullptr) return nullptr;

    SDL_SetColorKey(tempSurface, SDL_TRUE, SDL_MapRGB(tempSurface->format, 0xFF, 0xFF, 0xFF));

    retTexture = SDL_CreateTextureFromSurface(renderer, tempSurface);

    SDL_FreeSurface(tempSurface);
    return retTexture;
}

Tank::Tank()
{
    tankRenderer = nullptr;
    boolHasMoved = false;
    lastMovement = SDL_GetTicks();

    maxTurnSpeed = 144;
    maxSpeed = 100;
    angle = 0.0;
}

bool Tank::loadImage(const char * fileName, SDL_Renderer *renderer)
{
    tankRenderer = loadTexture(fileName, renderer);
    if (tankRenderer == nullptr) return false;

    SDL_QueryTexture(tankRenderer, nullptr, nullptr, &width, &height);

    return true;
}

void Tank::setPos(float x, float y)
{
    xPos = x;
    yPos = y;
}

bool Tank::render(SDL_Renderer* &renderer)
{
    SDL_Rect pos = {(int)xPos, (int)yPos, width, height};

    boolHasMoved = false;
    SDL_RendererFlip fp = SDL_FLIP_NONE;
    if (SDL_RenderCopyEx(renderer, tankRenderer, nullptr, &pos, angle, nullptr, fp)) return false;

    SDL_RenderPresent(renderer);

    return true;
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
    boolHasMoved = (speed || turnSpeed);
}

bool Tank::hasMoved()
{
    return boolHasMoved;
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

    printf("%f\nsin = %f\ncos = %f\n", angle, sin(angle), cos(angle));
}

Tank::~Tank()
{
    SDL_DestroyTexture(tankRenderer);
    tankRenderer = nullptr;
}
