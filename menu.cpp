#include "menu.h"
#include "gamedata.h"

#include <iostream>

bool Menu::loadMedia()
{
    if (!background.loadFromFile("sprites/menu.jpg", GD.screenRenderer))
    {
        return false;
    }

    buttons.clear();

    SDL_Rect rectForPlay = {GD.SCREEN_WIDTH / 4, GD.SCREEN_HEIGHT / 4, GD.SCREEN_WIDTH / 2 , GD.SCREEN_HEIGHT / 4 - 50};
    buttons.emplace_back(rectForPlay, GD.GAMEPLAY, "play.png");

    SDL_Rect rectForOptions = {GD.SCREEN_WIDTH / 4, GD.SCREEN_HEIGHT / 4 + GD.SCREEN_HEIGHT / 4 - 49 , GD.SCREEN_WIDTH / 2 , GD.SCREEN_HEIGHT / 4 - 50};
    //buttons.emplace_back(rectForOptions, GD.OPTIONS, "options.png");

    SDL_Rect rectForExit = {GD.SCREEN_WIDTH / 4, GD.SCREEN_HEIGHT / 4 + GD.SCREEN_HEIGHT / 4 - 50 + GD.SCREEN_HEIGHT / 4 - 48 , GD.SCREEN_WIDTH / 2 , GD.SCREEN_HEIGHT / 4 - 50};
    //buttons.emplace_back(rectForExit, GD.QUIT, "exit.png");

    return true;
}

bool Menu::render(SDL_Renderer *&dest) const
{
    background.render(dest, Point(0, 0), 0);

    for (const auto &b : buttons)
    {
        b.render();
    }

    SDL_RenderPresent(GD.screenRenderer);

    return true;
}

GameData::Scene Menu::run()
{
    render(GD.screenRenderer);

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
	/*if (!(loadImage(fileName, dest)))
	{
		printf("Unable to loadImagin in main menu !\n");
	}
	else if (!(render(dest)))
	{
		printf("Unable to render in main menu !\n");
	}*/
}

/*int Menu::playerChoiceHandler()
{
	SDL_Rect rectForPlay = { GD.SCREEN_WIDTH / 4, GD.SCREEN_HEIGHT / 4, GD.SCREEN_WIDTH / 2 , GD.SCREEN_HEIGHT / 4 - 50 };
	SDL_Rect rectForOptions = { GD.SCREEN_WIDTH / 4, GD.SCREEN_HEIGHT / 4 + GD.SCREEN_HEIGHT / 4 - 49 , GD.SCREEN_WIDTH / 2 , GD.SCREEN_HEIGHT / 4 - 50 };
	SDL_Rect rectForExit = { GD.SCREEN_WIDTH / 4, GD.SCREEN_HEIGHT / 4 + GD.SCREEN_HEIGHT / 4 - 50 + GD.SCREEN_HEIGHT / 4 - 48 , GD.SCREEN_WIDTH / 2 , GD.SCREEN_HEIGHT / 4 - 50 };
	SDL_Event e;
	bool ok = 1;

	while (SDL_PollEvent(&e))
	{   //daca nu merge insemna ca nu ai tinut cont de coordonatele bune , un plus ceva in if-uri rezolva treaba
		int x, y;
		SDL_GetMouseState(&x, &y);
		if (!(x < GD.SCREEN_WIDTH / 4 || y < GD.SCREEN_HEIGHT / 4 || x > GD.SCREEN_WIDTH / 2 || y > GD.SCREEN_HEIGHT / 4 - 50))
		{
			SDL_SetRenderDrawColor(dest, 0xFF, 0x00, 0x00, 0xFF);
			SDL_RenderFillRect(dest, &rectForPlay);

			while (ok)
			{
				SDL_GetMouseState(&x, &y);
				if (!(x < GD.SCREEN_WIDTH / 4 || y < GD.SCREEN_HEIGHT / 4 || x > GD.SCREEN_WIDTH / 2 || y > GD.SCREEN_HEIGHT / 4 - 50))
				{
					ok = 1;
					if (e.type == SDL_MOUSEBUTTONDOWN)
					{
						return 1;
					}
				}
				else
				{
					SDL_SetRenderDrawColor(dest, 0x00, 0xFF, 0x00, 0xFF);
					SDL_RenderFillRect(dest, &rectForPlay);
					ok = 0;
				}

			}
		}
		else if (!(x < GD.SCREEN_WIDTH / 4 || y < GD.SCREEN_HEIGHT / 4 + GD.SCREEN_HEIGHT / 4 - 49 || x > GD.SCREEN_WIDTH / 2 || y > GD.SCREEN_HEIGHT / 4 - 50))
		{
			SDL_SetRenderDrawColor(dest, 0xFF, 0x00, 0x00, 0xFF);
			SDL_RenderFillRect(dest, &rectForOptions);

			while (ok)
			{
				SDL_GetMouseState(&x, &y);
				if (!(x < GD.SCREEN_WIDTH / 4 || y < GD.SCREEN_HEIGHT / 4 + GD.SCREEN_HEIGHT / 4 - 49 || x > GD.SCREEN_WIDTH / 2 || y > GD.SCREEN_HEIGHT / 4 - 50))
				{
					ok = 1;
					if (e.type == SDL_MOUSEBUTTONDOWN)
					{
						return 2;
					}
				}
				else
				{
					SDL_SetRenderDrawColor(dest, 0x00, 0xFF, 0x00, 0xFF);
					SDL_RenderFillRect(dest, &rectForOptions);
					ok = 0;
				}

			}
		}
		else if (!(x < GD.SCREEN_WIDTH / 4 || y < GD.SCREEN_HEIGHT / 4 + GD.SCREEN_HEIGHT / 4 - 50 + GD.SCREEN_HEIGHT / 4 - 48 || x > GD.SCREEN_WIDTH / 2 || y > GD.SCREEN_HEIGHT / 4 - 50))
		{
			SDL_RenderFillRect(dest, &rectForOptions);
			SDL_RenderFillRect(dest, &rectForExit);

			while (ok)
			{
				SDL_GetMouseState(&x, &y);
				if (!(x < GD.SCREEN_WIDTH / 4 || y < GD.SCREEN_HEIGHT / 4 + GD.SCREEN_HEIGHT / 4 - 50 + GD.SCREEN_HEIGHT / 4 - 48 || x > GD.SCREEN_WIDTH / 2 || y > GD.SCREEN_HEIGHT / 4 - 50))
				{
					ok = 1;
					if (e.type == SDL_MOUSEBUTTONDOWN)
					{
						return 3;
					}
				}
				else
				{
					SDL_SetRenderDrawColor(dest, 0x00, 0xFF, 0x00, 0xFF);
					SDL_RenderFillRect(dest, &rectForOptions);
					ok = 0;
				}

			}

		}
	}
}
*/