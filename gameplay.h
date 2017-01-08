#include<SDL2/SDL.h>
#include<SDL2/SDL_image.h>
#include"tank.h"
#include"bullet.h"
#include"texture.h"
#include"level.h"
#include"geometry.h"

class GamePlay 
{
public:
	Tank player;
	void openFile(int nrLevel);
	void run(int nrLevel);
};