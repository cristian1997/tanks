#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include "texture.h"
#include "gamedata.h"


class Options
{
private:
	Texture option;

public:
	bool loadFilesForOptions();
	void run();
	void render();
};