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

bool Texture::render(SDL_Renderer *&dest, int xPos, int yPos, float angle)
{
    SDL_Rect pos = {(int)xPos, (int)yPos, width, height};

    SDL_RendererFlip fp = SDL_FLIP_NONE;
    if (SDL_RenderCopyEx(dest, texture, nullptr, &pos, angle, nullptr, fp)) return false;

    SDL_RenderPresent(dest);

    return true;
}

Texture::~Texture()
{
    SDL_DestroyTexture(texture);
    texture = nullptr;
}
