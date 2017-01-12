#include "tank.h"
#include "bullet.h"
#include "texture.h"
#include "geometry.h"
#include "gamedata.h"
#include "powerup.h"
#include "map.h"

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <vector>
#include <algorithm>
#include <ctime>
#include <cstdlib>

class GamePlay 
{
private:
    std::vector<Tank> tanks;
    std::vector<Bullet> bullets;
    std::vector<PowerUp> powerUps;
    Map map;

    bool loadMedia();
    void applyPhysics();
    void updatePos();
    bool render();
    bool checkCollisions();
    void generateRandomPowerUp();
    
    template<class T>
    void eraseDestroyed(std::vector<T> &objects);

public:
    GameData::Scene run();
};