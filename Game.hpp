#include "SDL2/SDL.h"
#include "Player.hpp"
#include "Obstacles.hpp"
#include <vector>


class Game 
{
public:
    Game();
    ~Game();

    void run();
    void draw(SDL_Renderer* m_renderer);
    void loadGround (SDL_Renderer* m_renderer);

    std::vector<Obstacles> vetorObstacles;

    void verColisoes();
    Uint32 spawnTimeGenerator();

    SDL_Texture* loadBackground(const char* filepath, SDL_Renderer* renderer);
    bool checkColisao(SDL_Rect a, SDL_Rect b);

    void GameOver();

    void startScreen();
    
private:
    SDL_Window* m_window;
    SDL_Renderer* m_renderer;
    bool m_isRunning;
    int m_WIDTH_WINDOW;
    int m_HEIGHT_WINDOW;

    float maxJumpHeight;

    Uint32 lastTimeSpawned;
    Uint32 startSpawnTime;
    Uint32 spawnTimeInterval; 

    Player m_player;

    SDL_Rect m_ground;
    int m_groundHeight;

    
    SDL_Rect m_background;
    SDL_Texture* background_texture;

};