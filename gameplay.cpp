#include "gameplay.h"
//#include "level.h"

#include <iostream>

/*void GamePlay::openFile(int nrLevel)
{
	open(nrLevel);
}*/

bool GamePlay::loadMedia()
{
    if (!player.loadImage("sprites/blue tank.png"))
    {
        printf("Unable to load image sprites/blue tank.png! SDL Error: %s\n", SDL_GetError());
        return false;
    }

    if (!tt.loadImage("sprites/blue tank.png"))
    {
        printf("Unable to load image sprites/blue tank.png! SDL Error: %s\n", SDL_GetError());
        return false;
    }

    return true;
}

void GamePlay::updatePos()
{
    player.updatePos();

    tt.updatePos();

    for (auto &b : bullets)
    {
        b.updatePos();
    }
}

bool GamePlay::render()
{
    SDL_RenderClear(GD.screenRenderer);

    if (!player.render())
    {
        printf("Error rendering player\n%s\n", SDL_GetError());
        return false;
    }

    if (!tt.render())
    {
        printf("Error rendering player\n%s\n", SDL_GetError());
        return false;
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
    auto playerPoly = player.getPolygon();
    auto ttPoly = tt.getPolygon();

    for (const auto &b : bullets)
    {
        auto bulletPoly = b.getPolygon();

        if (Geometry::intersect(playerPoly, bulletPoly))
            std::cout << "Player hit\n";

        if (Geometry::intersect(ttPoly, bulletPoly))
            std::cout << "Enemy hit\n";
    }

    return false;
}

GameData::Scene GamePlay::run()
{
    //openFile(nrLevel);

    int frames;

    if (!loadMedia()) return GD.QUIT;

    player.setPos(10, 10, 0.0);
    tt.setPos(500, 60, 0.0);

    if (!render()) return GD.QUIT;

    bool quit = false;
    SDL_Event e;
    frames = 0;
    int start = SDL_GetTicks();

    while (!quit)
    {
        player.shouldFire = false;
        tt.shouldFire = false;

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
            else if (e.type == SDL_KEYDOWN && e.key.keysym.sym == SDLK_0)
            {
                for (auto p : tt.getPolygon()) std::cout << p.x << ' ' << p.y << '\n';
                std::cout << '\n';
                for (auto p : bullets[0].getPolygon()) std::cout << p.x << ' ' << p.y << '\n';
            }
            else player.handleEvent(e), tt.handleEvent(e);
        }

        if (player.shouldFire)
        {
            double x = player.getX() + player.getW() + 5.0;
            double y = player.getY() + (player.getH() - Bullet::getH()) / 2.0;
            double x0 = player.getX() + player.getW() / 2;
            double y0 = player.getY() + player.getH() / 2;

            Point ret = Geometry::rotatePoint(Point(x, y), Point(x0, y0), player.getAngle());
            Bullet bullet(ret.x, ret.y, player.getAngle(), Point(0, 0));
            bullets.push_back(bullet);
        }

        updatePos();
        checkCollisions();

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