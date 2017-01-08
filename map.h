#include<SDL2/SDL.h>
#include<SDL2/SDL_image.h>
#include"gamedata.h"
#include"texture.h"

class map
{
public:
	Texture mapTexture;
	void run(int textureTypeVector[64*48]);
};