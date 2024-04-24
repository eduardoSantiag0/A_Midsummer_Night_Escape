#include "SDL2/SDL.h"

class Obstacles
{
private:
    int m_speed;
    SDL_Texture* m_obstacleTexture;
    SDL_Rect m_obstacle;
    bool m_acive;


public:
    Obstacles(int posX, int posY);
    void move();
    void draw(SDL_Renderer* m_renderer);

    SDL_Rect getRect() const;
    SDL_Texture* getTexture (const char* filepath, SDL_Renderer* renderer);
};