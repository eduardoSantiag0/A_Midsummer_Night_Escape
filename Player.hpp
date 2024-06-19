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

    // const int m_limiar_pulo = 200;
    int m_limiar_pulo;

public:
    Player(int pos_chao);
    void jump();
    void startJump();
    void draw(SDL_Renderer* m_renderer);
    bool isJumping;
    bool m_GoDown;
    
    SDL_Rect getRect() const;
    SDL_Texture* getTexture (const char* filepath, SDL_Renderer* renderer);

};