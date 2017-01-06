#include <SDL2\SDL.h>
#include <SDL2\SDL_image.h>
#include "texture.h"


class Tank
{
private:
    Texture tankTexture;
    int lastMovement;
    int width, height;
    Point pos;
    double angle;
    double speed, turnSpeed;

public:
    double maxSpeed, maxTurnSpeed;        // pixels per second

    Tank();
    bool loadImage(const char *fileName, SDL_Renderer *renderer);
    void setPos(double x, double y);
    bool render(SDL_Renderer *&dest);
    void updatePos();
    double getX();
    double getY();
    double getW();
    double getH();
    double getAngle();

    void handleEvent(const SDL_Event &e);

    ~Tank();
};