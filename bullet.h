#include <SDL2\SDL.h>
#include <SDL2\SDL_image.h>
#include "texture.h"

class Bullet
{
private:
    static Texture bulletTexture;
    static int width, height;
    int lastMovement;
    double xPos, yPos;
    double angle;
    static constexpr double speed = 200.0;

public:

    Bullet(double x, double y, double ang);
    static bool loadImage(const char fileName[], SDL_Renderer *renderer);
    bool render(SDL_Renderer *&dest);
    void updatePos();

    ~Bullet();
};