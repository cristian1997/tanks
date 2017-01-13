#include "map.h"

void Map::loadMap(std::vector<Tank> &tanks)
{
    std::string s = "sprites/map" + std::to_string(GD.nrLevel) + std::string(".jpg");

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
            else if (x == 3)
            {
                tanks.emplace_back(Tank(true));
                tanks.back().initialize(j * GD.SPRITE_WIDTH, i * GD.SPRITE_HEIGHT, 0);
                tanks.back().setKeys(0, GD.tankTextures.size() - 1);
            }
        }
    }
}

bool Map::render() const
{
    SDL_Rect rect = {0, 0, GD.SCREEN_WIDTH, GD.SCREEN_HEIGHT};

    return mapTexture.render(GD.screenRenderer, rect);
}