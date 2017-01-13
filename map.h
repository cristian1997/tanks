#include "gamedata.h"
#include "texture.h"
#include "tank.h"

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <string>
#include <fstream>


class Map
{
    Texture mapTexture;

public:

	void loadMap(std::vector<Tank> &v);
	bool render() const;
};