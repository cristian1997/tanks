#include "tank.h"
#include "bullet.h"
#include "texture.h"
#include "level.h"
#include "geometry.h"
#include "gamedata.h"

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <vector>

class GamePlay 
{
private:
	Tank player, tt;
    std::vector<Bullet> bullets;

	//void openFile(int nrLevel);

public:
    GameData::Scene run();
};