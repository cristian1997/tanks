#include "gameplay.h"
#include "level.h"

#include <iostream>

void GamePlay::openFile(int nrLevel)
{
	//open(nrLevel);
}

GameData::Scene GamePlay::run()
{
    std::cout << "Gameplay\n";
    //openFile(nrLevel);

    int frames;

    if (!player.loadImage("sprites/blue tank.png", GD.screenRenderer))
    {
        printf("Unable to load image sprites/blue tank.png! SDL Error: %s\n", SDL_GetError());
        return GD.QUIT;
    }

    player.setPos(10, 10, 0.0);

    if (!player.render(GD.screenRenderer))
        printf("Error rendering player\n");

    SDL_UpdateWindowSurface(GD.window);

    bool quit = false;
    SDL_Event e;
    frames = 0;
    int start = SDL_GetTicks();

    while (!quit)
    {
        if (SDL_PollEvent(&e))
        {
            if (e.type == SDL_QUIT)
            {
                quit = true;
            }
            else if (e.type == SDL_KEYDOWN && e.key.keysym.sym == SDLK_SPACE)
            {
                if (!player.fire()) continue;

                double x = player.getX() + player.getW() + 5.0;
                double y = player.getY() + (player.getH() - Bullet::getH()) / 2.0;
                double x0 = player.getX() + player.getW() / 2;
                double y0 = player.getY() + player.getH() / 2;

                Point ret = Geometry::rotatePoint(Point(x, y), Point(x0, y0), player.getAngle());
                Bullet bullet(ret.x, ret.y, player.getAngle(), Point(0, 0));
                bullets.push_back(bullet);
            }
            else if (e.type == SDL_KEYDOWN && e.key.keysym.sym == SDLK_ESCAPE)
            {
                return GD.MENU;
            }
            else player.handleEvent(e);
        }
        SDL_RenderClear(GD.screenRenderer);
        player.updatePos();

        if (!player.render(GD.screenRenderer))
            printf("Error\n");

        for (auto b : bullets)
        {
            b.updatePos();
            if (!b.render(GD.screenRenderer))
            {
                printf("Error rendering bullet\n");
                printf("%s\n", SDL_GetError());
            }
        }

        SDL_RenderPresent(GD.screenRenderer);

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