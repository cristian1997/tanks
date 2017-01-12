#include "map.h"

void Map::loadMap()
{
    std::string s = "sprites/defaultmap" + std::to_string(GD.nrLevel) + std::string(".jpg");

    mapTexture.loadFromFile(s.c_str(), GD.screenRenderer);

    s = "collisions/collisions" + std::to_string(GD.nrLevel) + std::string(".txt");
    std::ifstream fin(s.c_str());

    GD.obstacles.clear();

    for (int i = 0; i < GD.SCREEN_HEIGHT / GD.SPRITE_HEIGHT; ++i)
    {
        for (int j = 0; j < GD.SCREEN_WIDTH / GD.SPRITE_WIDTH; ++j)
        {
            int x;
            fin >> x;

            if (x == 1)
            {
                GD.obstacles.emplace_back(j * GD.SPRITE_WIDTH, i * GD.SPRITE_HEIGHT);
            }
        }
    }
}

bool Map::render() const
{
    SDL_Rect rect = {0, 0, GD.SCREEN_WIDTH, GD.SCREEN_HEIGHT};

    return mapTexture.render(GD.screenRenderer, rect);
}