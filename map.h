#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "gamedata.h"
#include "texture.h"
#include <string>

class Map
{
public:
	Texture mapTexture;

	void loadMap();
	void render();
};