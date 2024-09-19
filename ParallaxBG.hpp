#include <vector>
#include "SDL2/SDL.h"


class ParallaxBG
{
private:
    int scrollSpeed;
    int groundY;
    std::vector<SDL_Rect> treeBackgrounds;
    std::vector<SDL_Texture*> m_treeTextures;

    int m_WIDTH_WINDOW;
    int m_HEIGHT_WINDOW;
    SDL_Renderer* m_renderer;

public: 
    ParallaxBG(int m_WIDTH_WINDOW, int m_HEIGHT_WINDOW, int groundY, SDL_Renderer* renderer, int speed);
    void move();
    void draw();
};