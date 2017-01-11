#include"options.h"

bool Options ::loadFilesForOptions()
{
	if (!option.loadFromFile("OptionsMenu.jpg", GD.screenRenderer))
	{
		return false;
	}
	return true;
}

void Options::render()
{
	option.render(GD.screenRenderer, Point(0, 0), 0);
	SDL_RenderPresent(GD.screenRenderer);
}

void Options::run()
{
	render();
    
	
}
#include <thread>
