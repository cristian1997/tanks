#include "Mapa.h"
#include<fstream>
using namespace std;

mapa::mapa()
{
}


mapa::~mapa()
{
}

string mapa::nivelCurent(int nivel)
{
	std::string numeNivel;

	switch (nivel)
	{
	case 1: numeNivel = "nivel_1";
		break;
	case 2: numeNivel = "nivel_2";
		break;
	case 3: numeNivel = "nivel_3";
		break;
	case 4: numeNivel = "nivel_4";
		break;
	case 5: numeNivel = "nivel_5";
		break;
	case 6: numeNivel = "nivel_6";
		break;
	case 7: numeNivel = "nivel_7";
		break;
	case 8: numeNivel = "nivel_8";
		break;
	case 9: numeNivel = "nivel_9";
		break;
	case 10: numeNivel = "nivel_10";
		break;
	case 11: numeNivel = "nivel_11";
		break;
	case 12: numeNivel = "nivel_12";
		break;
	default:
		break;
	}

	return numeNivel;
}

void mapa::renderPic(string *numePic, SDL_Surface &dest, int x, int y)
{   
	patratica = IMG_Load(numePic);
	SDL_Rect pozitiePic = { x, y };

	SDL_BlitSurface(patratica, nullptr, dest, &pozitiePic);
}
void mapa::creareNivel(int nivel)
{
	int x, y ;
	int patrat ;
	string * numePic;

	string numeNivel = nivelCurent(nivel);
	ifstream Level((string)numeNivel);

	for (y = 0; y <= 480; y++)
  	{
		for (x = 0; x <= 680; x++)
		{
			Level >> patrat;
			numePozica = cePatrat(patrat);
			numePic = &numePozica;
			renderPic(numePic, dest, x, y);
		}
	}

}

string mapa::cePatrat(int patrat)
{
	std::string numePatrat;

	switch (patrat)
	{
	case 0:
	case 1:
	case 2:
	case 3:
	case 4:
	case 5:
	case 6:
	case 7:
	case 8:
	case 9:
	case 10:
	case 11:
	case 12:
	case 13:
	case 14:
	case 15:
	case 16:
	case 17:

	default:
		break;
	}
	return numePatrat;
}