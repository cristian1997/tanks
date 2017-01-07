#include <SDL.h>
#include <SDL_image.h>
#include "texture.h"


const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;

class Menu
{
private:
	Texture menuTexture;

public:
	GamePlay joc;
	Options optiuni;

	bool loadImage(const char *fileName, SDL_Renderer *renderer);
	bool render(SDL_Renderer *&dest);
	bool play();
	bool options();
	bool exit();
    int  playerChoiceHandler();
};

