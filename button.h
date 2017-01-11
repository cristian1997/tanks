#pragma once

#include "gamedata.h"
#include "texture.h"

#include <SDL.h>

class Button
{
private:
    SDL_Rect pos;
    GameData::Scene action;
    Texture defaultTexture, hoverTexture;
    bool isMouseInside;

    bool inside(int x, int y) const;

public:
    Button(SDL_Rect _pos, GameData::Scene _action, const char fileName[]);
    bool render() const;
    bool mouseInside() const;
    bool handleMouseMotion(int x, int y);
    GameData::Scene getAction() const;
};