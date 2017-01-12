#include "mapselection.h"

bool MapSelection::loadMedia()
{
    return background.loadFromFile("sprites/mapselection.jpg", GD.screenRenderer);
}

bool MapSelection::render() const
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

bool MapSelection::buildButtons()
{
    SDL_Rect rect = {0, 0, 200, 150};

    for (int i = 0; i < GD.nrMaps; ++i)
    {
        int lin = i / 3;
        int col = i % 3;

        rect.x = 50 + col * 250;
        rect.y = 100 + lin * 250;

        std::string s = std::string("map") + std::to_string(i) + std::string(".jpg");

        buttons.emplace_back(rect, GD.NONE, s.c_str(), false, true, i);
    }

    return false;
}

GameData::Scene MapSelection::run()
{
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
                            if (b.getAction() != GD.NONE) return b.getAction();
                            else
                            {
                                for (auto &bt : buttons) bt.deselect();
                                b.select();
                                GD.nrLevel = b.getInfo();

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
