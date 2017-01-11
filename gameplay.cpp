#include "gameplay.h"
//#include "level.h"

#include <iostream>

/*void GamePlay::openFile(int nrLevel)
{
	open(nrLevel);
}*/

bool GamePlay::loadMedia()
{
    for(int i = 0;  i<nrTanks; ++i) tanks[i].tankTexture = GD.playerText;

    return true;
}

void GamePlay::updatePos()
{
    for (auto &t : tanks) t.updatePos();
    for (auto &b : bullets) b.updatePos();
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

    for (auto &b : bullets)
    {
        if (!b.render())
        {
            printf("Error rendering bullet\n%s\n", SDL_GetError());
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

    for (int i = 0; i < nrTanks; ++i)
    {
        for (auto &b : bullets)
        {
            auto bulletPoly = b.getPolygon();

            if (!tanks[i].isDestroyed && Geometry::intersect(polys[i], bulletPoly))
            {
                tanks[i].isDestroyed = true;
                b.isDestroyed = true;
            }
        }
    }

    return false;
}

GameData::Scene GamePlay::run()
{
    //openFile(nrLevel);
    nrTanks = 2;
    tanks.resize(2);

    if (!loadMedia()) return GD.QUIT;

    tanks[0].initialize(20, 20, 0);
    tanks[1].initialize(200, 200, 0);

    for (int i = 0; i < nrTanks; ++i) tanks[i].setKeys(i);

    if (!render()) return GD.QUIT;

    bool quit = false;
    SDL_Event e;
    int frames = 0;
    int start = SDL_GetTicks();

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
            else if (e.type == SDL_KEYDOWN && e.key.keysym.sym == SDLK_1)
            {
                bullets.clear();
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
            Bullet bullet(ret.x, ret.y, t.getAngle(), Point(0, 0));
            bullets.push_back(bullet);
        }

        updatePos();
        checkCollisions();

        bullets.erase(std::remove_if(bullets.begin(), bullets.end(),
            [](Bullet b) -> bool { return b.isDestroyed; }),
            bullets.end()
        );

        if (!render()) return GD.QUIT;

        ++frames;

        if (SDL_GetTicks() - start >= 1000)
        {
            //printf("%d\n", frames);
            frames = 0;
            start = SDL_GetTicks();
        }
    }

    return GD.QUIT;
}