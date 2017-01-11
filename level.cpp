#include"level.h"

void openLevel(int nrLevel)
{
	std::string s = "level" + std::to_string(nrLevel);
	std::fstream f(s);
	f.open(s);
	renderMap(f);
}

void renderMap(std::fstream &f)
{
	int x;
	int i = 0;
	
	f >> x;
	nrEnemyTanks = x;
	f >> x;
	bossTank = x;
	f >> x;
	startPozX = x;
	f >> x;
	startPozY = x;
	

	while(f>>x)
	{
		f >> x;
		GD.mapTextureTypeVector[i] = x;
		i++;
	}

	mapa.loadMap();

}
int getNrEnemyTanks()
{
	return nrEnemyTanks;
}
int getStartPozX()
{
	return startPozX;
}
int getStartPozY()
{
	return startPozY;
}
bool bossTankExist()
{
	return bossTank;
}
