#include <SDL2\SDL.h>
#include <SDL2\SDL_image.h>
#include "texture.h"

class Bullet
{
private:
    Texture bulletTexture;
    int lastMovement;
    int width, height;
    float xPos, yPos;
    float angle;
    static constexpr float speed = 20.0;

public:

    Bullet(float x, float y, float ang);
    bool loadImage(SDL_Renderer *renderer);
    bool render(SDL_Renderer *&dest);
    void updatePos();

    ~Bullet();
};