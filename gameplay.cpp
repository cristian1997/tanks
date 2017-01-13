#include "gameplay.h"

bool GamePlay::initialize()
{
    for (int i = 0; i < GD.XDIM; ++i)
    {
        for (int j = 0; j < GD.YDIM; ++j)
        {
            if (map.getType(i, j) == 3)
            {
                tanks.emplace_back(Tank(true));
                tanks.back().initialize(i * GD.SPRITE_WIDTH, j * GD.SPRITE_HEIGHT, 0);
                tanks.back().setKeys(0, GD.tankTextures.size() - 1);
            }
        }
    }

    return true;
}

void GamePlay::applyPhysics()
{
    for (auto &t : tanks) t.applyPhysics(), t.isAllowed = true, t.onWater = false;
    for (auto &b : bullets) b.applyPhysics();
}

void GamePlay::updatePos()
{
    for (auto &t : tanks) t.updatePos();
}

bool GamePlay::render()
{
    SDL_RenderClear(GD.screenRenderer);

    map.render();

    for (const auto &t : tanks)
    {
        if (!t.isDestroyed && !t.render())
        {
            printf("Error rendering tank\n%s\n", SDL_GetError());
            return false;
        }
    }

    for (const auto &b : bullets)
    {
        if (!b.render())
        {
            printf("Error rendering bullet\n%s\n", SDL_GetError());
            return false;
        }
    }

    for (const auto &p : powerUps)
    {
        if (!p.render())
        {
            printf("Error rendering power up\n%s\n", SDL_GetError());
            return false;
        }
    }

    for (const auto &t : tanks)
    {
        if (!t.renderHp())
        {
            printf("Error rendering hp\n%s\n", SDL_GetError());
            return false;
        }
    }

    SDL_RenderPresent(GD.screenRenderer);

    return true;
}

bool GamePlay::checkCollisions()
{
    std::vector<std::vector<Point>> polys;
    for (const auto &t : tanks) polys.push_back(t.getPolygon());

    for (auto i = 0; i < tanks.size(); ++i)
    {
        if (tanks[i].isFake()) continue;

        for (auto &b : bullets)
        {
            auto bulletPoly = b.getPolygon();

            if (!tanks[i].isDestroyed && Geometry::intersect(polys[i], bulletPoly))
            {
                tanks[i].modifyHp(-b.getDmg());
                b.isDestroyed = true;
            }
        }

        if (tanks[i].isDestroyed) continue;

        for (auto j = i + 1; j < tanks.size(); ++j)
        {
            if (tanks[j].isDestroyed) continue;

            if (Geometry::intersect(polys[i], polys[j]))
            {
                tanks[i].isAllowed = false;
                tanks[j].isAllowed = false;
            }
        }

        int x = tanks[i].getX() / GD.SPRITE_WIDTH;
        int y = tanks[i].getY() / GD.SPRITE_HEIGHT;

        for (int ii = x - 2; ii <= x + 2; ++ii)
        {
            for (int j = y - 2; j <= y + 2; ++j)
            {
                if (ii < 0 || ii >= GD.XDIM || j < 0 || j >= GD.YDIM) continue;

                if (!Geometry::intersect(polys[i], Geometry::getPolygon(Point(ii * GD.SPRITE_WIDTH, j * GD.SPRITE_HEIGHT), GD.SPRITE_WIDTH, GD.SPRITE_HEIGHT)))
                    continue;

                int type = map.getType(ii, j);

                if (type == 1) tanks[i].isAllowed = false;
                else if (type == 2) tanks[i].onWater = true;
                else if (type >= 4)
                {
                    if (type == GameData::REVERSE)
                    {
                        Point aux = {tanks[0].getX(), tanks[0].getY()};
                        double auux = tanks[0].getAngle();

                        tanks[0].setPos(Point(tanks[1].getX(), tanks[1].getY()), tanks[1].getAngle());
                        tanks[1].setPos(aux, auux);
                    }
                    else tanks[i].applyPowerUp(static_cast<GameData::PowerUps>(type));

                    map.setType(ii, j, 0);

                    for (auto &p : powerUps)
                    {
                        if (p.getPos() == Point(ii * GD.SPRITE_WIDTH, j * GD.SPRITE_HEIGHT))
                        {
                            p.isDestroyed = true;
                            --nrPowerUps;
                            break;
                        }
                    }
                }
            }
        }
    }

    for (auto &b : bullets)
    {
        auto bPoly = b.getPolygon();

        for (int i = 0; i < tanks.size(); ++i)
        {
            if (!tanks[i].isFake()) continue;

            if (Geometry::intersect(bPoly, polys[i]))
            {
                b.isDestroyed = true;
                tanks[i].isDestroyed = true;
                break;
            }
        }

        int x = b.getPos().x / GD.SPRITE_WIDTH;
        int y = b.getPos().y / GD.SPRITE_HEIGHT;

        for (int i = x - 1; i <= x + 1; ++i)
        {
            for (int j = y - 1; j <= y + 1; ++j)
            {
                if (map.getType(i, j) == 1)
                {
                    if (Geometry::intersect(bPoly, Geometry::getPolygon(Point(i * GD.SPRITE_WIDTH, j * GD.SPRITE_HEIGHT), GD.SPRITE_WIDTH, GD.SPRITE_HEIGHT)))
                    {
                        b.isDestroyed = true;
                    }
                }
            }
        }
    }

    return false;
}

void GamePlay::generateRandomPowerUp()
{
    if (nrPowerUps >= 10) return;

    int x, y;
    bool intersect;
    GameData::PowerUps type = static_cast<GameData::PowerUps>(4 + rand() % GD.nrPowerUps);

    do
    {
        intersect = true;
        x = rand() % (GD.SCREEN_WIDTH / GD.SPRITE_WIDTH);
        y = rand() % (GD.SCREEN_HEIGHT / GD.SPRITE_HEIGHT);

        if (map.getType(x, y) != 0) continue;

        intersect = false;
        for (const auto &t : tanks)
        {
            if (Geometry::intersect(t.getPolygon(), Geometry::getPolygon(Point(x, y), GD.SPRITE_WIDTH, GD.SPRITE_HEIGHT)))
            {
                intersect = true;
                break;
            }
        }
    } while (intersect);

    map.setType(x, y, type);
    powerUps.emplace_back(x * GD.SPRITE_WIDTH, y * GD.SPRITE_HEIGHT, type);
    ++nrPowerUps;
}

GameData::Scene GamePlay::run()
{
    srand(time(nullptr));

    tanks.clear();
    tanks.resize(2);

    tanks[0].initialize(GD.spawnPosition[GD.nrLevel][0].x, GD.spawnPosition[GD.nrLevel][0].y, 0);
    tanks[1].initialize(GD.spawnPosition[GD.nrLevel][1].x, GD.spawnPosition[GD.nrLevel][1].y, 0);

    bullets.clear();
    powerUps.clear();
    nrPowerUps = 0;

    for (int i = 0; i < tanks.size(); ++i) tanks[i].setKeys(i, i);

    map.loadMap();

    if (!initialize()) return GD.QUIT;

    if (!render()) return GD.QUIT;

    bool quit = false;
    SDL_Event e;
    int lastPowerUp = SDL_GetTicks();
    int powerUpTime = (GD.gameMode == 1 ? 2000 : 5000);

    while (!quit)
    {
        for (auto &t : tanks) t.shouldFire = false;

        while (SDL_PollEvent(&e))
        {
            if (e.type == SDL_QUIT)
            {
                quit = true;
            }
            else if (e.type == SDL_KEYDOWN && e.key.keysym.sym == SDLK_ESCAPE)
            {
                return GD.MENU;
            }
            else
            {
                for (auto &t : tanks) t.handleEvent(e);
            }
        }

        for(auto &t : tanks)
        {
            if (!t.shouldFire) continue;

            double x = t.getX() + t.getW() + 10.0;
            double y = t.getY() + (t.getH() - Bullet::getH()) / 2.0;
            double x0 = t.getX() + t.getW() / 2;
            double y0 = t.getY() + t.getH() / 2;

            Point ret = Geometry::rotatePoint(Point(x, y), Point(x0, y0), t.getAngle());
            Bullet bullet(ret.x, ret.y, t.getAngle(), Point(0, 0), t.getDmg());
            bullets.push_back(bullet);
        }

        applyPhysics();
        checkCollisions();
        updatePos();

        for (auto &t : tanks)
        {
            t.updatePowerUps();
        }

        eraseDestroyed(tanks);
        eraseDestroyed(bullets);
        eraseDestroyed(powerUps);

        if (!render()) return GD.QUIT;

        int time = SDL_GetTicks();

        if (time - lastPowerUp > powerUpTime)
        {
            generateRandomPowerUp();
            lastPowerUp = time;
        }
    }

    return GD.QUIT;
}

template<class T>
inline void GamePlay::eraseDestroyed(std::vector<T> &objects)
{
    objects.erase(std::remove_if(objects.begin(), objects.end(),
        [](T o) -> bool { return o.isDestroyed; }),
        objects.end()
    );
}
