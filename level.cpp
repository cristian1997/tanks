#include"level.h"

void openLevel(int nrLevel)
{
	std::string s = "level" + std::to_string(nrLevel);
	std::fstream f(s);
	f.open(s);
	//renderMap(f);
}

void renderMap(std::fstream &f)
{
	int x;
	int i = 0;
	

	while(f>>x)
	{
		f >> x;
		GD.mapTextureTypeVector[i] = x;
		i++;
	}

	//mapa.loadMap();

}