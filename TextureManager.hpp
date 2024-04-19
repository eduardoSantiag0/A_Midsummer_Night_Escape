#include <SDL2/SDL_image.h>
#include <SDL2/SDL.h>

class TextureManager 
{
public:
    static SDL_Texture* LoadTexture ( const char* filename, SDL_Renderer* render);
};