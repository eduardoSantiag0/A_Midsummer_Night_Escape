#include "SDL2/SDL.h"

//todo Mudar construtor de Obstáculos
//todo Gerador de numeros

class Obstacles
{
private:
    int m_speed;
    SDL_Texture* m_obstacleTexture;
    SDL_Rect m_obstacle;
    bool m_acive;


public:
    Obstacles(int posX, int posY, int tipo);
    void move();
    void draw(SDL_Renderer* m_renderer);

    SDL_Rect getRect() const;
    SDL_Texture* getTexture (const char* filepath, SDL_Renderer* renderer);
};