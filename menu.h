#include "texture.h"
#include "gamedata.h"
#include "button.h"

#include <SDL2\SDL.h>
#include <SDL2\SDL_image.h>
#include <stdio.h>
#include <vector>

class Menu
{
private:
	Texture background;
    std::vector<Button> buttons;

    bool render() const;

public:
	//GamePlay joc;
	//Options optiuni;

    GameData::Scene run();
    bool loadMedia();
	/*bool play();
	bool options();
	bool exit();
    int  playerChoiceHandler();*/
};

