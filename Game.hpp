#include "SDL2/SDL.h"
#include "Player.hpp"
#include "Obstacles.hpp"
#include <vector>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_mixer.h>
#include "Score.hpp"
#include <fstream>
#include "ParallaxBG.hpp"

class Game 
{
public:
    Game();
    ~Game();

    void run();
    void draw(SDL_Renderer* m_renderer);

    std::vector<Obstacles> vetorObstacles;

    void verColisoes();
    bool checkColisao(SDL_Rect a, SDL_Rect b);
    Uint32 spawnTimeGenerator();
    Uint32 spawnControllerDiminish;


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

    Uint32 lastTimeSpawned;
    Uint32 startSpawnTime;
    Uint32 spawnTimeInterval; 

    Player m_player;

    // SDL_Rect m_ground;
    int m_groundHeight;
    int groundY;

    
    SDL_Rect m_background;
    SDL_Texture* background_texture;
    SDL_Rect treeBackground;
    SDL_Texture* treeTexture;
    void loadBackground(SDL_Texture*& texture, const char* filepath, SDL_Renderer* renderer, SDL_Rect srcRect);
    SDL_Texture* groundTexture;

    int  m_score_player;
    int randomIntGenerator(int min, int max);

    SDL_Texture* m_textTexture;
    TTF_Font* m_font;
    SDL_Color textColor;

    Score scoreDisplay;
    std::fstream m_FileHighestScore;
    int m_HighestScores;
    void loadHighestScore();
    void updateHighestScore();

    void renderText(const char* message, int x, int y, float scale, SDL_Color color);
    void loadDisplayHighestScore();

    Mix_Music* themeSong;


    std::vector<SDL_Rect> treeBackgrounds;

    ParallaxBG parallaxBG;

    void moveGround();
    std::vector<SDL_Rect> groundArray;
    int groundScrollSpeed;

};