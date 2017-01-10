#include "texture.h"

bool Texture::loadFromFile(const char fileName[])
{
    SDL_Surface *tempSurface = nullptr;
    SDL_Texture *retTexture = nullptr;

    tempSurface = IMG_Load(fileName);
    if (tempSurface == nullptr) return nullptr;

    SDL_SetColorKey(tempSurface, SDL_TRUE, SDL_MapRGB(tempSurface->format, 0xFF, 0xFF, 0xFF));

    retTexture = SDL_CreateTextureFromSurface(GD.screenRenderer, tempSurface);

    if (retTexture != nullptr)
    {
        SDL_QueryTexture(retTexture, nullptr, nullptr, &width, &height);
    }

    texture = retTexture;

    SDL_FreeSurface(tempSurface);
    return (retTexture != nullptr);
}

bool Texture::render(Point pos, double angle, const Point *pivot) const
{
    SDL_Rect rect = {(int)pos.x, (int)pos.y, width, height};
    SDL_RendererFlip fp = SDL_FLIP_NONE;
    SDL_Point *p;

    if (pivot) { p = new SDL_Point;  p->x = pivot->x; p->y = pivot->y; }
    else p = nullptr;

    if (SDL_RenderCopyEx(GD.screenRenderer, texture, nullptr, &rect, angle, p, fp)) return false;

    return true;
}

int Texture::getW() const
{
    return width;
}

int Texture::getH() const
{
    return height;
}

Texture::~Texture()
{
    SDL_DestroyTexture(texture);
    texture = nullptr;
}
