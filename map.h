#include <SDL.h>
#include <SDL_image.h>
#include "gamedata.h"
#include "texture.h"
#include <string>

class map
{
public:
	Texture mapTexture;
	void loadMap();
	void render();
};