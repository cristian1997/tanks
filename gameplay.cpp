#include "gameplay.h"

#include <iostream>

bool GamePlay::loadMedia()
{
    for (auto i = 0; i < tanks.size(); ++i) tanks[i].tankTexture = GD.playerText;

    return true;
}

void GamePlay::applyPhysics()
{
    for (auto &t : tanks) t.applyPhysics(), t.isAllowed = true;
    for (auto &b : bullets) b.applyPhysics();
}

void GamePlay::updatePos()
{
    for (auto &t : tanks) t.updatePos();
}

bool GamePlay::render()
{
    SDL_RenderClear(GD.screenRenderer);

    //map.render();

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
        for (auto &b : bullets)
        {
            auto bulletPoly = b.getPolygon();

            if (!tanks[i].isDestroyed && Geometry::intersect(polys[i], bulletPoly))
            {
                tanks[i].modifyHp(-b.getDmg());
                b.isDestroyed = true;
            }
        }

        for (auto j = i + 1; j < tanks.size(); ++j)
        {
            if (tanks[i].isDestroyed || tanks[j].isDestroyed) continue;

            if (Geometry::intersect(polys[i], polys[j]))
            {
                tanks[i].isAllowed = false;
                tanks[j].isAllowed = false;
            }
        }

        for (auto &p : powerUps)
        {
            if (Geometry::intersect(polys[i], p.getPolygon()))
            {
                p.isDestroyed = true;
                tanks[i].applyPowerUp(p.getType());
            }
        }
    }

    return false;
}

void GamePlay::generateRandomPowerUp()
{
    int x = rand() % GD.SCREEN_WIDTH;
    int y = rand() % GD.SCREEN_HEIGHT;
    GameData::PowerUps type = static_cast<GameData::PowerUps>(rand() % GD.nrPowerUps);

    powerUps.emplace_back(x, y, type);
}

GameData::Scene GamePlay::run()
{
    srand(time(nullptr));
    tanks.resize(2);

    if (!loadMedia()) return GD.QUIT;

    tanks[0].initialize(20, 20, 0);
    tanks[1].initialize(200, 200, 0);

    for (int i = 0; i < tanks.size(); ++i) tanks[i].setKeys(i);

    if (!render()) return GD.QUIT;

    bool quit = false;
    SDL_Event e;
    int frames = 0;
    int start = SDL_GetTicks();
    int lastPowerUp = start;

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

        for(const auto &t : tanks)
        {
            if (!t.shouldFire) continue;

            double x = t.getX() + t.getW() + 5.0;
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

        if (time - lastPowerUp > 2000)
        {
            generateRandomPowerUp();
            lastPowerUp = time;
        }

        ++frames;

        if (time - start >= 1000)
        {
            //printf("%d\n", frames);
            frames = 0;
            start = time;
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
