#include "map.h"

void map::loadMap()
{
	int x,y,i=0;
	int xPos = 0, yPos = 0;

	for (y = 0; y < GD.SCREEN_WIDTH/25; y++)
	{   
		for (x = 0; x < GD.SCREEN_HEIGHT/25; x++)
		{   			
			mapTexture.loadFromFile(std::to_string(GD.mapTextureTypeVector[i]).c_str(), GD.screenRenderer);
			mapTexture.render(GD.screenRenderer, xPos, yPos, 0);
			xPos = xPos + 25;
			SDL_RenderPresent(GD.screenRenderer);
			i++;
		}
		xPos = 0;
		yPos = yPos + 25;
    }
}
