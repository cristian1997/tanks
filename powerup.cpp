#include "powerup.h"

int PowerUp::width = 25, PowerUp::height = 25;

PowerUp::PowerUp(int x, int y, GameData::PowerUps _type)
{
    pos.x = x;
    pos.y = y;
    type = _type;

    isDestroyed = false;

    poly.emplace_back(x, y);
    poly.emplace_back(x + width, y);
    poly.emplace_back(x + width, y + height);
    poly.emplace_back(x, y + height);
}

bool PowerUp::render() const
{
    SDL_Rect dest = { pos.x, pos.y, width, height };

    return GD.powerUpTextures[type - 4].render(GD.screenRenderer, dest);
}

GameData::PowerUps PowerUp::getType() const
{
    return type;
}

std::vector<Point> PowerUp::getPolygon() const
{
    return poly;
}

Point PowerUp::getPos() const
{
    return pos;
}
