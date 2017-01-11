#include "tank.h"
#include "bullet.h"
#include "texture.h"
#include "level.h"
#include "geometry.h"
#include "gamedata.h"
#include "powerup.h"

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
    std::vector<PowerUp> powerUps;

    bool loadMedia();
    void applyPhysics();
    void updatePos();
    bool render();
    bool checkCollisions();
    
    template<class T>
    void eraseDestroyed(std::vector<T> &objects);

public:
    GameData::Scene run();
};