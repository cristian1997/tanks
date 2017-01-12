#pragma once

#include "texture.h"
#include "gamedata.h"
#include "button.h"

#include <vector>

class GameModeSelection
{
private:
    Texture background;
    std::vector<Button> buttons;

    bool buildButtons();

public:
    bool loadMedia();
    bool render() const;
    GameData::Scene run();
};