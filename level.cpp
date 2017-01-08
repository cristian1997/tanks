#include"level.h"

void open(int nrLevel)
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
	int textureTypeVector[64*48];
	f >> x;
	nrEnemyTanks = x;
	f >> x;
	bossTank = x;
	f >> x;
	startPozX = x;
	f >> x;
	startPozY = x;
	

	while(!f.eof)
	{
		f >> x;
		textureTypeVector[i] = x;
		i++;
	}

	mapa.run(textureTypeVector);

}
