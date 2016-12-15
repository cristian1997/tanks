#include <SDL2\SDL.h>
#include <SDL2\SDL_image.h>

class tank
{
private:
    SDL_Surface *tankSurface;
    int lastMovement;
    bool boolHasMoved;
    float xPos, yPos;
    float dx, dy;       // direction on x-axis and y-axis

public:
    float xVel, yVel;   // velocity on x-axis and y-axis
    float speed;        // pixels per second

    tank();
    bool loadImage(const char *fileName);
    void setPos(float x, float y);
    bool render(SDL_Surface *&dest);
    void updatePos();

    bool hasMoved();
    void handleEvent(const SDL_Event &e);

    ~tank();
};