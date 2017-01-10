#include "button.h"

#include <string>

Button::Button(SDL_Rect _pos, GameData::Scene _action, const char fileName[])
{
    isMouseInside = false;
    pos = _pos;
    action = _action;

    std::string s;
    
    s = std::string("sprites/default") + fileName;
    if (!defaultTexture.loadFromFile(s.c_str()))
    {
        printf("Couldn't load %s!", s.c_str());
    }

    s = std::string("sprites/hover") + fileName;
    if (!hoverTexture.loadFromFile(s.c_str()))
    {
        printf("Couldn't load %s!", s.c_str());
    }
}

bool Button::render() const
{
    if (isMouseInside)
    {
        if (!hoverTexture.render(Point(pos.x, pos.y), 0))
        {
            printf("Couldn't render\n");
        }
    }
    else
    {
        if (!defaultTexture.render(Point(pos.x, pos.y), 0))
        {
            printf("Couldn't render\n%s\n", SDL_GetError());
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

GameData::Scene Button::getAction() const
{
    return action;
}
