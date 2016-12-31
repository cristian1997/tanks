#include <SDL2\SDL.h>
#include <SDL2\SDL_image.h>
#include "texture.h"


class Tank
{
private:
    Texture tankTexture;
    int lastMovement;
    bool boolHasMoved;
    int width, height;
    float xPos, yPos;
    float angle;
    float speed, turnSpeed;

public:
    float maxSpeed, maxTurnSpeed;        // pixels per second

    Tank();
    bool loadImage(const char *fileName, SDL_Renderer *renderer);
    void setPos(float x, float y);
    bool render(SDL_Renderer *&dest);
    void updatePos();

    bool hasMoved();
    void handleEvent(const SDL_Event &e);

    ~Tank();
};