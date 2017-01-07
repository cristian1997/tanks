#include "texture.h"

bool Texture::loadFromFile(const char fileName[], SDL_Renderer * renderer)
{
    SDL_Surface *tempSurface;
    SDL_Texture *retTexture;

    tempSurface = IMG_Load(fileName);
    if (tempSurface == nullptr) return nullptr;

    SDL_SetColorKey(tempSurface, SDL_TRUE, SDL_MapRGB(tempSurface->format, 0xFF, 0xFF, 0xFF));

    retTexture = SDL_CreateTextureFromSurface(renderer, tempSurface);

    if (retTexture != nullptr)
    {
        SDL_QueryTexture(retTexture, nullptr, nullptr, &width, &height);
    }

    texture = retTexture;

    SDL_FreeSurface(tempSurface);
    return (retTexture != nullptr);
}

bool Texture::render(SDL_Renderer *&dest, Point pos, double angle, Point *pivot)
{
    SDL_Rect rect = {(int)pos.x, (int)pos.y, width, height};
    SDL_RendererFlip fp = SDL_FLIP_NONE;
    SDL_Point *p;

    if (pivot) { p = new SDL_Point;  p->x = pivot->x; p->y = pivot->y; }
    else p = nullptr;

    if (SDL_RenderCopyEx(dest, texture, nullptr, &rect, angle, p, fp)) return false;

    return true;
}

double Texture::getW()
{
    return width;
}

double Texture::getH()
{
    return height;
}

Texture::~Texture()
{
    SDL_DestroyTexture(texture);
    texture = nullptr;
}
