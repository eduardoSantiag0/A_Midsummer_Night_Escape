#include "SDL2/SDL.h"

class Player 
{
private:
    SDL_Rect m_player_rect;
    int m_pos_chao;
    int maxJumpHeight;

    SDL_Texture* m_playerTexture;

    float jumpVelocity;
    float gravityUp;
    float gravityDown;
    bool isAlive;

    SDL_Rect srcRect;
    int frameWidth;
    int frameHeight;
    int currentFrame;
    int maxFrames;
    int animationSpeed;  
    Uint32 lastFrameTime;


public:
    Player(int pos_chao);
    void jump(bool spacePressed);
    void startJump();
    void endJump();
    void draw(SDL_Renderer* m_renderer);
    bool isJumping;
    bool m_GoDown;
    bool isEscaping;
    void isDead();

    void resetPosition();
    
    SDL_Rect getRect() const;
    SDL_Texture* getTexture (const char* filepath, SDL_Renderer* renderer);
    
    void startEscaping();
    bool getEscaping() const;
    void updateFrame();
};