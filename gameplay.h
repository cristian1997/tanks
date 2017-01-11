#include "tank.h"
#include "bullet.h"
#include "texture.h"
#include "level.h"
#include "geometry.h"
#include "gamedata.h"

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <vector>
#include <algorithm>

class GamePlay 
{
private:
    int nrTanks;
    std::vector<Tank> tanks;
    //Map map;
    std::vector<Bullet> bullets;

	//void openFile(int nrLevel);
    bool loadMedia();
    void updatePos();
    bool render();
    bool checkCollisions();

public:
    GameData::Scene run();
};