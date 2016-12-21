#include <SDL2\SDL.h>
#include <SDL2\SDL_image.h>



class Tank
{
private:
    SDL_Texture *tankRenderer;
    int lastMovement;
    bool boolHasMoved;
    int width, height;
    float xPos, yPos;
    float angle;
    float speed, turnSpeed;

    SDL_Texture* loadTexture(const char fileName[], SDL_Renderer *renderer);

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