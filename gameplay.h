#include "tank.h"
#include "bullet.h"
#include "texture.h"
#include "geometry.h"
#include "gamedata.h"
#include "powerup.h"
#include "map.h"

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_mixer.h>
#include <vector>
#include <algorithm>
#include <ctime>
#include <cstdlib>

class GamePlay 
{
private:
    std::vector<Tank> tanks;
    std::vector<Bullet> bullets;
    std::vector<Point> obstacles;
    std::vector<PowerUp> powerUps;
    Map map;
    int nrPowerUps;

    bool initialize();
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