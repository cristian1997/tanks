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
    int ind;
    int hp, dmg, baseDmg;
    int width, height;
    Point pos, prevPos;
    double angle, prevAngle;
    double speed, turnSpeed;
    double baseFireRate, fireRate; // rounds per second
    std::map<std::string, decltype(SDLK_0)> keys;
    int lastPowerUp[GD.nrPowerUps];
    double baseMaxSpeed, baseMaxTurnSpeed;

    bool outOfScreen() const;
    void updateSpeed(double newSpeed);

public:
    Texture *tankTexture, hpTexture;
    double maxSpeed, maxTurnSpeed;        // pixels per second
    bool shouldFire, isDestroyed, isAllowed;

    Tank();
    bool setKeys(int _ind);
    void initialize(double x, double y, double angle);
    bool render() const;
    bool renderHp() const;
    void applyPhysics();
    void updatePos();
    double getX() const;
    double getY() const;
    double getW() const;
    double getH() const;
    double getAngle() const;
    std::vector<Point> getPolygon() const;
    void applyPowerUp(GameData::PowerUps type);
    void updatePowerUps();
    void modifyHp(int diff);
    int getDmg() const;

    void handleEvent(const SDL_Event &e);
};