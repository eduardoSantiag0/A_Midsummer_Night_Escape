#include <iostream>
#include "SDL2/SDL.h"

class Obstacles
{
private:
    int m_speed;
    bool m_active;
    int m_spawn_pos;
    void senoidalMovement();

    bool m_GoUp;
    bool m_GoDown;

    int m_Tipo;
    double m_time;

    std::string spritePath;
    SDL_Texture* m_obstacleTexture;
    SDL_Rect m_obstacle;
    int frameWidth;
    int frameHeight;
    int currentFrame;
    int maxFrames;
    int animationSpeed;  
    SDL_Rect srcRect;    
    Uint32 lastFrameTime;
    SDL_Texture* getTexture (const char* filepath, SDL_Renderer* renderer);

    void updateFrame();
public:
    Obstacles(int posX, int posY, int tipo);
    void move();
    void draw(SDL_Renderer* m_renderer);

    SDL_Rect getRect() const;

};