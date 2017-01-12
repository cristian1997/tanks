#pragma once

#include "gamedata.h"
#include "texture.h"

#include <SDL2/SDL.h>

class Button
{
private:
    int info;
    SDL_Rect pos;
    GameData::Scene action;
    Texture defaultTexture, hoverTexture, selectedTexture;
    bool isMouseInside, isSelected;
    bool shouldSelected, shouldHover;

    bool inside(int x, int y) const;

public:
    Button(SDL_Rect _pos, GameData::Scene _action, const char fileName[], bool _shouldHover = true, bool _shouldSelected = false, int _info = -1);
    bool render() const;
    bool mouseInside() const;
    bool handleMouseMotion(int x, int y);
    void select();
    void deselect();
    int getInfo() const;
    GameData::Scene getAction() const;
};