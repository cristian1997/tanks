#include "map.h"

void Map::loadMap()
{
    std::string s = "sprites/map" + std::to_string(GD.nrLevel) + std::string(".jpg");

    mapTexture.loadFromFile(s.c_str(), GD.screenRenderer);

    s = "collisions/collisions" + std::to_string(GD.nrLevel) + std::string(".txt");
    std::ifstream fin(s.c_str());

    for (int i = 0; i < GD.SCREEN_HEIGHT / GD.SPRITE_HEIGHT; ++i)
    {
        for (int j = 0; j < GD.SCREEN_WIDTH / GD.SPRITE_WIDTH; ++j)
        {
            fin >> type[j][i];
        }
    }
}

bool Map::render() const
{
    SDL_Rect rect = {0, 0, GD.SCREEN_WIDTH, GD.SCREEN_HEIGHT};

    return mapTexture.render(GD.screenRenderer, rect);
}

int Map::getType(int i, int j) const
{
    if (i < 0 || i >= GD.XDIM || j < 0 || j >= GD.YDIM) return -1;
    return type[i][j];
}

void Map::setType(int i, int j, int newType)
{
    type[i][j] = newType;
}
