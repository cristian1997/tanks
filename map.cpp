#include "map.h"

void map::run(int textureTypeVector[64*48])
{
	int x,y;
	char s;
	int xPos = 0, yPos = 0;

	for (y = 0; y < 48; y++)
	{   
		for (x = 0; x < 64; x++)
		{   //modifica tu te rog de aici 
			s = textureTypeVector[i];
			mapTexture.loadFromFile(s, screenRenderer);
			//pana aici
			mapTexture.render(screenRendere, xPos, yPos, 0);
			xPos = xPos + 10;
			SDL_RenderPresent(screenRenderer);
			i++;
		}
		xPos = 0;
		yPos = yPos + 10;
    }
}
// vectorul e de 64*48, deoarece am considerat fiecare patratica din mapa ca fiind de 10 lungime, pe 10 pixeli latime 