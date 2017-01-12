#pragma once

#include "geometry.h"
#include "gamedata.h"

#include <vector>

class PowerUp
{
private:
    Point pos;
    GameData::PowerUps type;
    static int width, height;
    std::vector<Point> poly;

public:
    bool isDestroyed;

    PowerUp(int x, int y, GameData::PowerUps _type);
    bool render() const;
    GameData::PowerUps getType() const;
    std::vector<Point> getPolygon() const;
};