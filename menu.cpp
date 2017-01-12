#include "menu.h"

#include <iostream>

bool Menu::loadMedia()
{
    if (!background.loadFromFile("sprites/menu.jpg", GD.screenRenderer))
    {
        return false;
    }

    buttons.clear();

    SDL_Rect rectForPlay = {GD.SCREEN_WIDTH / 4, GD.SCREEN_HEIGHT / 4, GD.SCREEN_WIDTH / 2 - 100, GD.SCREEN_HEIGHT / 4 - 50};
    buttons.emplace_back(rectForPlay, GD.MAPSELECTION, "play.png");

    SDL_Rect rectForOptions = {GD.SCREEN_WIDTH / 4, GD.SCREEN_HEIGHT / 4 + GD.SCREEN_HEIGHT / 4 - 49 , GD.SCREEN_WIDTH / 2 - 100, GD.SCREEN_HEIGHT / 4 - 50};
    //buttons.emplace_back(rectForOptions, GD.OPTIONS, "options.png");

    SDL_Rect rectForExit = {GD.SCREEN_WIDTH / 4, GD.SCREEN_HEIGHT / 4 + GD.SCREEN_HEIGHT / 4 - 50 + GD.SCREEN_HEIGHT / 4 - 48 - 100, GD.SCREEN_WIDTH / 2 , GD.SCREEN_HEIGHT / 4 - 50};
    //buttons.emplace_back(rectForExit, GD.QUIT, "exit.png");

    return true;
}

bool Menu::render() const
{
    background.render(GD.screenRenderer, Point(0, 0), 0);

    for (const auto &b : buttons)
    {
        b.render();
    }

    SDL_RenderPresent(GD.screenRenderer);

    return true;
}

GameData::Scene Menu::run()
{
    render();

    int x, y;
    bool hadBeenRendered;
    SDL_Event e;

    while (true)
    {
        hadBeenRendered = false;
        SDL_GetMouseState(&x, &y);

        if (SDL_PollEvent(&e))
        {
            switch (e.type)
            {
                case SDL_QUIT:
                    return GD.QUIT;
                    break;
                case SDL_KEYDOWN:
                {
                    switch (e.key.keysym.sym)
                    {
                        case SDLK_RETURN:
                            return GD.GAMEPLAY;
                            break;
                        case SDLK_ESCAPE:
                            return GD.QUIT;
                            break;
                    }
                    break;
                }
                case SDL_MOUSEBUTTONDOWN:
                {
                    for (const auto &b : buttons)
                    {
                        if (b.mouseInside())
                        {
                            return b.getAction();
                        }
                    }
                }
            }
        }

        for (auto &b : buttons)
        {
            if (b.handleMouseMotion(x, y))
            {
                b.render();
                hadBeenRendered = true;
            }
        }

        if (hadBeenRendered)
        {
            SDL_RenderPresent(GD.screenRenderer);
        }
    }

    return GD.QUIT;
}
