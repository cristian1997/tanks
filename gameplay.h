#include "tank.h"
#include "bullet.h"
#include "texture.h"
#include "level.h"
#include "geometry.h"
#include "gamedata.h"

#include <SDL.h>
#include <SDL_image.h>
#include <vector>
#include <algorithm>

class GamePlay 
{
private:
	Tank player, tt;
    std::vector<Bullet> bullets;

    bool loadMedia();
    void updatePos();
    bool render();
    bool checkCollisions();

public:
	bool continuePlay = true;
    GameData::Scene run();
};