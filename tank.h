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
    bool shouldFire;

    Tank();
    bool loadImage(const char *fileName, SDL_Renderer *renderer);
    void setPos(double x, double y, double angle);
    bool render(SDL_Renderer *&dest) const;
    void updatePos();
    double getX() const;
    double getY() const;
    double getW() const;
    double getH() const;
    double getAngle() const;

    void handleEvent(const SDL_Event &e);

    ~Tank();
};