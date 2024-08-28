#include "SDL2/SDL.h"
#include "Player.hpp"
#include "Obstacles.hpp"
#include <vector>
#include <SDL2/SDL_ttf.h>
#include "Score.hpp"
#include <fstream>

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
    Uint32 spawnControllerDiminish;

    SDL_Texture* loadBackground(const char* filepath, SDL_Renderer* renderer);
    bool checkColisao(SDL_Rect a, SDL_Rect b);

    void gameOverScreen();
    void startScreen();
    
private:
    SDL_Window* m_window;
    SDL_Renderer* m_renderer;
    
    bool m_isRunning;
    bool m_startScreen;
    bool m_gameOverScreen;
    
    int m_WIDTH_WINDOW;
    int m_HEIGHT_WINDOW;

    // float maxJumpHeight;

    Uint32 lastTimeSpawned;
    Uint32 startSpawnTime;
    Uint32 spawnTimeInterval; 

    Player m_player;

    SDL_Rect m_ground;
    int m_groundHeight;

    
    SDL_Rect m_background;
    SDL_Texture* background_texture;

    int  m_score_player;
    int randomIntGenerator(int min, int max);

    SDL_Texture* m_textTexture;
    TTF_Font* m_font;

    Score scoreDisplay;
    std::fstream m_FileHighestScore;
    int m_HighestScores;
    void loadHighestScore();
    void updateHighestScore();

    void renderText(const char* message, int x, int y, float scale, SDL_Color color);
    void loadDisplayHighestScore();

};