#include <iostream>
#include "TextureManager.hpp"
#include <SDL2/SDL_image.h>


SDL_Texture* TextureManager::LoadTexture ( const char* filename, SDL_Renderer* render) 
{
    SDL_Surface* tempSurface = IMG_Load(filename);
    if (!tempSurface) {
        std::cerr << "Failed to load image: " << filename << ", Error: " << IMG_GetError() << std::endl;
        return nullptr; 
    }
    SDL_Texture* tex = SDL_CreateTextureFromSurface(render, tempSurface);
    SDL_FreeSurface(tempSurface);

    if (!tex) {
        std::cerr << "Failed to create texture from surface: " << filename << ", Error: " << SDL_GetError() << std::endl;
        return nullptr;
    }
    return tex;
}

