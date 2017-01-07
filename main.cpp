#include "tank.h"
#include "bullet.h"
#include <SDL.h>
#include <SDL_image.h>
#include <vector>
#include <stdio.h>
#include"menu.h"

const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;

bool init();
bool loadMedia();
void close();

SDL_Window* window = nullptr;
SDL_Renderer* screenRenderer = nullptr;
Tank player;
Menu menu;
std::vector<Bullet> bullets;

bool init()
{
	if (SDL_Init(SDL_INIT_VIDEO) < 0)
	{
		printf("SDL could not initialize! SDL_Error: %s\n", SDL_GetError());
		return false;
	}

	window = SDL_CreateWindow("SDL Tutorial", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
	if (window == nullptr)
	{
		printf("Window could not be created! SDL_Error: %s\n", SDL_GetError());
		return false;
	}

	screenRenderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
	if (screenRenderer == nullptr)
	{
		printf("Renderer could not be created! SDL_Error: %s\n", SDL_GetError());
	}

	return true;
}

bool loadMedia()
{
	if (!player.loadImage("sprites/blue tank.png", screenRenderer))
	{
		printf("Unable to load image sprites/blue tank.png! SDL Error: %s\n", SDL_GetError());
		return false;
	}

	if (!Bullet::loadImage("sprites/bullet.png", screenRenderer))
	{
		printf("Unable to load image sprites/bullet.png! SDL Error: %s\n", SDL_GetError());
		return false;
	}

	return true;
}

void close()
{
	SDL_DestroyWindow(window);
	window = nullptr;

	SDL_Quit();
}

int main(int argc, char* args[])
{
	int frames;
	int currentScene = 4;
	bool quit = 1;
	if (!init())
	{
		printf("Failed to initialize!\n");
	}
	else
	{
		if (!loadMedia())
		{
			printf("Failed to load media!\n");
		}
		else
		{
			do {
				switch (currentScene)
				{
				case 1:
				{
					if (!(menu.play()))
						printf("Failed to start the Game!\n");
				}
				case 2:
				{
					if (!(menu.options()))
						printf("Failed to open Options\n");
				}
				case 3:
				{
					quit = menu.exit();
				}
				case 4:
				{
					menu.
				}
				 currentScene=menu.playerChoiceHandler();
			} while (quit == 1);
		}

	close();

	return 0;
}
