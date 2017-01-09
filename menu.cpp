#include "menu.h"
#include "gamedata.h"

#include <iostream>

bool Menu::loadImage(const char *fileName, SDL_Renderer *renderer)
{
	return background.loadFromFile(fileName, renderer);
}

bool Menu::render(SDL_Renderer *&dest)
{    
    background.loadFromFile("sprites/menu.jpg", GD.screenRenderer);
    background.render(dest, Point(0, 0), 0);

	SDL_Rect rectForPlay = { GD.SCREEN_WIDTH / 4, GD.SCREEN_HEIGHT / 4, GD.SCREEN_WIDTH / 2 , GD.SCREEN_HEIGHT / 4 - 50 };
	SDL_Rect rectForOptions = { GD.SCREEN_WIDTH / 4, GD.SCREEN_HEIGHT / 4 + GD.SCREEN_HEIGHT / 4 - 49 , GD.SCREEN_WIDTH / 2 , GD.SCREEN_HEIGHT / 4 - 50 };
	SDL_Rect rectForExit = { GD.SCREEN_WIDTH / 4, GD.SCREEN_HEIGHT / 4 + GD.SCREEN_HEIGHT / 4 - 50 + GD.SCREEN_HEIGHT / 4 - 48 , GD.SCREEN_WIDTH / 2 , GD.SCREEN_HEIGHT / 4 - 50 };
	SDL_SetRenderDrawColor(dest, 0x00, 0xFF, 0x00, 0xFF);

	SDL_RenderFillRect(dest, &rectForPlay);
	SDL_RenderFillRect(dest, &rectForOptions);
	SDL_RenderFillRect(dest, &rectForExit);

    return true;
}

GameData::Scene Menu::run()
{
    render(GD.screenRenderer);
    SDL_RenderPresent(GD.screenRenderer);
    std::cout << "menu\n";
    SDL_Event e;

    while (true)
    {
        if (SDL_PollEvent(&e))
        {
            if (e.type == SDL_KEYDOWN)
            {
                if (e.key.keysym.sym == SDLK_RETURN)
                {
                    return GD.GAMEPLAY;
                }
            }
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