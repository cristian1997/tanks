#pragma once

#include <SDL.h>
#include <SDL_image.h>
#include <fstream>
#include <string>
#include "map.h"
#include "gamedata.h"
    



    int nrEnemyTanks;
    bool bossTank;
    int startPozX;
    int startPozY;
    map mapa;

    void openLevel(int nrLevel);
    void renderMap(std::fstream &);
    int getNrEnemyTanks();
    int getStartPozX();
    int getStartPozY();