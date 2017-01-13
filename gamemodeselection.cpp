#include "gamemodeselection.h"

bool GameModeSelection::loadMedia()
{
    return background.loadFromFile("sprites/mapselection.jpg", GD.screenRenderer);
}

bool GameModeSelection::render() const
{
    SDL_Rect rect = {0, 0, GD.SCREEN_WIDTH, GD.SCREEN_HEIGHT};
    if (!background.render(GD.screenRenderer, rect))
        return false;

    for (const auto &b : buttons)
    {
        if (!b.render()) return false;
    }

    SDL_RenderPresent(GD.screenRenderer);

    return true;
}

bool GameModeSelection::buildButtons()
{
    SDL_Rect rect = {0, 0, 200, 150};
    std::string s;

    rect = {100, 100, 150, 100};
    s = std::string("normal.png");
    buttons.emplace_back(rect, GD.NONE, s.c_str(), false, true, 0);

    rect = {400, 100, 150, 100};
    s = std::string("blitz.png");
    buttons.emplace_back(rect, GD.NONE, s.c_str(), false, true, 1);

    rect = {100, 250, 150, 100};
    s = std::string("blitz.png");
    buttons.emplace_back(rect, GD.NONE, s.c_str(), false, true, 2);

    rect = {500, 450, 300, 100};
    s = std::string("continue.png");
    buttons.emplace_back(rect, GD.MAPSELECTION, s.c_str(), true, false);

    return true;
}

GameData::Scene GameModeSelection::run()
{
    GD.gameMode = -1;
    buildButtons();

    if (!render())
    {
        return GD.QUIT;
    }

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
                            return GD.MENU;
                            break;
                    }
                    break;
                }
                case SDL_MOUSEBUTTONDOWN:
                {
                    for (auto &b : buttons)
                    {
                        if (b.mouseInside())
                        {
                            if (b.getAction() != GD.NONE)
                            {
                                if (GD.gameMode >= 0)
                                    return b.getAction();
                            }
                            else
                            {
                                for (auto &bt : buttons) bt.deselect();
                                b.select();
                                GD.gameMode = b.getInfo();

                                for (auto &bt : buttons) bt.render();
                                hadBeenRendered = true;
                            }
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
