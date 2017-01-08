#include "menu.h"
#include "level.h"

bool Menu::loadImage(const char *fileName)
{
	return menuTexture.loadFromFile(fileName, screenRenderer);
}

bool Menu::render()
{    

	SDL_Rect rectForPlay = { SCREEN_WIDTH / 4, SCREEN_HEIGHT / 4, SCREEN_WIDTH / 2 , SCREEN_HEIGHT / 4 - 50 };
	SDL_Rect rectForOptions = { SCREEN_WIDTH / 4, SCREEN_HEIGHT / 4 + SCREEN_HEIGHT / 4 - 49 , SCREEN_WIDTH / 2 , SCREEN_HEIGHT / 4 - 50 };
	SDL_Rect rectForExit = { SCREEN_WIDTH / 4, SCREEN_HEIGHT / 4 + SCREEN_HEIGHT / 4 - 50 + SCREEN_HEIGHT / 4 - 48 , SCREEN_WIDTH / 2 , SCREEN_HEIGHT / 4 - 50 };
	SDL_SetRenderDrawColor(screenRenderer, 0x00, 0xFF, 0x00, 0xFF);

	SDL_RenderFillRect(screenRenderer, &rectForPlay);
	SDL_RenderFillRect(screenRenderer, &rectForOptions);
	SDL_RenderFillRect(screenRenderer, &rectForExit);

    return menuTexture.render(screenRenderer, 0.0 ,0.0 ,0.0);
}
void Menu::run(const char *fileName)
{
	if (!(loadImage(fileName, screenRenderer)))
	{
		printf("Unable to loadImagin in main menu !\n");
	}
	else if (!(render(screenRenderer)))
	{
		printf("Unable to render in main menu !\n");
	}
}





















int Menu::playerChoiceHandler()
{
	SDL_Rect rectForPlay = { SCREEN_WIDTH / 4, SCREEN_HEIGHT / 4, SCREEN_WIDTH / 2 , SCREEN_HEIGHT / 4 - 50 };
	SDL_Rect rectForOptions = { SCREEN_WIDTH / 4, SCREEN_HEIGHT / 4 + SCREEN_HEIGHT / 4 - 49 , SCREEN_WIDTH / 2 , SCREEN_HEIGHT / 4 - 50 };
	SDL_Rect rectForExit = { SCREEN_WIDTH / 4, SCREEN_HEIGHT / 4 + SCREEN_HEIGHT / 4 - 50 + SCREEN_HEIGHT / 4 - 48 , SCREEN_WIDTH / 2 , SCREEN_HEIGHT / 4 - 50 };
	SDL_Event e;
	bool ok = 1;

	while (SDL_PollEvent(&e))
	{   //daca nu merge insemna ca nu ai tinut cont de coordonatele bune , un plus ceva in if-uri rezolva treaba
		int x, y;
		SDL_GetMouseState(&x, &y);
		if (!(x < SCREEN_WIDTH / 4 || y < SCREEN_HEIGHT / 4 || x > SCREEN_WIDTH / 2 || y > SCREEN_HEIGHT / 4 - 50))
		{
			SDL_SetRenderDrawColor(screenRenderer, 0xFF, 0x00, 0x00, 0xFF);
			SDL_RenderFillRect(screenRenderer, &rectForPlay);

			while (ok)
			{
				SDL_GetMouseState(&x, &y);
				if (!(x < SCREEN_WIDTH / 4 || y < SCREEN_HEIGHT / 4 || x > SCREEN_WIDTH / 2 || y > SCREEN_HEIGHT / 4 - 50))
				{
					ok = 1;
					if (e.type == SDL_MOUSEBUTTONDOWN)
					{
						return 1;
					}
				}
				else
				{
					SDL_SetRenderDrawColor(screenRenderer, 0x00, 0xFF, 0x00, 0xFF);
					SDL_RenderFillRect(screenRenderer, &rectForPlay);
					ok = 0;
				}

			}
		}
		else if (!(x < SCREEN_WIDTH / 4 || y < SCREEN_HEIGHT / 4 + SCREEN_HEIGHT / 4 - 49 || x > SCREEN_WIDTH / 2 || y > SCREEN_HEIGHT / 4 - 50))
		{
			SDL_SetRenderDrawColor(screenRenderer, 0xFF, 0x00, 0x00, 0xFF);
			SDL_RenderFillRect(screenRenderer, &rectForOptions);

			while (ok)
			{
				SDL_GetMouseState(&x, &y);
				if (!(x < SCREEN_WIDTH / 4 || y < SCREEN_HEIGHT / 4 + SCREEN_HEIGHT / 4 - 49 || x > SCREEN_WIDTH / 2 || y > SCREEN_HEIGHT / 4 - 50))
				{
					ok = 1;
					if (e.type == SDL_MOUSEBUTTONDOWN)
					{
						return 2;
					}
				}
				else
				{
					SDL_SetRenderDrawColor(screenRenderer, 0x00, 0xFF, 0x00, 0xFF);
					SDL_RenderFillRect(screenRenderer, &rectForOptions);
					ok = 0;
				}

			}
		}
		else if (!(x < SCREEN_WIDTH / 4 || y < SCREEN_HEIGHT / 4 + SCREEN_HEIGHT / 4 - 50 + SCREEN_HEIGHT / 4 - 48 || x > SCREEN_WIDTH / 2 || y > SCREEN_HEIGHT / 4 - 50))
		{
			SDL_RenderFillRect(screenRenderer, &rectForOptions);
			SDL_RenderFillRect(screenRenderer, &rectForExit);

			while (ok)
			{
				SDL_GetMouseState(&x, &y);
				if (!(x < SCREEN_WIDTH / 4 || y < SCREEN_HEIGHT / 4 + SCREEN_HEIGHT / 4 - 50 + SCREEN_HEIGHT / 4 - 48 || x > SCREEN_WIDTH / 2 || y > SCREEN_HEIGHT / 4 - 50))
				{
					ok = 1;
					if (e.type == SDL_MOUSEBUTTONDOWN)
					{
						return 3;
					}
				}
				else
				{
					SDL_SetRenderDrawColor(screenRenderer, 0x00, 0xFF, 0x00, 0xFF);
					SDL_RenderFillRect(screenRenderer, &rectForOptions);
					ok = 0;
				}

			}

		}
	}
}
