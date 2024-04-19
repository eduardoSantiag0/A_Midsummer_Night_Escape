#include "SDL2/SDL.h"
#include "Player.hpp"

class Game 
{
public:
    Game();
    ~Game();

    void run();
    void draw(SDL_Renderer* m_renderer);
    void loadGround (SDL_Renderer* m_renderer);
    
private:
    SDL_Window* m_window;
    SDL_Renderer* m_renderer;
    bool m_isRuning;
    int m_WIDTH_WINDOW;
    int m_HEIGHT_WINDOW;

    float currentDeltaJump;
    float lastDeltaJump;


    Player m_player;

    SDL_Rect m_ground;
    int m_groundHeight;

    constexpr static float jumpInterval = 400.0f;
    
    SDL_Rect m_background;
    SDL_Texture* background_texture;
    SDL_Texture* loadBackground(const char* filepath, SDL_Renderer* renderer);
    bool checkColisao(SDL_Rect a, SDL_Rect b);
    void GameOver();
};