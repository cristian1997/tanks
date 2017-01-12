#include "gamedata.h"
#include "texture.h"

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <string>
#include <fstream>


class Map
{
    Texture mapTexture;

public:

	void loadMap();
	bool render() const;
};