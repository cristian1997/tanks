#include "button.h"

#include <string>

Button::Button(SDL_Rect _pos, GameData::Scene _action, const char fileName[], bool _shouldHover, bool _shouldSelected, int _info)
{
    isMouseInside = false;
    isSelected = false;

    info = _info;
    pos = _pos;
    action = _action;
    shouldHover = _shouldHover;
    shouldSelected = _shouldSelected;

    std::string s;
    
    s = std::string("sprites/default") + fileName;
    if (!defaultTexture.loadFromFile(s.c_str(), GD.screenRenderer))
    {
        printf("Couldn't load %s!", s.c_str());
    }

    if (shouldHover)
    {
        s = std::string("sprites/hover") + fileName;
        if (!hoverTexture.loadFromFile(s.c_str(), GD.screenRenderer))
        {
            printf("Couldn't load %s!", s.c_str());
        }
    }

    if (shouldSelected)
    {
        s = std::string("sprites/selected") + fileName;
        if (!selectedTexture.loadFromFile(s.c_str(), GD.screenRenderer))
        {
            printf("Couldn't load %s!", s.c_str());
        }
    }
}

bool Button::render() const
{
    if (shouldSelected && isSelected)
    {
        if (!selectedTexture.render(GD.screenRenderer, pos))
        {
            printf("Couldn't render\n");
            return false;
        }
    }
    else if (shouldHover && isMouseInside)
    {
        if (!hoverTexture.render(GD.screenRenderer, pos))
        {
            printf("Couldn't render\n");
            return false;
        }
    }
    else
    {
        if (!defaultTexture.render(GD.screenRenderer, pos))
        {
            printf("Couldn't render\n%s\n", SDL_GetError());
            return false;
        }
    }

    return true;
}

bool Button::inside(int x, int y) const
{
    return pos.x <= x && x < pos.x + pos.w && pos.y < y && y < pos.y + pos.h;
}

bool Button::mouseInside() const
{
    return isMouseInside;
}

bool Button::handleMouseMotion(int x, int y)
{
    if (inside(x, y))
    {
        if (!isMouseInside)
        {
            isMouseInside = true;
            return true;
        }
    }
    else
    {
        if (isMouseInside)
        {
            isMouseInside = false;
            return true;
        }
    }

    return false;
}

void Button::select()
{
    isSelected = true;
}

void Button::deselect()
{
    isSelected = false;
}

int Button::getInfo() const
{
    return info;
}

GameData::Scene Button::getAction() const
{
    return action;
}
