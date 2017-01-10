#pragma once

#include "texture.h"
#include "gamedata.h"

#include <SDL2\SDL.h>
#include <SDL2\SDL_image.h>
#include <map>
#include <vector>
#include <algorithm>

class Tank
{
private:
    int lastMovement, lastFire;
    int width, height;
    Point pos;
    double angle;
    double speed, turnSpeed;
    double defaultFireRate, fireRate; // rounds per second
    std::map<std::string, decltype(SDLK_0)> keys;

    bool outOfScreen() const;

public:
    Texture *tankTexture;
    double maxSpeed, maxTurnSpeed;        // pixels per second
    bool shouldFire;
    bool isDestroyed;

    Tank();
    bool setKeys(int ind);
    void initialize(double x, double y, double angle);
    bool render() const;
    void updatePos();
    double getX() const;
    double getY() const;
    double getW() const;
    double getH() const;
    double getAngle() const;
    std::vector<Point> getPolygon() const;

    void handleEvent(const SDL_Event &e);
};