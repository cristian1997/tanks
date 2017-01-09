#pragma once

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <fstream>
#include <string>
//#include "map.h"
    

class Level
{
    int nrEnemyTanks;
    bool bossTank;
    int startPozX;
    int startPozY;
    //map mapa;

    void open(int nrLevel);
    void renderMap(std::fstream &);
    int getNrEnemyTanks();
    int getStartPozX();
    int getStartPozY();
};