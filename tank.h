#pragma once

#include <SDL2\SDL.h>
#include <SDL2\SDL_image.h>
#include "texture.h"


class Tank
{
private:
    Texture tankTexture;
    int lastMovement, lastFire;
    int width, height;
    Point pos;
    double angle;
    double speed, turnSpeed;
    double fireRate; // rounds per second

public:
    double maxSpeed, maxTurnSpeed;        // pixels per second

    Tank();
    bool loadImage(const char *fileName, SDL_Renderer *renderer);
    void setPos(double x, double y, double angle);
    bool render(SDL_Renderer *&dest);
    void updatePos();
    double getX();
    double getY();
    double getW();
    double getH();
    double getAngle();
    bool fire();

    void handleEvent(const SDL_Event &e);

    ~Tank();
};