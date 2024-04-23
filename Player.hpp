#include "SDL2/SDL.h"

class Player 
{
public:
    Player(int pos_chao);
    void jump();
    void draw(SDL_Renderer* m_renderer);
    bool isJumping;
    bool m_GoDown;
    
    SDL_Rect getRect() const;
    SDL_Texture* getTexture (const char* filepath, SDL_Renderer* renderer);


private:
    SDL_Rect m_player_rect;
    int m_pos_chao;
    int maxJumpHeight;
    float m_gravity;

    SDL_Texture* m_playerTexture;
};