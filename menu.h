#include "texture.h"
#include "gamedata.h"

#include <SDL2\SDL.h>
#include <SDL2\SDL_image.h>
#include <stdio.h>

class Menu
{
private:
	Texture background;

    bool loadImage(const char *fileName, SDL_Renderer *renderer);
    bool render(SDL_Renderer *&dest);

public:
	//GamePlay joc;
	//Options optiuni;

    GameData::Scene run();
	/*bool play();
	bool options();
	bool exit();
    int  playerChoiceHandler();*/
};

