#pragma once
#include <SDL2/SDL.h>

class mapa
{
public:
	mapa();
	~mapa();

	std::string numePozica;

	void mapa::creareNivel(int nivel);
	string mapa::nivelCurent(int nivel);
	void mapa::renderPic(string *numePic, SDL_Surface &dest,int x, int y);
	string mapa::cePatrat(char patrat);


private:

	SDL_Surface * patratica;
	int latime;
	int lungime;
	
};
//class scena:mapa//ce face mapa + meniul central + meniul de pauza + eventhandler +
//class mapa//randeze imagini pe suprafata lui;
//gWindow;gScreenSurface