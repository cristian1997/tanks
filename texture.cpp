#include "texture.h"

bool Texture::loadFromFile(const char fileName[], SDL_Renderer *renderer)
{
    if (texture)
    {
        SDL_DestroyTexture(texture);
        texture = nullptr;
    }

    SDL_Surface *tempSurface = nullptr;
    SDL_Texture *retTexture = nullptr;

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

bool Texture::loadFromText(const std::string text, SDL_Renderer * renderer, TTF_Font *font, SDL_Color &color)
{
    if (texture)
    {
        SDL_DestroyTexture(texture);
        texture = nullptr;
    }

    SDL_Surface* textSurface = TTF_RenderText_Solid(font, text.c_str(), color);
    if (textSurface == nullptr)
    {
        printf("Unable to render text surface! SDL_ttf Error: %s\n", TTF_GetError());
        return false;
    }

    texture = SDL_CreateTextureFromSurface(renderer, textSurface);
    if (texture == nullptr)
    {
        printf("Unable to create texture from rendered text! SDL Error: %s\n", SDL_GetError());
        return false;
    }
    
    width = textSurface->w;
    height = textSurface->h;

    SDL_FreeSurface(textSurface);

    return texture != nullptr;
}

bool Texture::render(SDL_Renderer *&dest, Point pos, double angle, const Point *pivot) const
{
    SDL_Rect rect = {(int)pos.x, (int)pos.y, width, height};
    SDL_RendererFlip fp = SDL_FLIP_NONE;
    SDL_Point *p;

    if (pivot) { p = new SDL_Point;  p->x = pivot->x; p->y = pivot->y; }
    else p = nullptr;

    if (SDL_RenderCopyEx(dest, texture, nullptr, &rect, angle, p, fp)) return false;

    return true;
}

bool Texture::render(SDL_Renderer *& dest, const SDL_Rect & rect) const
{
    if(SDL_RenderCopyEx(dest, texture, nullptr, &rect, 0, nullptr, SDL_FLIP_NONE))  return false;
    
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
    //SDL_DestroyTexture(texture);
    texture = nullptr;
}
