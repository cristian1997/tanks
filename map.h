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
    int type[GD.SCREEN_HEIGHT / GD.SPRITE_HEIGHT][GD.SCREEN_WIDTH / GD.SPRITE_WIDTH];

public:

	void loadMap();
	bool render() const;
    int getType(int i, int j) const;
    void setType(int i, int j, int newType);
};